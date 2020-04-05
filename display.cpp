// copy from "GFX Demo for multiple backends"
// By Marc MERLIN <marc_soft@merlins.org>
// Contains code (c) Adafruit, license BSD

#include <Adafruit_GFX.h>
#include <SPI.h>

#define show endWrite
#define clear() fillScreen(0)
#define mw 96
#define mh 64

#include "display.hpp"

Display::Display(){
  //delay(1000);
  // Default is 40Mhz
  display.begin(40000000);
  Serial.println("For extra speed, try 80Mhz, may be less stable");
  //display.begin(80000000);
  display.setTextWrap(false);
  display.setAddrWindow(0, 0, mw, mh);
  // Test full bright of all LEDs. If brightness is too high
  // for your current limit (i.e. USB), decrease it.
  //display.fillScreen(LED_WHITE_HIGH);
  //display.show();
  //delay(3000);
  display.clear();
};

void Display::show_int(int16_t x, int16_t y, int disp_num, uint8_t font_size, uint16_t color){
  display.setCursor(x, y);
  display.setTextColor(color);
  display.setTextSize(font_size);
  display.print(disp_num);
}

void Display::clear_display(){
  display.clear();
}

void Display::print(int16_t x, int16_t y, uint8_t font_size, uint16_t color, const String& msg){
  display.setCursor(x, y);
  display.setTextColor(color);
  display.setTextSize(font_size);
  display.print(msg);
}

void Display::show_msg(int16_t x, int16_t y, uint8_t font_size, const String& msg, uint16_t color){
  print(x, y, font_size, color, msg);
}

void Display::show_important_msg(int16_t x, int16_t y, uint8_t font_size, const String& msg){
  print(x, y, font_size, LED_RED_HIGH, msg);
}

void Display::show_column_frame(uint8_t width, uint8_t columns, uint16_t color)
{
  display.fillRect(0, 0, mw, width, color);
  display.fillRect(0, mh - width, mw, mh, color);
  display.fillRect(0, 0, width, mh, color);
  display.fillRect(mw - width, 0, mw, mh, color);
  for(int i = 1; i < columns; i++){
    uint8_t offset_x = i * ((mw - (1 + columns) * width) / columns);
    display.fillRect(offset_x, 0, width, mh, color);
  }
}

void Display::show_msg_on_column(uint8_t column, uint8_t column_width, uint8_t max_columns,
  int16_t margin_x, int16_t margin_y, uint8_t font_size, const String& msg, uint16_t color)
{
  show_msg(column_width + column * ((mw - (1 + max_columns) * column_width) / max_columns) + margin_x,
    column_width + margin_y, font_size, msg, color);
}

void Display::show_int_on_column(uint8_t column, uint8_t column_width, uint8_t max_columns,
  int16_t margin_x, int16_t margin_y, uint8_t font_size, int16_t disp_num, uint16_t color)
{
  show_int(column_width + column * ((mw - (1 + max_columns) * column_width) / max_columns) + margin_x,
    column_width + margin_y, disp_num, font_size, color);
}

void Display::clear_column_vertical(uint8_t column, uint8_t column_width, uint8_t max_columns,
  int16_t y, bool isUpper)
{
  int16_t _y = column_width + y;
  int16_t _h = mh - (1 + max_columns) * column_width - y;
  if(isUpper){
    _y = 0;
    _h = y;
  }
  display.fillRect(column_width + column * ((mw - (1 + max_columns) * column_width) / max_columns),
    _y, ((mw - (1 + max_columns) * column_width) / max_columns) - 2, _h, 0); // なぜかwを2引かないと消しすぎる
}