/*
   Meeting Room 365 E-ink Display App
   (c) 2022 James Futhey. All Rights Reserved.
*/

//////////////////////////////////
//////// CONFIGURATION //////////
////////////////////////////////

// Wifi SSID & Password
char ssid[] = "Wasabi";
char pass[] = "letthemeatsushi";

// Display Key
char displayKey[] = "fooallbars";

// Timezone String
// If this is set, you don't need to provide an offset
// ------------------------------------------------------------
// String timezone_string = ""; // None, or use your own custom Unix timezone string
// String timezone_string = "America/New_York"; // Eastern, US
// String timezone_string = "America/Chicago"; // Central, US
// String timezone_string = "America/Denver"; // Mountain, US
String timezone_string = "America/Los_Angeles"; // Pacific, US
// ------------------------------------------------------------

// Timezone Offset, if timezone_string is not set
int timeZone = 0;
// ------------------------------------------------------------

// Use a digital clock (vs. analog clock)
int digitalclock = 2;

// Refresh Interval (In Minutes)
int update_clock_each_minute = 0; // Update clock more often than meetings are refreshed
int minutes = 3; // Fetch events on this interval

// Event refresh rate when on standby (seconds)
#define TIME_TO_SLEEP 600

// Touchscreen enabled start / end time
int touch_start_hour = 0; // <= 0 touchscreen always enabled / disabled
int touch_end_hour = 0; // >= 24 touchscreen always enabled, 0 always disabled

// Show / hide battery indicator, battery %, temperature
int temp_in_f = 1;
int show_temperature = 0;
int show_battery_icon = 1;
int show_battery_percent = 1;
int battery_icon_offset = 0; // Normally 0, 208 when right aligned

// Battery voltage min/max
const float battery_max = 4.60; // Maximum voltage of battery
const float battery_min = 3.3;  // Minimum voltage before shutdown

// Screen rotation, 1-4; 1 for Portrait, Default 4 for landscape 
int rotation = 4; 


//////////////////////////////////
///// INTERNATIONALIZATION //////
////////////////////////////////
String extend = "Extend";
String grab_room = "Grab Room";
String end_meeting = "End Meeting";
String please_wait_str = "Please Wait..";


//////////////////////////////////
// DO NOT EDIT BELOW THIS LINE //
////////////////////////////////

// Warn if not Inkplate 6PLUS
#ifndef ARDUINO_INKPLATE6PLUS
#error "Error: This program can only run on the Inkplate 6PLUS."
#endif

#include "Inkplate.h"
#include "generatedUI.h"
#include "driver/rtc_io.h"
#include "Network.h"
#include <algorithm>
#include <ezTime.h>
#include <ctime>

RTC_DATA_ATTR int bootCount = 0;
#define uS_TO_S_FACTOR 1000000
unsigned long lastMillis;
unsigned long lastMillis2;
byte touchPadPin = PAD1;

int battery_is_below_threshold = 0;
float battery_threshold = 20.0;
int use_digital_clock = 0;
int wake_btn_pressed = 0;
int show_reserve_btn = 0;
int show_extend_btn = 0;
int show_end_btn = 0;
String voltstr = "";
int please_wait = 0;
int twentyfour = 0;
int sleeping = 0;
int occupied = 0;
String data[11];
int action = 0;
int hours = 0;
char date[64];

Inkplate display(INKPLATE_3BIT);
Network network;

void setup() {
    display.begin();
    Serial.begin(115200);
    display.frontlight(0);
    display.setRotation(rotation);
    
    // Setup mcp interrupts
    display.pinModeInternal(MCP23017_INT_ADDR, display.mcpRegsInt, touchPadPin, INPUT);
    display.setIntOutput(1, false, false, HIGH);
    display.setIntPin(touchPadPin, RISING);
    if (!display.tsInit(true)) Serial.println("Touchscreen init failed!");
    
    action = 0;
    ++bootCount;
    displayInfo();
    network.begin();
    getDisplayData();
}

void readBattery() {
    String charging = " ";
    float battery_percent = 0.0;
    int powered = display.readPowerGood();
    float voltage = display.readBattery();
    float temp = display.readTemperature();
    voltstr = String(voltage, 1);
    
    // Serial debugging information
    Serial.println("Hour of day:");
    Serial.println(hours);
    Serial.println("Voltage, powered, temp, batt<threshold:");
    Serial.println(voltage);
    Serial.println(powered);
    Serial.print(display.readTemperature(), DEC);
    Serial.println(" ");

    // Convert voltage to percent
    battery_percent = ((voltage - battery_min) / (battery_max - battery_min)) * 100;
    if (battery_percent >= battery_threshold) battery_is_below_threshold = 0;
    else battery_is_below_threshold = 1;
    Serial.println(battery_is_below_threshold);
    
    rect02_b_x = 774 + (battery_percent / 4); // Dynamic icon "fill" width 774-799
    if (battery_percent >= 100.0) battery_percent = 100.0;
    if (battery_percent < 0.0) battery_percent = 0.0;
    if (String(powered) == "255") charging = "+";
    if (battery_percent == 100) charging = "";
    text0_content = charging + String(battery_percent, 0) + "%";

    if (show_temperature) {
        show_battery_percent = 1;
        if (temp_in_f) temp = temp * (9/5) + 32;
        text0_content = " " + String(temp, 0) + " " + (temp_in_f ? "F" : "C");
    }
}

