#include <Adafruit_NeoPixel.h>

#define PIN 0

const int numLeds = 16; 

int ledNum[16];
int wipeArray[16] = {8,7,9,6,10,5,11,4,12,3,13,2,14,1,15,0};

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(90);
  strip.show(); // Initialize all pixels to 'off'
  for (int i = 0; i < 16; i++){
    ledNum[i] = i;
  }
  int r;
  for (int rand_index = 0; rand_index < 14; rand_index++){
    r = random(rand_index, 15);
    int temp = ledNum[rand_index];
    ledNum[rand_index] = ledNum[r];
    ledNum[r] = temp;
  }
}

void loop() {

  breatheAllRand(110);
  breatheAllRand(127);
  breatheAllRand(90);
  delay(1000);
}

//Randomizing next led to update
void breatheAllRand(int max_red) {
  const int delay_time = 100;
  const int led_delay = 10;
  
  for (int redVal=5; redVal <= max_red ; redVal++) {         
    for (int blueAug = 1; blueAug >= 0; blueAug--) {      
      for(int j=0; j<strip.numPixels(); j++) {              
        strip.setPixelColor(ledNum[j], strip.Color(redVal, 0, redVal * 2 - blueAug ));
        strip.show();
        delay(led_delay/ 2);
      }
    }     
  }
  for (int redVal = max_red; redVal >= 5; redVal--) {
    for (int blueAug = 1; blueAug >= 0; blueAug--) {      
      for(int j=0; j < strip.numPixels(); j++) {
        strip.setPixelColor(ledNum[j], strip.Color(redVal, 0, redVal * 2 + blueAug));
        strip.show();
        delay(led_delay / 2);
      }
    }    
  }
  delay(300);
}
