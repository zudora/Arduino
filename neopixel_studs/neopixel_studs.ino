#include <Adafruit_NeoPixel.h>

#define PIN 0

Adafruit_Neopixel strip = Adafruit_Neopixel(2, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.setBrightness(80);
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:

}
