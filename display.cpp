// copy from "GFX Demo for multiple backends"
// By Marc MERLIN <marc_soft@merlins.org>
// Contains code (c) Adafruit, license BSD

#include <Adafruit_GFX.h>
#include <SPI.h>

#define show endWrite
#define clear() fillScreen(0)
#define mw 96
#define mh 64

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

void Display::show_int(int16_t x, int16_t y, int disp_num){
  display.setCursor(x, y);
  display.setTextColor(LED_GREEN_HIGH);
  display.setTextSize(TEXT_SIZE);
  display.print(disp_num);
}

void Display::clear_display(){
  display.clear();
}