void getTimeUpdateClock() {
    // Timezone string to offset
    if (timezone_string != "") {
      Timezone LocalTime;
      LocalTime.setLocation(String(timezone_string));
      timeZone = LocalTime.getOffset() / 60 * -1;
      Serial.println("timezone_string, timeZone");
      Serial.println(timezone_string);
      Serial.println(timeZone);
    }
    
    network.getTime(date);

    // Update clock
    digital_clock0_h = widget1_h = ((date[0] - '0') * 10) + (date[1] - '0');
    digital_clock0_m = widget1_m = ((date[3] - '0') * 10) + (date[4] - '0');
    use_digital_clock = digitalclock;

    // Update digital clock string (2)
    if (digitalclock == 2) {
      text5c_content = String(digital_clock0_h) + ":" + (digital_clock0_m < 10 ? "0" : "") + String(digital_clock0_m);
      text5c_cursor_x = digital_clock0_h >= 20 ? 790 : (digital_clock0_h >= 10 ? 800 : 823);
    }
}

void updateOnlyClock() {
    display.clearDisplay();
    please_wait = 0;
    readBattery();
    sleeping = 0;
  
    getTimeUpdateClock();
    hideButtonsIfSleeping();
    
    mainDraw();
    display.display();
    sleepOrDont();
}

void hideButtonsIfSleeping() {
    // Hide buttons if we will deep sleep, exception on wake button press
    if (wake_btn_pressed == 0 && (hours < touch_start_hour || hours >= touch_end_hour || battery_is_below_threshold == 1)) {
      show_reserve_btn = 0;
      show_extend_btn = 0;
      show_end_btn = 0;
      sleeping = 1;
    }
}

void sleepOrDont() {
    if (wake_btn_pressed == 1 || (hours > touch_start_hour && hours < touch_end_hour && battery_is_below_threshold == 0)) {
      Serial.println("Touchscreen enabled");
      // wake_btn_pressed = 0;
      
    } else {
      Serial.println("Touchscreen disabled for 10 minutes");

      // Deep sleep
      display.tsShutdown();
      rtc_gpio_isolate(GPIO_NUM_12);
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_36, 0);
      esp_deep_sleep_start();
    }
}

void getDisplayData() {
    display.clearDisplay();
    please_wait = 0;
    readBattery();
    sleeping = 0;
    
    while (!network.getData()) {
        Serial.println("Retrying retriving data!");
        delay(100);
    }

    getTimeUpdateClock();
    hideButtonsIfSleeping();
    
    mainDraw();
    display.display();
    sleepOrDont();
}

void resetText() {
    Serial.println("Resetting display");
    display.clearDisplay();
    display.display(1); // Immediate feedback, even if this executes slower
    
    // Reset all text to "loading" & empty state
    use_digital_clock = digitalclock;
    text1_content = "";
    text2_content = "";
    text5_content = please_wait_str;
    text5b_content = "";
    text6_content = "";
    text7_content = "";
    text8_content = "";
    text9_content = "";
    show_reserve_btn = 0;
    show_extend_btn = 0;
    show_end_btn = 0;
    please_wait = 1;
    
    mainDraw();
    display.display();
}

void keysEvents() {
    // Portrait
    if (rotation == 1 || rotation == 3) {
      // Instant Reservation Press
      if (display.touchInArea(500, 772, 245, 100) && show_reserve_btn == 1) {
          Serial.println("Instant Reservation Pressed");
          resetText();
          action = 1; // Instant Reservation
          getDisplayData();
      }
      // End Early Press
      if (display.touchInArea(500, 900, 245, 100) && show_end_btn == 1) {
          Serial.println("End Early Pressed");
          resetText();
          action = 2; // End early
          getDisplayData();
      }
      // Extend Meeting Press
      if (display.touchInArea(500, 782, 245, 100) && show_extend_btn == 1) {
          Serial.println("Extend Meeting Pressed");
          resetText();
          action = 3; // Extend Meeting
          getDisplayData();
      }
     
    } else { // Landscape
      // Instant Reservation Press
      if (display.touchInArea(770, 185, 245, 100) && show_reserve_btn == 1) {
          Serial.println("Instant Reservation Pressed");
          resetText();
          action = 1; // Instant Reservation
          getDisplayData();
      }
      // End Early Press
      if (display.touchInArea(770, 400, 245, 100) && show_end_btn == 1) {
          Serial.println("End Early Pressed");
          resetText();
          action = 2; // End early
          getDisplayData();
      }
      // Extend Meeting Press
      if (display.touchInArea(770, 292, 245, 100) && show_extend_btn == 1) {
          Serial.println("Extend Meeting Pressed");
          resetText();
          action = 3; // Extend Meeting
          getDisplayData();
      }
    }

    // Fetch new display data every n minutes
    if (millis() - lastMillis >= minutes * 60 * 1000UL) {
        Serial.println("Refreshing events due to timer");
        lastMillis = millis();
        wake_btn_pressed = 0;
        action = 0;
        getDisplayData();
        
    } else if (millis() - lastMillis2 >= 60 * 1000UL) {
       // Handle 1 minute interval clock updates
       lastMillis2 = millis();
       if (update_clock_each_minute == 1) updateOnlyClock();
    }
}

// Function that will write number of boots and boot reason to screen
void displayInfo() {
    Serial.print(F("Boot count: "));
    Serial.println(bootCount, DEC);

    // Display wake up reason
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();
    
    switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Wakeup caused by external signal using RTC_IO");
        wake_btn_pressed = 1;
        resetText();
        break;
    case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Wakeup caused by external signal using RTC_CNTL");
        break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Wakeup caused by timer");
        break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Wakeup caused by touchpad");
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Wakeup caused by ULP program");
        break;
    default:
        Serial.println("Wakeup was not caused by deep sleep");
        break;
    }
}

void loop() {
    keysEvents();
}
