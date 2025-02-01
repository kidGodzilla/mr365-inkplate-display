/*
   Meeting Room 365 E-ink Display App -- Generated UI
   (c) 2022 James Futhey. All Rights Reserved.

   This file is a bit messy because parts of it were automatically generated
*/
#include "Arduino.h"
#include "Inkplate.h"
//#include "Fonts/FreeSansBold48pt7b.h"
#include "Fonts/FreeSansBold36pt7b.h"
#include "Fonts/FreeSansBold24pt7b.h"
#include "Fonts/FreeSansBold18pt7b.h"
#include "Fonts/FreeSansBold12pt7b.h"
#include "Fonts/FreeSans12pt7b.h"
#include "icon.h"

extern Inkplate display;

extern int show_battery_percent;
extern int battery_icon_offset;
extern int show_battery_icon;
extern int use_digital_clock;
extern int show_reserve_btn;
extern int show_extend_btn;
extern int show_end_btn;
extern int please_wait;
extern int sleeping;
extern int occupied;
extern int rotation;
extern String end_meeting;
extern String grab_room;
extern String extend;

int rect0_a_x = 0;
int rect0_a_y = 0;
int rect0_b_x = 761;
int rect0_b_y = 760;
int rect0_fill = 1;
int rect0_radius = -1;
int rect0_color = 0;
int main_text_color = 7;
int portrait = 0;

// Battery percent
String text0_content = "";
int text0_cursor_x = 955;
int text0_cursor_y = 28;
const GFXfont *text0_font = &FreeSansBold12pt7b;

String text1_content = ""; // Room Name
int text1_cursor_x = 50;
int text1_cursor_y = 100;
const GFXfont *text1_font = &FreeSansBold24pt7b;

int digital_clock0_h = 0;
int digital_clock0_m = 0;
int digital_clock0_location_x = 820;
int digital_clock0_location_y = 72;
int digital_clock0_size = 48;
int digital_clock0_bitmask[] = {119, 48, 93, 121, 58, 107, 111, 49, 127, 59};
int digital_clock0_triangleX[] = {83, 101, 108, 101, 108, 277, 101, 108, 277, 257, 277, 108, 257, 277, 286, 76, 60, 98, 60, 98, 80, 80, 39, 60, 80, 39, 55, 31, 55, 73, 31, 73, 52, 31, 9, 52, 9, 52, 20, 61, 86, 80, 86, 80, 233, 233, 227, 80, 233, 227, 252, 260, 292, 305, 305, 260, 240, 305, 281, 240, 240, 281, 260, 259, 234, 276, 234, 276, 256, 256, 214, 234, 214, 256, 237, 38, 27, 60, 38, 60, 207, 207, 38, 212, 212, 207, 230};
int digital_clock0_triangleY[] = {30, 13, 60, 13, 60, 14, 13, 60, 14, 57, 14, 60, 57, 14, 29, 36, 47, 61, 47, 61, 198, 198, 201, 47, 198, 201, 219, 252, 232, 253, 252, 253, 390, 252, 406, 390, 406, 390, 416, 227, 202, 249, 202, 249, 203, 203, 247, 249, 203, 247, 224, 60, 35, 49, 49, 60, 200, 50, 201, 200, 200, 201, 220, 231, 252, 252, 252, 252, 403, 403, 390, 252, 390, 403, 415, 439, 424, 392, 439, 392, 394, 394, 439, 439, 439, 394, 424};
int digital_clock0_maxX = 310;
int digital_clock0_maxY = 440;

String text2_content = ""; // Status: AVAILABLE or OCCUPIED 
int text2_cursor_x = 50;
int text2_cursor_y = 150;
const GFXfont *text2_font = &FreeSansBold12pt7b;

int rect1_a_x = 770;
int rect1_a_y = 390;
int rect1_b_x = 1015;
int rect1_b_y = 490;
int rect1_fill = 1;
int rect1_radius = -1;
int rect1_color = 6;

