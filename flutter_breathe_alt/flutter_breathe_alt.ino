#include <Adafruit_NeoPixel.h>

#define PIN 0

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    
  breatheAll();  
  breatheAll();  
  breatheAll();
  delay(5000);
}

void breatheAll() {
  int variant = 2;
  for (int i=10; i <= 127 ; i++) {
    for(int j=0; j < strip.numPixels(); j++) {
      //strip.setPixelColor(j, strip.Color(i+15, i, 0)); // yellow with a little extra red to make it warmer
      strip.setPixelColor(j, strip.Color(i, 0, i * 2));        
    }  
    strip.show();    
    delay(25);
  }
  for (int i = 127; i >= 10; i--) {
    for(int j=0; j < strip.numPixels(); j++) {      
      strip.setPixelColor(j, strip.Color(i, 0, i * 2));      
    }    
    strip.show();    
    delay(25);
  }
  delay(300);
}

void breatheAllblue() {
  for (int i=1; i <= 127 ; i++) {
    for(int j=0; j<strip.numPixels(); j++) {
      //strip.setPixelColor(j, strip.Color(i+15,i,0)); // yellow with a little extra red to make it warmer 
      strip.setPixelColor(j, strip.Color(i,0,i*2));
    }
    strip.show();
    delay(20);
  }
  for (int i = 127; i >= 1; i--) {
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(i,0,i*2));
    }
    strip.show();
    delay(20);
  }
  delay(1000);
}
