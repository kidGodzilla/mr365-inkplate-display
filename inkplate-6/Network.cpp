/*
Network.cpp
Inkplate 6 Arduino library
David Zovko, Borna Biro, Denis Vajak, Zvonimir Haramustek @ e-radionica.com
September 24, 2020
https://github.com/e-radionicacom/Inkplate-6-Arduino-library

For support, please reach over forums: forum.e-radionica.com/en
For more info about the product, please check: www.inkplate.io

This code is released under the GNU Lesser General Public License v3.0: https://www.gnu.org/licenses/lgpl-3.0.en.html
Please review the LICENSE file included with this example.
If you have any questions about licensing, please contact techsupport@e-radionica.com
Distributed as-is; no warranty is given.
*/

#include "Network.h"

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>

//#include "Inkplate.h"
#include <ArduinoJson.h>

extern char displayKey[];
extern String text1_content;
extern String text2_content;
extern String text6_content;
extern String text5_content;
extern String text5b_content;
extern String text7_content;
extern String text8_content;
extern String text9_content;
extern String timezone_string;
extern int show_reserve_btn;
extern int show_extend_btn;
extern int main_text_color;
extern int show_end_btn;
extern int rect0_color;
extern String voltstr;
extern int twentyfour;
extern int occupied;
extern int timeZone;
extern int action;
extern int hours;


// Static Json from ArduinoJson library
StaticJsonDocument<30000> doc;

void Network::begin() {
    // Initiating wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);

    int cnt = 0;
    Serial.print(F("Waiting for WiFi to connect..."));
    while ((WiFi.status() != WL_CONNECTED))
    {
        Serial.print(F("."));
        delay(1000);
        ++cnt;

        WiFi.reconnect();
        delay(5000);

        if (cnt == 10)
        {
            Serial.println("Can't connect to WIFI, restarting");
            delay(100);
            ESP.restart();
        }
    }
    Serial.println(F(" connected"));

    // Find internet time
    setTime();
}

void Network::getHours(char *timeStr) {
    // Get seconds since 1.1.1970.
    time_t nowSecs = time(nullptr);

    // Used to store time
    struct tm timeinfo;
    gmtime_r(&nowSecs, &timeinfo);

    // Copies time string into timeStr
    strncpy(timeStr, asctime(&timeinfo) + 11, 5);

    // Setting time string timezone
    int hr = 10 * timeStr[0] + timeStr[1] + timeZone;

    // Better defined modulo, in case timezone makes hours to go below 0
    hr = (hr % 24 + 24) % 24;
    
    hours = hr;
}

void Network::getTime(char *timeStr) {
    // Get seconds since 1.1.1970.
    time_t nowSecs = time(nullptr);

    // Used to store time
    struct tm timeinfo;
    gmtime_r(&nowSecs, &timeinfo);

    // Copies time string into timeStr
    strncpy(timeStr, asctime(&timeinfo) + 11, 5);

    // Setting time string timezone
    int hr = 10 * timeStr[0] + timeStr[1] + timeZone;

    // Better defined modulo, in case timezone makes hours to go below 0
    hr = (hr % 24 + 24) % 24;
    
    hours = hr;

    if (twentyfour == 0 && hr > 12) {
      hr -= 12;
    }

    // Adding time to '0' char makes it into whatever time char, for both digits
    timeStr[0] = hr / 10 + '0';
    timeStr[1] = hr % 10 + '0';
}

// Function to get display data from web
bool Network::getData() {
    // Variable to store fail
    bool f = 0;

    // If not connected to wifi reconnect wifi
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.reconnect();

        delay(5000);

        int cnt = 0;
        Serial.println(F("Waiting for WiFi to reconnect..."));
        
        while ((WiFi.status() != WL_CONNECTED)) {
            // Prints a dot every second that wifi isn't connected
            Serial.print(F("."));
            delay(1000);
            ++cnt;

            WiFi.reconnect();
            delay(5000);

            if (cnt == 10) {
                Serial.println("Can't connect to WIFI, restart initiated.");
                delay(100);
                ESP.restart();
            }
        }
    }

    // Http object used to make get request
    HTTPClient http;

    http.getStream().setTimeout(10);
    http.getStream().flush();

    // Begin http by passing url to it
    // http.begin(calendarURL);

    delay(300);

    // Initiate http
    char temp[512];
    sprintf(temp, "https://api.mr365.co/eink/%s?action=%i&voltage=%s", displayKey, action, voltstr);

    Serial.println(temp);

    http.begin(temp);

    // Actually do request
    int httpCode = http.GET();
    if (httpCode == 200) {
        while (http.getStream().available() && http.getStream().peek() != '{')
            (void)http.getStream().read();

        // Try parsing JSON object
        DeserializationError error = deserializeJson(doc, http.getStream());

        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
            f = 1;
            
        } else if (doc.size() > 0) {
            // Set all data got from internet using formatTemp and formatWind defined above
            // This part relies heavily on ArduinoJson library

            Serial.println("Success");

            // Save our data to data pointer from main file
            text1_content = doc["name"].as<String>();
            text2_content = doc["status"].as<String>();
            text6_content = doc["currentMeetingTimeString"].as<String>();
            text5_content = doc["currentMeetingSubjectLine1"].as<String>();
            text5b_content = doc["currentMeetingSubjectLine2"].as<String>();
            text7_content = doc["nextMeetingString"].as<String>();
            text8_content = doc["nextMeetingSubject"].as<String>();
            text9_content = doc["nextMeetingTimeString"].as<String>();
            // show_extend_btn = doc["canExtend"].as<int>();
            // show_end_btn = doc["canEndMeeting"].as<int>();
            // show_reserve_btn = doc["canInstantReserve"].as<int>();
            occupied = doc["occupied"].as<int>();

            if (doc["timezone"] && timezone_string == "") {
              timeZone = doc["timezone"].as<int>();
            }
            if (doc["timezoneString"]) {
              timezone_string = doc["timezoneString"].as<String>();
            }
            if (doc["twentyfour"]) {
              twentyfour = doc["twentyfour"].as<int>();
            }

            Serial.println(occupied);
            Serial.println(text1_content);
            Serial.println(text2_content);
            Serial.println(text6_content);
            Serial.println(text5_content);
            Serial.println(text5b_content);
            Serial.println(text7_content);
            Serial.println(text8_content);
            Serial.println(text9_content);
            Serial.println(show_extend_btn);
            Serial.println(show_end_btn);
            Serial.println(show_reserve_btn);
            f = 0;
        }
    } else {
       f = 1;
    }

    // Clear document and end http
    doc.clear();
    http.end();

    return !f;
}

void Network::setTime() {
    // Used for setting correct time
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    Serial.print(F("Waiting for NTP time sync: "));
    time_t nowSecs = time(nullptr);
    while (nowSecs < 8 * 3600 * 2) {
        delay(500);
        Serial.print(F("."));
        yield();
        nowSecs = time(nullptr);
    }

    Serial.println();

    // Used to store time info
    struct tm timeinfo;
    gmtime_r(&nowSecs, &timeinfo);

    Serial.print(F("Current time: "));
    Serial.print(asctime(&timeinfo));
}