String text3_content = end_meeting;
int text3_cursor_x = 818;
int text3_cursor_y = 449;
const GFXfont *text3_font = &FreeSansBold12pt7b;

int rect2_a_x = 770;
int rect2_a_y = 282;
int rect2_b_x = 1015;
int rect2_b_y = 382;
int rect2_fill = 1;
int rect2_radius = -1;
int rect2_color = 6;

String text4_content = extend;
int text4_cursor_x = 850;
int text4_cursor_y = 341;
const GFXfont *text4_font = &FreeSansBold12pt7b;

String text5_content = ""; // Current meeting subject
String text5b_content = "";
String text5c_content = "";
int text5_cursor_x = 50;
int text5_cursor_y = 346;
int text5b_cursor_y = 436;
int text5c_cursor_x = 800;
int text5c_cursor_y = 127;
//const GFXfont *text5_font = &FreeSansBold48pt7b;
const GFXfont *text5_font = &FreeSansBold36pt7b;

String text6_content = ""; // Current meeting time
int text6_cursor_x = 50;
int text6_cursor_y = 260;
const GFXfont *text6_font = &FreeSans12pt7b;

String text7_content = "Next Meeting";
int text7_cursor_x = 50;
int text7_cursor_y = 570;
const GFXfont *text7_font = &FreeSansBold18pt7b;

String text8_content = ""; // Next meeting subject
int text8_cursor_x = 50;
int text8_cursor_y = 650;
const GFXfont *text8_font = &FreeSansBold24pt7b;

String text9_content = ""; // Next meeting times
int text9_cursor_x = 50;
int text9_cursor_y = 720;
const GFXfont *text9_font = &FreeSansBold12pt7b;

int rect3_a_x = 0;
int rect3_a_y = 500;
int rect3_b_x = 761;
int rect3_b_y = 760;
int rect3_fill = 1;
int rect3_radius = -1;
int rect3_color = 1;

int rect4_a_x = 770;
int rect4_a_y = 182;
int rect4_b_x = 1015;
int rect4_b_y = 282;
int rect4_fill = 1;
int rect4_radius = -1;
int rect4_color = 6;

String text10_content = grab_room;
int text10_cursor_x = 824;
int text10_cursor_y = 242;
const GFXfont *text10_font = &FreeSansBold12pt7b;

int widget1_h = 0;
int widget1_m = 0;
int widget1_center_x = 893;
int widget1_center_y = 94;
int widget1_size = 128;
int widget1_r0 = (double)widget1_size / 2 * 0.55;
int widget1_r1 = (double)widget1_size / 2 * 0.65;
int widget1_r2 = (double)widget1_size / 2 * 0.9;
int widget1_r3 = (double)widget1_size / 2 * 1.0;

// Variables for battery icon
int rect00_a_x = 770;
int rect00_a_y = 10;
int rect00_b_x = 802;
int rect00_b_y = 28;
int rect00_fill = -1;
int rect01_fill = 1;
int rect00_radius = 2;
int rect00_color = 0;
int rect01_color = 2;
int rect01_a_x = 802;
int rect01_a_y = 14;
int rect01_b_x = 807;
int rect01_b_y = 24;
int rect02_a_x = 773;
int rect02_a_y = 13;
int rect02_b_x = 799;
int rect02_b_y = 25;

// Sleep message, Triangle button indicator
String texts0_content = "Press Wake";
int texts0_cursor_x = 824;
int texts0_cursor_y = 282;
const GFXfont *texts0_font = &FreeSansBold12pt7b;

String texts1_content = "Button for";
int texts1_cursor_x = 833;
int texts1_cursor_y = 322;

String texts2_content = "More Options";
int texts2_cursor_x = 812;
int texts2_cursor_y = 362;

String texts3_content = "(Left Edge)";
int texts3_cursor_x = 829;
int texts3_cursor_y = 402;

int triangle0_a_x = 20;
int triangle0_a_y = 520;
int triangle0_b_x = 20;
int triangle0_b_y = 540;
int triangle0_c_x = 0;
int triangle0_c_y = 530;
int triangle0_fill = 1;
int triangle0_radius = -1;
int triangle0_color = 7;

