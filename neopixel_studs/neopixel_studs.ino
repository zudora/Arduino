#include <Adafruit_NeoPixel.h>

#define LED_PIN 0
#define MIC_PIN 1
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     10  // Noise/hum/interference in mic signal
#define SAMPLES   60  // Length of buffer for dynamic level adjustment

Adafruit_Neopixel strip = Adafruit_Neopixel(2, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.setBrightness(80);
  strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  

}
