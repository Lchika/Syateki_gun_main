/**
 * @file display.hpp
 * @brief 画面表示クラス
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <Adafruit_SSD1331.h>

// This could also be defined as display.color(255,0,0) but those defines
// are meant to work for adafruit_gfx backends that are lacking color()
#define LED_BLACK		0

#define LED_RED_VERYLOW 	(3 <<  11)
#define LED_RED_LOW 		(7 <<  11)
#define LED_RED_MEDIUM 		(15 << 11)
#define LED_RED_HIGH 		(31 << 11)

#define LED_GREEN_VERYLOW	(1 <<  5)   
#define LED_GREEN_LOW 		(15 << 5)  
#define LED_GREEN_MEDIUM 	(31 << 5)  
#define LED_GREEN_HIGH 		(63 << 5)  

#define LED_BLUE_VERYLOW	3
#define LED_BLUE_LOW 		7
#define LED_BLUE_MEDIUM 	15
#define LED_BLUE_HIGH 		31

#define LED_ORANGE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW		(LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW	(LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW		(LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM	(LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH		(LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW	(LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW		(LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM		(LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH		(LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW		(LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM	(LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)

/**
 * @class Display
 * @brief
 */
class Display {
private:
  /*
  SD1331 Pin	    Arduino	ESP8266		rPi
  1 GND
  2 VCC
  3 SCL/SCK/CLK/D0	13	GPIO14/D5	GPIO11/SPI0-SCLK	
  4 SDA/MOSI/D1		11	GPIO13/D7	GPIO10/SPI0-MOSI	
  5 RES/RST		9	GPIO15/D8	GPIO24			
  6 DC/A0 (data)		8	GPIO05/D1	GPIO23			
  7 CS			10	GPIO04/D2	GPIO08		
  */
  // You can use any (4 or) 5 pins
  // hwspi hardcodes those pins, no need to redefine them
  static int8_t constexpr sclk = 18;
  static int8_t constexpr mosi = 23;
  static int8_t constexpr cs = 5;
  static int8_t constexpr rst = 4;
  static int8_t constexpr dc = 21;
  //#pragma message "Using SWSPI"
  Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);
  // Option 2: must use the hardware SPI pins
  // (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
  // an output. This is much faster - also required if you want
  // to use the microSD card (see the image drawing example)
  //#pragma message "Using HWSPI"
  //Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);
  static uint8_t constexpr TEXT_SIZE = 6;
  void print(int16_t x, int16_t y, uint8_t font_size, uint16_t color, const String& msg);

public:
  Display();
  void show_int(int16_t x, int16_t y, int disp_num, uint8_t font_size, uint16_t color = LED_CYAN_HIGH);
  void show_int_on_column(uint8_t column, uint8_t column_width, uint8_t max_columns,
    int16_t margin_x, int16_t margin_y, uint8_t font_size, int16_t disp_num, uint16_t color = LED_CYAN_HIGH);
  void clear_display();
  void show_msg(int16_t x, int16_t y, uint8_t font_size, const String& msg, uint16_t color = LED_ORANGE_HIGH);
  void show_important_msg(int16_t x, int16_t y, uint8_t font_size, const String& msg);
  void show_msg_on_column(uint8_t column, uint8_t column_width, uint8_t max_columns,
    int16_t margin_x, int16_t margin_y, uint8_t font_size, const String& msg, uint16_t color = LED_ORANGE_HIGH);
  void show_column_frame(uint8_t width, uint8_t columns, uint16_t color);
  void clear_column_vertical(uint8_t column, uint8_t column_width, uint8_t max_columns,
    int16_t y, bool isUpper = false);
};

#endif