void mainDraw() {
    if (occupied == 1) {
        Serial.println("Room occupied, dark bg");
        main_text_color = 7;
        rect0_color = 0;
    } else {
        Serial.println("Room available, light bg");
        main_text_color = 0;
        rect0_color = 6;
    }

    // Portrait Mode
    if (rotation == 1 || rotation == 3) { 
        portrait = 1;
        
        // Battery percent
        text0_cursor_x = 955 - 260;
        text0_cursor_y = 28 - 1;
    
        // Digital clock 1
        digital_clock0_location_x = 820 - 260;
        digital_clock0_location_y = 72 + 5;
    
        // Digital clock 2
        text5c_cursor_x = 800 - 260;
        text5c_cursor_y = 127 + 5;
    
        // Analog clock
        widget1_center_x = 893 - 225;
        widget1_center_y = 94 + 36;
    
        // Grab room
        rect4_a_x = 770 - 270;
        rect4_a_y = 182 + 590;
        rect4_b_x = 1015 - 270;
        rect4_b_y = 282 + 590;
        text10_cursor_x = 824 - 270;
        text10_cursor_y = 242 + 590;
    
        // End meeting
        rect1_a_x = 770 - 270;
        rect1_a_y = 390 + 500 + 10;
        rect1_b_x = 1015 - 270;
        rect1_b_y = 490 + 500 + 10;
        text3_cursor_x = 818 - 270;
        text3_cursor_y = 449 + 500 + 10;
    
        // Extend meeting
        rect2_a_x = 770 - 270;
        rect2_a_y = 282 + 500;
        rect2_b_x = 1015 - 270;
        rect2_b_y = 382 + 500;
        text4_cursor_x = 850 - 270;
        text4_cursor_y = 341 + 500;
    
        // Battery icon
        rect00_a_x = 770 - 260 + 140;
        rect00_a_y = 10;
        rect00_b_x = 802 - 260 + 140;
        rect00_b_y = 28;
        rect01_a_x = 802 - 260 + 140;
        rect01_a_y = 14;
        rect01_b_x = 807 - 260 + 140;
        rect01_b_y = 24;
        rect02_a_x = 773 - 260 + 140;
        rect02_a_y = 13;
        rect02_b_x = 799 - 260 + 140;
        rect02_b_y = 25;

        if (occupied == 1) {
            rect00_color = 7;
            rect01_color = 6;
        } else {
            rect00_color = 0;
            rect01_color = 0;
        }
    
        // Sleep message
        texts0_content = "Press Wake";
        texts0_cursor_x = 824 - 260 - 120;
        texts0_cursor_y = 282 + 555;
        texts1_content = "Button for";
        texts1_cursor_x = 833 - 260 - 120;
        texts1_cursor_y = 322 + 555;
        texts2_content = "More Options";
        texts2_cursor_x = 812 - 260 - 120;
        texts2_cursor_y = 362 + 555;
        texts3_content = "(Bottom Edge)";
        texts3_cursor_x = 829 - 260 - 120 - 21;
        texts3_cursor_y = 402 + 555;
    
        // Indicator triangle
        triangle0_a_y = 1000;
        triangle0_a_x = 520 - 6;
        triangle0_b_y = 1000;
        triangle0_b_x = 540 - 6;
        triangle0_c_y = 1020;
        triangle0_c_x = 530 - 6;
        triangle0_color = 1;

        // Logo position
        bitmap0_x = 0;
        bitmap0_y = 760;
    }

    if (please_wait == 0) {
        if (rect0_radius != -1 && rect0_fill != -1)
            display.fillRoundRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_radius, rect0_color);
        else if (rect0_radius != -1 && rect0_fill == -1)
            display.drawRoundRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_radius, rect0_color);
        else if (rect0_radius == -1 && rect0_fill != -1)
            display.fillRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_color);
        else if (rect0_radius == -1 && rect0_fill == -1)
            display.drawRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_color);
    
       
        if (rect3_radius != -1 && rect3_fill != -1)
            display.fillRoundRect(rect3_a_x, rect3_a_y, rect3_b_x - rect3_a_x, rect3_b_y - rect3_a_y, rect3_radius, rect3_color);
        else if (rect3_radius != -1 && rect3_fill == -1)
            display.drawRoundRect(rect3_a_x, rect3_a_y, rect3_b_x - rect3_a_x, rect3_b_y - rect3_a_y, rect3_radius, rect3_color);
        else if (rect3_radius == -1 && rect3_fill != -1)
            display.fillRect(rect3_a_x, rect3_a_y, rect3_b_x - rect3_a_x, rect3_b_y - rect3_a_y, rect3_color);
        else if (rect3_radius == -1 && rect3_fill == -1)
            display.drawRect(rect3_a_x, rect3_a_y, rect3_b_x - rect3_a_x, rect3_b_y - rect3_a_y, rect3_color);
    }

    if (please_wait == 0) {
        display.setFont(text1_font);
        display.setTextColor(main_text_color, 7);    display.setTextSize(1);    display.setCursor(text1_cursor_x, text1_cursor_y);
        display.print(text1_content);
    }

    // Digital Clock
    if (use_digital_clock == 1 && please_wait == 0) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < sizeof(digital_clock0_triangleX) / sizeof(digital_clock0_triangleX[0]); j += 3) {
                int temp[4] = {digital_clock0_h / 10 % 10, digital_clock0_h % 10, digital_clock0_m / 10 % 10, digital_clock0_m % 10};
                int b = digital_clock0_bitmask[temp[i]];
                if (b & (1 << ((j - 1) / (3 * 4)))) {
                    display.fillTriangle(
                        (int)((float)i * (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * 1.1 + (float)digital_clock0_location_x + (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * (float)digital_clock0_triangleX[j + 0] / (float)digital_clock0_maxX),
                        (int)((float)digital_clock0_location_y + (float)digital_clock0_size * (float)digital_clock0_triangleY[j + 0] / (float)digital_clock0_maxY),
    
                        (int)((float)i * (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * 1.1 + (float)digital_clock0_location_x + (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * (float)digital_clock0_triangleX[j + 1] / (float)digital_clock0_maxX),
                        (int)((float)digital_clock0_location_y + (float)digital_clock0_size * (float)digital_clock0_triangleY[j + 1] / (float)digital_clock0_maxY),
    
                        (int)((float)i * (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * 1.1 + (float)digital_clock0_location_x + (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * (float)digital_clock0_triangleX[j + 2] / (float)digital_clock0_maxX),
                        (int)((float)digital_clock0_location_y + (float)digital_clock0_size * (float)digital_clock0_triangleY[j + 2] / (float)digital_clock0_maxY),
    
                        (occupied == 1 && portrait == 1 ? 6 : 0));
                }
            }
        }

        int digital_clock0_r = 0.05 * (float)digital_clock0_size;
    
        display.fillCircle((int)((float)digital_clock0_location_x + 4.0 * (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * 1.075 / 2.0), (int)((float)digital_clock0_location_y + (float)digital_clock0_size * 0.4), digital_clock0_r, (occupied == 1 && portrait == 1 ? 6 : 0));
        display.fillCircle((int)((float)digital_clock0_location_x + 4.0 * (float)digital_clock0_maxX / (float)digital_clock0_maxY * (float)digital_clock0_size * 1.075 / 2.0), (int)((float)digital_clock0_location_y + (float)digital_clock0_size * 0.6), digital_clock0_r, (occupied == 1 && portrait == 1 ? 6 : 0));
    }

    if (please_wait == 0) {
        display.setFont(text2_font);
        display.setTextColor(main_text_color, 7);    display.setTextSize(1);    display.setCursor(text2_cursor_x, text2_cursor_y);
        display.print(text2_content);
    }

    if (show_end_btn == 1) {
        if (rect1_radius != -1 && rect1_fill != -1)
            display.fillRoundRect(rect1_a_x, rect1_a_y, rect1_b_x - rect1_a_x, rect1_b_y - rect1_a_y, rect1_radius, rect1_color);
        else if (rect1_radius != -1 && rect1_fill == -1)
            display.drawRoundRect(rect1_a_x, rect1_a_y, rect1_b_x - rect1_a_x, rect1_b_y - rect1_a_y, rect1_radius, rect1_color);
        else if (rect1_radius == -1 && rect1_fill != -1)
            display.fillRect(rect1_a_x, rect1_a_y, rect1_b_x - rect1_a_x, rect1_b_y - rect1_a_y, rect1_color);
        else if (rect1_radius == -1 && rect1_fill == -1)
            display.drawRect(rect1_a_x, rect1_a_y, rect1_b_x - rect1_a_x, rect1_b_y - rect1_a_y, rect1_color);
  
        display.setFont(text3_font);
        display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(text3_cursor_x, text3_cursor_y);
        display.print(text3_content);
    }

    if (show_extend_btn == 1) {
        if (rect2_radius != -1 && rect2_fill != -1)
            display.fillRoundRect(rect2_a_x, rect2_a_y, rect2_b_x - rect2_a_x, rect2_b_y - rect2_a_y, rect2_radius, rect2_color);
        else if (rect2_radius != -1 && rect2_fill == -1)
            display.drawRoundRect(rect2_a_x, rect2_a_y, rect2_b_x - rect2_a_x, rect2_b_y - rect2_a_y, rect2_radius, rect2_color);
        else if (rect2_radius == -1 && rect2_fill != -1)
            display.fillRect(rect2_a_x, rect2_a_y, rect2_b_x - rect2_a_x, rect2_b_y - rect2_a_y, rect2_color);
        else if (rect2_radius == -1 && rect2_fill == -1)
            display.drawRect(rect2_a_x, rect2_a_y, rect2_b_x - rect2_a_x, rect2_b_y - rect2_a_y, rect2_color);
    
        display.setFont(text4_font);
        display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(text4_cursor_x, text4_cursor_y);
        display.print(text4_content);
    }

    if (please_wait == 0) {
        display.drawBitmap3Bit(bitmap0_x, bitmap0_y, bitmap0_content, bitmap0_w, bitmap0_h);
    }
    
    display.setFont(text5_font);
    display.setTextColor((please_wait == 0 ? main_text_color : 0), 7);    display.setTextSize(1);    display.setCursor(text5_cursor_x, (please_wait == 0 ? text5_cursor_y : (text5_cursor_y + 40)));
    display.print(text5_content);
    
    display.setFont(text5_font);
    display.setTextColor(main_text_color, 7);    display.setTextSize(1);    display.setCursor(text5_cursor_x, text5b_cursor_y);
    display.print(text5b_content);

    if (use_digital_clock == 2 && please_wait == 0) {
        display.setFont(text5_font);
        display.setTextColor(((occupied == 1 && portrait == 1) ? 6 : 0), 7);    display.setTextSize(1);    display.setCursor(text5c_cursor_x, text5c_cursor_y);
        display.print(text5c_content);
    }

    if (please_wait == 0) {
        display.setFont(text6_font);
        display.setTextColor(main_text_color, 7);    display.setTextSize(1);    display.setCursor(text6_cursor_x, text6_cursor_y);
        display.print(text6_content);
        
        display.setFont(text7_font);
        display.setTextColor(7, 7);    display.setTextSize(1);    display.setCursor(text7_cursor_x, text7_cursor_y);
        display.print(text7_content);
    
        display.setFont(text8_font);
        display.setTextColor(7, 7);    display.setTextSize(1);    display.setCursor(text8_cursor_x, text8_cursor_y);
        display.print(text8_content);
    
        display.setFont(text9_font);
        display.setTextColor(7, 7);    display.setTextSize(1);    display.setCursor(text9_cursor_x, text9_cursor_y);
        display.print(text9_content);
    }

    if (show_reserve_btn == 1) {
        if (rect4_radius != -1 && rect4_fill != -1)
            display.fillRoundRect(rect4_a_x, rect4_a_y, rect4_b_x - rect4_a_x, rect4_b_y - rect4_a_y, rect4_radius, rect4_color);
        else if (rect4_radius != -1 && rect4_fill == -1)
            display.drawRoundRect(rect4_a_x, rect4_a_y, rect4_b_x - rect4_a_x, rect4_b_y - rect4_a_y, rect4_radius, rect4_color);
        else if (rect4_radius == -1 && rect4_fill != -1)
            display.fillRect(rect4_a_x, rect4_a_y, rect4_b_x - rect4_a_x, rect4_b_y - rect4_a_y, rect4_color);
        else if (rect4_radius == -1 && rect4_fill == -1)
            display.drawRect(rect4_a_x, rect4_a_y, rect4_b_x - rect4_a_x, rect4_b_y - rect4_a_y, rect4_color);
    
        display.setFont(text10_font);
        display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(text10_cursor_x, text10_cursor_y);
        display.print(text10_content);
    }

    if (sleeping == 1) {
        display.setFont(texts0_font);
        display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(texts0_cursor_x, texts0_cursor_y);
        display.print(texts0_content);
    
        display.setFont(texts0_font);
        display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(texts1_cursor_x, texts1_cursor_y);
        display.print(texts1_content);
    
        display.setFont(texts0_font);
        display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(texts2_cursor_x, texts2_cursor_y);
        display.print(texts2_content);
    
        display.setFont(texts0_font);
        display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(texts3_cursor_x, texts3_cursor_y);
        display.print(texts3_content);

        if (rotation == 1 || rotation == 4) {
            if (triangle0_fill != -1)
                display.fillTriangle(triangle0_a_x, triangle0_a_y, triangle0_b_x, triangle0_b_y, triangle0_c_x, triangle0_c_y, triangle0_color);
            else
                display.drawTriangle(triangle0_a_x, triangle0_a_y, triangle0_b_x, triangle0_b_y, triangle0_c_x, triangle0_c_y, triangle0_color);
        }
    }

    // Analogue Clock
    if (use_digital_clock == 0 && please_wait == 0) {
        for (int i = 0; i < 60; ++i) {
            if (i % 5 == 0)
                display.drawThickLine(widget1_center_x + widget1_r1 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                    widget1_center_y + widget1_r1 * sin((double)i / 60.0 * 2.0 * 3.14159265),
                    widget1_center_x + widget1_r3 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                    widget1_center_y + widget1_r3 * sin((double)i / 60.0 * 2.0 * 3.14159265), ((occupied == 1 && portrait == 1) ? 6 : 0), 3);
            else if (widget1_size > 150)
                display.drawLine(widget1_center_x + widget1_r1 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                    widget1_center_y + widget1_r1 * sin((double)i / 60.0 * 2.0 * 3.14159265),
                    widget1_center_x + widget1_r2 * cos((double)i / 60.0 * 2.0 * 3.14159265),
                    widget1_center_y + widget1_r2 * sin((double)i / 60.0 * 2.0 * 3.14159265), ((occupied == 1 && portrait == 1) ? 6 : 0));
         }
         
         display.drawThickLine(widget1_center_x, widget1_center_y,
             widget1_center_x + widget1_r0 * cos((double)(widget1_h - 3.0 + widget1_m / 60.0) / 12.0 * 2.0 * 3.14159265),
             widget1_center_y + widget1_r0 * sin((double)(widget1_h - 3.0 + widget1_m / 60.0) / 12.0 * 2.0 * 3.14159265), ((occupied == 1 && portrait == 1) ? 6 : 0), 2);
       
         display.drawThickLine(widget1_center_x, widget1_center_y,
             widget1_center_x + widget1_r2 * cos((double)(widget1_m - 15.0) / 60.0 * 2.0 * 3.14159265),
             widget1_center_y + widget1_r2 * sin((double)(widget1_m - 15.0) / 60.0 * 2.0 * 3.14159265), ((occupied == 1 && portrait == 1) ? 6 : 0), 2);
    }

    // Battery voltage
    if (show_battery_percent == 1 && please_wait == 0) {
        display.setFont(text0_font);
        display.setTextColor((portrait == 1 && occupied == 1) ? 6 : 1, 7);    display.setTextSize(1);    display.setCursor(text0_cursor_x, text0_cursor_y);
        display.print(text0_content);
    }
    
    // Battery Icon
    if (show_battery_icon == 1 && please_wait == 0) {
        if (rect00_radius != -1 && rect00_fill != -1)
            display.fillRoundRect(rect00_a_x + battery_icon_offset, rect00_a_y, rect00_b_x - rect00_a_x, rect00_b_y - rect00_a_y, rect00_radius, rect00_color);
        else if (rect00_radius != -1 && rect00_fill == -1) {
            display.drawRoundRect(rect00_a_x + battery_icon_offset, rect00_a_y, rect00_b_x - rect00_a_x, rect00_b_y - rect00_a_y, rect00_radius, rect00_color);
            display.drawRoundRect(rect00_a_x - 1 + battery_icon_offset, rect00_a_y - 1, rect00_b_x - rect00_a_x + 2, rect00_b_y - rect00_a_y + 2, rect00_radius, rect00_color); // Double outline
        } else if (rect00_radius == -1 && rect00_fill != -1)
            display.fillRect(rect00_a_x + battery_icon_offset, rect00_a_y, rect00_b_x - rect00_a_x, rect00_b_y - rect00_a_y, rect00_color);
        else if (rect00_radius == -1 && rect00_fill == -1)
            display.drawRect(rect00_a_x + battery_icon_offset, rect00_a_y, rect00_b_x - rect00_a_x, rect00_b_y - rect00_a_y, rect00_color);
    
        if (rect00_radius != -1 && rect01_fill != -1)
            display.fillRoundRect(rect01_a_x + battery_icon_offset, rect01_a_y, rect01_b_x - rect01_a_x, rect01_b_y - rect01_a_y, rect00_radius, rect01_color);
        else if (rect00_radius != -1 && rect01_fill == -1)
            display.drawRoundRect(rect01_a_x + battery_icon_offset, rect01_a_y, rect01_b_x - rect01_a_x, rect01_b_y - rect01_a_y, rect00_radius, rect01_color);
        else if (rect00_radius == -1 && rect01_fill != -1)
            display.fillRect(rect01_a_x + battery_icon_offset, rect01_a_y, rect01_b_x - rect01_a_x, rect01_b_y - rect01_a_y, rect00_color);
        else if (rect00_radius == -1 && rect01_fill == -1)
            display.drawRect(rect01_a_x + battery_icon_offset, rect01_a_y, rect01_b_x - rect01_a_x, rect01_b_y - rect01_a_y, rect00_color);

        if (rect00_radius != -1 && rect01_fill != -1)
            display.fillRoundRect(rect02_a_x + battery_icon_offset, rect02_a_y, rect02_b_x - rect02_a_x, rect02_b_y - rect02_a_y, rect00_radius, rect01_color);
        else if (rect00_radius != -1 && rect01_fill == -1)
            display.drawRoundRect(rect02_a_x + battery_icon_offset, rect02_a_y, rect02_b_x - rect02_a_x, rect02_b_y - rect02_a_y, rect00_radius, rect01_color);
        else if (rect00_radius == -1 && rect01_fill != -1)
            display.fillRect(rect02_a_x + battery_icon_offset, rect02_a_y, rect02_b_x - rect02_a_x, rect02_b_y - rect02_a_y, rect00_color);
        else if (rect00_radius == -1 && rect01_fill == -1)
            display.drawRect(rect02_a_x + battery_icon_offset, rect02_a_y, rect02_b_x - rect02_a_x, rect02_b_y - rect02_a_y, rect00_color);
    }
    
}
