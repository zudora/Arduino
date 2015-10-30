#include <Adafruit_NeoPixel.h>

#define PIN 0
int ledNum[16];

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  //strip.setBrightness(100);
  strip.show(); // Initialize all pixels to 'off'
  for (int i = 0; i < 16; i++)
  {
    ledNum[i] = i;
  }
}

void loop() {
    
//  breatheAll();  
//  breatheAll();  
//  breatheAll();
  breatheAllblue();
  breatheAllblue();
  breatheAllblue();
  delay(5000);
}

//Made some changes to try to make coin cell batteries work. Looks like it may be an issue of max current and not just the 6v needing to be dropped to 3.5-4v.
//Tried various resistors
//Using a capacitor across the power smoothed out the flickering but made the colors not appear correctly. 
void breatheAll() {
    for (int i=10; i <= 127 ; i++) {
    for(int j=0; j < strip.numPixels(); j++) {
      //strip.setPixelColor(j, strip.Color(i+15, i, 0)); // yellow with a little extra red to make it warmer
      strip.setPixelColor(j, strip.Color(i, 0, i*2));        
    }  
    strip.show();    
    delay(100);
  }
  for (int i = 127; i >= 10; i--) {
    for(int j=0; j < strip.numPixels(); j++) {      
      strip.setPixelColor(j, strip.Color(i, 0, i*2));      
    }    
    strip.show();    
    delay(100);
  }
  delay(300);
}

//Use for blue-purple colors appropriate for jellyfish.
void breatheAllblue() {
  const int delay_time = 100;
  const int led_delay = 10;
  
  for (int i=5; i <= 127 ; i++) {
    int r;
    for (int rand_index = 0; rand_index < 15; rand_index++)
    {
      r = random(rand_index, 14);
      int temp = ledNum[rand_index];
      ledNum[rand_index] = ledNum[r];
      ledNum[r] = temp;
    }
    
    for(int j=0; j<strip.numPixels(); j++) {      
      strip.setPixelColor(ledNum[j], strip.Color(i, 0, i*2));
      delay(led_delay);
    }
    strip.show();
    //delay(delay_time);
  }
  for (int i = 127; i >= 5; i--) {
    for(int j=0; j<strip.numPixels(); j++) {
      strip.setPixelColor(ledNum[j], strip.Color(i, 0, i*2));
      delay(led_delay);
    }    
    strip.show();
    //delay(delay_time);
  }
  delay(300);
}
