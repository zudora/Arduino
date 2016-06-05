#include <Adafruit_NeoPixel.h>

#define PIN 0

const int numLeds = 16; 
const int led_delay = 150;
bool first = true;
bool last = false;
bool early = true;

int useArray[16];
int wipeArray[16] = {8,7,9,6,10,5,11,4,12,3,13,2,14,1,15,0};
int fourPointArray[16] = {0,4,8,12,1,5,9,13,3,7,11,15,2,6,10,14};

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
    pulseAll(90, true, 100);    
    pulseAll(102, true, 200);
    pulseAll(70, true, 50);
    delay(9000);
    last = true;
  }
}

void pulseAll(int max_red, bool addFlutter, int fluttDelay) {
  //Start blues
  early = true;

  //structure
  int startRed;
  int endRed;
  int inc;
  int colorDiff;
  int blueMult;

  for (int initBlue = 1; initBlue <= 10; initBlue++) {
    updateStrip(0, initBlue);
    delay(300);
  }
  early = false;
  //First full round
  int passRed = 0;
  if (first == true) {    
    for (int redVal = 1; redVal <= 5; redVal++) {         
      for (int blueAug = 1; blueAug >= 0; blueAug--) {      
        updateStrip(redVal, redVal + 10 - blueAug);      
        first = false;
        passRed = redVal;
      }    
    }    
  }
  //ramp up blue a bit
//  for (int blueVal = passRed + 21; blueVal = (passRed * 2) + 49; blueVal++) {
//    updateStrip(passRed, blueVal);
//    delay(100); 
//  }

  for (int redVal = 5; redVal <= max_red; redVal++) {         
    for (int blueAug = 1; blueAug >= 0; blueAug--) {      
      updateStrip(redVal, (redVal * 2) + 50 - blueAug);            
    } 
    if (redVal == max_red && addFlutter == true) { flutter(redVal, fluttDelay); }   
  }
  delay(500);
  for (int redVal = max_red; redVal >= 5; redVal--) {
    for (int blueAug = -1; blueAug <= 0; blueAug++) {      
      updateStrip(redVal, (redVal * 2) + 50 - blueAug);     
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
  delay(3000);
  if (last == true) {
    //Run down the scale for restart
  }
  first = true;
}

void runLoops(int startRed, int endRed, int inc, int colorDiff, int blueMult) {
  
  for (int redVal = startRed; redVal <= endRed; redVal + inc) {
    for (int blueAug = 1; blueAug >= 0; blueAug--) {
      updateStrip(redVal, (redVal * blueMult) + colorDiff - blueAug);
    }  
  }
}

void updateStrip(int redVal, int blueVal) {   
    for(int j=0; j < strip.numPixels(); j++) {
      strip.setPixelColor(wipeArray[j], strip.Color(redVal, 0, blueVal));
      strip.show();
      if ((first == false && j % 2 == 0) || early == true) { 
        delay(led_delay); 
        }      
    }
    delay(100);
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

void flutter(int redVal, int fluttDelay) {    
      for (int diffCount = 0; diffCount >= 49; diffCount++) {
        int redDiff = 0;
        if (diffCount <=24) { redDiff = 1; }
        else { redDiff = -1; }
        redVal = redVal + redDiff;      
        updateStrip(redVal, (redVal * 2) + 20);             
        delay(fluttDelay);
        if (diffCount == 24) { delay(300); }
      }
}

