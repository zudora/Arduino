// Simple NeoPixel test.  Lights just a few pixels at a time so a
// 1m strip can safely be powered from Arduino 5V pin.  Arduino
// may nonetheless hiccup when LEDs are first connected and not
// accept code.  So upload code first, unplug USB, connect pixels
// to GND FIRST, then +5V and digital pin 6, then re-plug USB.
// A working strip will show a few pixels moving down the line,
// cycling between red, green and blue.  If you get no response,
// might be connected to wrong end of strip (the end wires, if
// any, are no indication -- look instead for the data direction
// arrows printed on the strip).

#include <Adafruit_NeoPixel.h>

#define PIN      0
#define N_LEDS 16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  //strip.setBrightness(105);
}

void loop() {
  
//  chase(strip.Color(255, 0, 0)); // Red
//  chase(strip.Color(0, 255, 0)); //Green
  
  for(int var = 0; var <= 205; var++)
  {
    uint32_t red_val = 50 + var;
    uint32_t blue_val = 255 - var;  
    chase(strip.Color(red_val, 0, blue_val));
//    strip.setPixelColor(1, red_val, 0, blue_val);
//    strip.show();
    delay(5);
  }   
  for(int var = 205; var >= 0; var--)
  {
    uint32_t red_val = 50 + var;
    uint32_t blue_val = 255 - var;
    chase(strip.Color(red_val, 0, blue_val));
//    strip.setPixelColor(1, red_val, 0, blue_val);
//    strip.show();
    delay(5);
  }
}

static void chase(uint32_t c) {
for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      //strip.setPixelColor((i+1) % strip.numPixels(), 0); //Sweep all around
      strip.setPixelColor((i-4 + strip.numPixels()) + strip.numPixels(), 0); // Erase pixel a few steps back
      strip.show();
      delay(5);
  }
}

static void four_chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}
