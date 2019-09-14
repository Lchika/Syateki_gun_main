/**
 * @file display.hpp
 * @brief 画面表示クラス
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include <Adafruit_SSD1331.h>

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

public:
  Display();
  void show_int(int16_t x, int16_t y, int disp_num);
};

#endif