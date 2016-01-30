#include <Adafruit_NeoPixel.h>

#define PIN 0

const int numLeds = 16; 
const int led_delay = 90;
bool first = false;
 
int wipeArray[16] = {8,7,9,6,10,5,11,4,12,3,13,2,14,1,15,0};

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(70);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for (int i = 0; i <= 5; i++) {
    pulseAll(100);
    pulseAll(117);
    pulseAll(70);
    delay(8000);
  }
}

void pulseAll(int max_red) {
//Currently using wipe to choose next led
  if (first == true) {
    for (int redVal = 1; redVal <= 5; redVal++) {         
      for (int blueAug = 1; blueAug >= 0; blueAug--) {      
        updateStrip(redVal, redVal - blueAug);      
      }    
    }    
  }
  for (int redVal = 5; redVal <= max_red; redVal++) {         
    for (int blueAug = 1; blueAug >= 0; blueAug--) {      
      updateStrip(redVal, (redVal * 2) + 20 - blueAug);      
    }    
  }
  for (int redVal = max_red; redVal >= 5; redVal--) {
    for (int blueAug = -1; blueAug <= 0; blueAug++) {      
      updateStrip(redVal, (redVal * 2) + 20 - blueAug);     
    }    
  }
  if ((max_red * 2) + 10 < 225) {
    //Make it bluer
    int blueVal = max_red * 2 + 20;
    while (blueVal <= 235) {   
     for (int blueAug = 1; blueAug >= 0; blueAug--) {      
      updateStrip(max_red, blueVal - blueAug);     
     }
     blueVal+=2;
    }  
  }
  delay(300);
  if (first == true) { first = false; }
}

void updateStrip(int redVal, int blueVal) {
    for(int j=0; j < strip.numPixels(); j++) {
      strip.setPixelColor(wipeArray[j], strip.Color(redVal, 0, blueVal));
      strip.show();
      if (j % 2 == 0) { delay(led_delay); };      
    }
    genWipeArray();
}

void genWipeArray() {
  //numbers 0-15
  //choose starting point, which is an integer
  int tempArray[16];  
  int startNum = random(0, 16);
  int arrayIndex = 0;
  tempArray[0] = startNum;
  
  for (int ledShift = 1; ledShift <= 8; ledShift++) {
    arrayIndex++;
    tempArray[arrayIndex] = (startNum - ledShift) % 16;
    arrayIndex++;
    if (ledShift < 8) {
    tempArray[arrayIndex] = (startNum + ledShift) % 16;
    }
  }
  for (int i = 0; i <= 15; i++) {
    wipeArray[i] = tempArray[i];
  }
}

