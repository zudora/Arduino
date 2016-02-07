#include <Adafruit_NeoPixel.h>

#define PIN 2

const int ledNum = 5;

int volAccum; //For keeping track of previous peaks
int numAccum = 0; //Number of peaks in current history
int accumArray[20];
int tempArray[20];
int prevAvg = 0;
int arraySum;
int arrayAvg;
int prevArrayAvg = 0;

const int memorySize = 20;
int maxBrightness = 200;
int minVol = 0;
float peakVar;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledNum, PIN, NEO_GRB + NEO_KHZ800);

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {
  //Serial.begin(9600);
  strip.begin();
  strip.setBrightness(90);
  strip.show(); // Initialize all pixels to 'off'
}

// In a quiet location, a value over 1024 is probably garbage
// But in a loud location, we want to be able to discriminate


//current issue is long latency for high peaks

void loop() {
  for (int windowCount = 0; windowCount < memorySize; windowCount++)
  {
    unsigned long startMillis= millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level
    
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
  
    // collect data for 50 mS
    while (millis() - startMillis < sampleWindow) {
      sample = analogRead(18);
      //Serial.println(sample);
      
      if (sample < 1024) { 
        // toss out spurious readings      
         if (sample > signalMax) {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin) {
            signalMin = sample;  // save just the min levels
         }
      }
    }
    peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude    
    int brightness = map(peakToPeak, minVol, 1800, 0, maxBrightness);
    
    for (int i = 0; i < ledNum; i++) {
        strip.setPixelColor(i, strip.Color(brightness, 0, 0));        
        strip.show();
    }
    // add peak
    //volAccum += peakToPeak;
    accumArray[numAccum] = peakToPeak;
    if (numAccum < 20) { 
      numAccum++; 
    }       
  }
  
  //average and convert to integer
//  int latestAvg = volAccum / numAccum;
//  
//  // If last few seconds over a certain threshold, use a narrower map
//  if (abs(prevAvg - latestAvg) <= latestAvg * .3) {
//    volAdjust(minVol, prevAvg);
//  }
//  //cleanup
//  prevAvg = latestAvg; 
//    
//  if (numAccum > 20) {     
//    latestAvg = 0;
//    volAccum = 0;
//    numAccum = 0;
//  }

  //Using array
  arraySum = 0;  
  for (int i = 0; i < numAccum; i++) {
    arraySum += accumArray[i];
  }
  arrayAvg = arraySum / numAccum;

  // If last few seconds over a certain threshold, use a narrower map
  if (abs(prevArrayAvg - arrayAvg) <= arrayAvg * .3) {
    volAdjust(minVol, arrayAvg);
  }
  
  //cleanup
  if (numAccum == 20){
    prevArrayAvg = arrayAvg;
    for (int i = 0; i < numAccum; i++) {
      if (i <= 5) {
        accumArray[i] = accumArray[i + 15];
      }
      else {
        accumArray[i] = 0;
      }
    }
    numAccum = 5;
  } 
}

void volAdjust(int minVol, int target) {
    if (minVol < target) {
      minVol += 10;
    }
    else if (minVol > target) {
      minVol -= 10;      
    }  
}

//Old mappings
//  if (20 <= prevAvg < 30  && 20 < latestAvg < 30) {
//    volAdjust(minVol, prevAvg);
//  }
//  else if (30 <= prevAvg < 70  && 30 < latestAvg < 70) {
//    volAdjust(minVol, prevAvg);
//  }
//  else if (70 <= prevAvg < 100  && 70 <= latestAvg < 100) {
//    volAdjust(minVol, prevAvg);
//  }
//  else if (100 <= prevAvg < 200  && 100 <= latestAvg < 200) {
//    volAdjust(minVol, prevAvg);
//  }
//  else if (200 <= prevAvg < 400  && 200 <= latestAvg < 400) {
//    volAdjust(minVol, prevAvg);
//  }
//  else if (400 <= prevAvg < 600  && 400 <= latestAvg < 600) {
//    volAdjust(minVol, prevAvg);
//  }
//  else if (600 <= prevAvg < 900  && 600 <= latestAvg < 900) {
//    volAdjust(minVol, prevAvg);
//  }      
//    else if (1000 <= prevAvg && 1000 <= latestAvg) {
//    volAdjust(minVol, prevAvg);
//  }

