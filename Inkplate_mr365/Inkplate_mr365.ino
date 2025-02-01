/*
   Meeting Room 365 E-ink Display App
   Designed for the Inkplate 6PLUS, 6PLUSV2, 6FLICK.
   (c) 2022-2024 James Futhey. All Rights Reserved.
*/

//////////////////////////////////
//////// CONFIGURATION //////////
////////////////////////////////

// Wifi SSID & Password
char ssid[] = "networkssid";
char pass[] = "wifipassword";

// Display Key
char displayKey[] = "yourdisplaykeyhere";

// Timezone String
// If this is set, you don't need to provide an offset
// ------------------------------------------------------------
String timezone_string = ""; // None, or use your own custom Unix timezone string
// ------------------------------------------------------------
// String timezone_string = "America/New_York"; // Eastern, US
// String timezone_string = "America/Chicago"; // Central, US
// String timezone_string = "America/Denver"; // Mountain, US
// String timezone_string = "America/Los_Angeles"; // Pacific, US
// ------------------------------------------------------------
// String timezone_string = "Asia/Taipei"; // Taipei, Taiwan
// String timezone_string = "Asia/Tokyo"; // Tokyo, Japan (JST - No DST)
// String timezone_string = "Asia/Seoul"; // Seoul, South Korea (KST - No DST)
// String timezone_string = "Asia/Singapore"; // Singapore (SGT - No DST)
// String timezone_string = "Asia/Bangkok"; // Bangkok, Thailand (ICT - No DST)
// ------------------------------------------------------------
// String timezone_string = "Europe/London"; // London, UK (GMT/BST)
// String timezone_string = "Europe/Paris"; // Paris, France (CET/CEST)
// String timezone_string = "Europe/Berlin"; // Berlin, Germany (CET/CEST)
// String timezone_string = "Europe/Madrid"; // Madrid, Spain (CET/CEST)
// String timezone_string = "Europe/Rome"; // Rome, Italy (CET/CEST)
// String timezone_string = "Europe/Amsterdam"; // Amsterdam, Netherlands (CET/CEST)
// String timezone_string = "Europe/Brussels"; // Brussels, Belgium (CET/CEST)
// String timezone_string = "Europe/Stockholm"; // Stockholm, Sweden (CET/CEST)
// String timezone_string = "Europe/Oslo"; // Oslo, Norway (CET/CEST)
// String timezone_string = "Europe/Copenhagen"; // Copenhagen, Denmark (CET/CEST)
// String timezone_string = "Europe/Vienna"; // Vienna, Austria (CET/CEST)
// String timezone_string = "Europe/Zurich"; // Zurich, Switzerland (CET/CEST)
// String timezone_string = "Europe/Helsinki"; // Helsinki, Finland (EET/EEST)
// String timezone_string = "Europe/Athens"; // Athens, Greece (EET/EEST)
// String timezone_string = "Atlantic/Reykjavik"; // Reykjavik, Iceland (GMT - No DST)
// ------------------------------------------------------------

// Timezone Offset, if timezone_string is not set
// Do not bother to comment out, it's overwritten by timezone_string
int timeZone = -7;
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

// Warn if not Inkplate6PLUS or Inkplate6FLICK
#if !(defined(ARDUINO_INKPLATE6PLUS) || defined(ARDUINO_INKPLATE6PLUSV2) || defined(ARDUINO_INKPLATE6FLICK))
#error "Error: This program can only run on supported Inkplate models (6PLUS, 6PLUSV2, 6FLICK)."
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
    #ifdef ARDUINO_INKPLATE6PLUS
        // Optional: Uncomment if using USB-only powered Inkplate 6PLUS
        // display.setInkplatePowerMode(INKPLATE_USB_PWR_ONLY);
    #endif

    display.begin();
    Serial.begin(115200);
    display.frontlight(0);
    display.setRotation(rotation);

    // Re-initialize touchscreen after wake from deep sleep
    if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER) {
        if (!display.tsInit(true)) {
            Serial.println("Touchscreen re-init failed after wake.");
        }
    }

    #ifdef ARDUINO_INKPLATE6PLUS
        display.setIntOutput(1, false, false, HIGH);
        display.setIntPin(PAD1, RISING, IO_INT_ADDR);
        display.setIntPin(PAD2, RISING, IO_INT_ADDR);
        display.setIntPin(PAD3, RISING, IO_INT_ADDR);
    #elif defined(ARDUINO_INKPLATE6PLUSV2)
        display.setIntPin(PAD1, IO_INT_ADDR);
        display.setIntPin(PAD2, IO_INT_ADDR);
        display.setIntPin(PAD3, IO_INT_ADDR);
    #elif defined(ARDUINO_INKPLATE6FLICK)
        // No MCP interrupt setup needed
    #endif

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

    // Debugging Information
    Serial.println("Hour of day: " + String(hours));
    Serial.println("Voltage: " + String(voltage, 2) + "V, Powered: " + String(powered) + ", Temp: " + String(temp));

    // Battery Percentage Calculation
    battery_percent = ((voltage - battery_min) / (battery_max - battery_min)) * 100;
    battery_percent = constrain(battery_percent, 0.0, 100.0);  // Clamp to 0–100%

    battery_is_below_threshold = (battery_percent < battery_threshold) ? 1 : 0;
    Serial.println("Battery below threshold: " + String(battery_is_below_threshold));

    // Dynamic Icon Fill Calculation
    rect02_b_x = 774 + (battery_percent / 4);  // Adjust fill width (774–799)

    // Charging Status
    if (powered == 255) charging = "+";
    if (battery_percent == 100) charging = "";

    // Display Battery Percentage or Temperature
    if (show_temperature) {
        show_battery_percent = 1;
        if (temp_in_f) temp = temp * 9.0 / 5.0 + 32;  // Convert to Fahrenheit if needed
        text0_content = " " + String(temp, 0) + " " + (temp_in_f ? "F" : "C");
    } else {
        text0_content = charging + String(battery_percent, 0) + "%";
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
      if (digital_clock0_h == 0) digital_clock0_h = 12;
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
    } else {
        Serial.println("Touchscreen disabled for 10 minutes");

        // Shut down touchscreen to save power
        display.tsShutdown();

        // Enable wake-up sources
        esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
        esp_sleep_enable_ext0_wakeup(GPIO_NUM_36, 0); // Wake button

        #ifdef ARDUINO_INKPLATE6FLICK
            // Use GPIO_34 (touchpad INT) for wakeup
            esp_sleep_enable_ext1_wakeup((1LL << GPIO_NUM_34), ESP_EXT1_WAKEUP_ALL_LOW);
            display.tsSetPowerState(CYPRESS_TOUCH_DEEP_SLEEP_MODE); // Save power
        #elif defined(ARDUINO_INKPLATE6PLUSV2)
            // 6PLUS V2 uses ALL_LOW wake condition
            esp_sleep_enable_ext1_wakeup((1LL << GPIO_NUM_34), ESP_EXT1_WAKEUP_ALL_LOW);
        #else
            // Standard wake-up for 6PLUS V1
            esp_sleep_enable_ext1_wakeup((1LL << GPIO_NUM_34), ESP_EXT1_WAKEUP_ANY_HIGH);
        #endif

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

    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
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
