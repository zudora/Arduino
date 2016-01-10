#include <Adafruit_NeoPixel.h>

#define PIN 2

const int ledNum = 1;

int volAccum; //For keeping track of previous peaks
int prevAvg = 0;
const int memorySize = 20;
int maxBrightness = 200;
int minVol = 0;
float peakVar;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledNum, PIN, NEO_GRB + NEO_KHZ800);

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() 
{
  //Serial.begin(9600);
  strip.begin();
  strip.setBrightness(90);
  strip.show(); // Initialize all pixels to 'off'
}

// In a quiet location, a value over 1024 is probably garbage
// But in a loud location, we want to be able to discriminate


void loop() 
{
  for (int windowCount = 0; windowCount < memorySize; windowCount++)
  {
    unsigned long startMillis= millis();  // Start of sample window
    unsigned int peakToPeak = 0;   // peak-to-peak level
    
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
  
    // collect data for 50 mS
    while (millis() - startMillis < sampleWindow)
    {
      sample = analogRead(3);
      //Serial.println(sample);
      
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
    }
    peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
    //Serial.println(peakToPeak);
    int brightness = map(peakToPeak, minVol, 1800, 0, maxBrightness);
    
    //int brightness = map(peakToPeak, minVol, 1500, 0, maxBrightness);
    
    for (int i = 0; i < ledNum; i++){
        strip.setPixelColor(i, strip.Color(brightness, 0, 0));
        strip.show();
    }
  
    // add peak to list
    volAccum += peakToPeak;
       
    //double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
    
  }
  int latestAvg = volAccum / memorySize;
  //Serial.println(latestAvg);

  // If last few seconds over a certain threshold, use a narrower map
  if (abs(prevAvg - latestAvg) <= latestAvg * .3){
  //Serial.print("Voladjust\t");
   //Serial.println(minVol);
    volAdjust(minVol, prevAvg);
  }
  
//  if (20 <= prevAvg < 30  && 20 < latestAvg < 30){
//    volAdjust(minVol, prevAvg);
//  }
//  else if (30 <= prevAvg < 70  && 30 < latestAvg < 70){
//    volAdjust(minVol, prevAvg);
//  }
//  else if (70 <= prevAvg < 100  && 70 <= latestAvg < 100){
//    volAdjust(minVol, prevAvg);
//  }
//  else if (100 <= prevAvg < 200  && 100 <= latestAvg < 200){
//    volAdjust(minVol, prevAvg);
//  }
//  else if (200 <= prevAvg < 400  && 200 <= latestAvg < 400){
//    volAdjust(minVol, prevAvg);
//  }
//  else if (400 <= prevAvg < 600  && 400 <= latestAvg < 600){
//    volAdjust(minVol, prevAvg);
//  }
//  else if (600 <= prevAvg < 900  && 600 <= latestAvg < 900){
//    volAdjust(minVol, prevAvg);
//  }      
//    else if (1000 <= prevAvg && 1000 <= latestAvg){
//    volAdjust(minVol, prevAvg);
//  }
  
  prevAvg = latestAvg;
  latestAvg = 0;
  volAccum = 0;
}

void volAdjust(int minVol, int target)
{
    if (minVol < target){
      minVol += 10;
    }
    else if (minVol > target){
      minVol -= 10;      
    }  
}

