#include <Adafruit_NeoPixel.h>

#define PIN 6

const int ledNum = 2;

int volAccum; //For keeping track of previous peaks
int prevAvg = 0;
const int memorySize = 100;
int maxBrightness = 200;
int minVol = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledNum, PIN, NEO_GRB + NEO_KHZ800);

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() 
{
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(90);
  strip.show(); // Initialize all pixels to 'off'
}

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
      sample = analogRead(0);
      
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
    int brightness = map(peakToPeak, minVol, 1023, 0, maxBrightness);
    
    for (int i = 0; i < ledNum; i++){
        strip.setPixelColor(i, strip.Color(brightness, 0, 0));
        strip.show();
    }
  
    // add peak to list
    volAccum += brightness;   
    //double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
    //Serial.println(volts);    
  }
  int latestAvg = volAccum / memorySize;
  Serial.println(latestAvg);

  // If last few seconds over a certain threshold, use a narrower map
  if (prevAvg > 200 && volAccum > 200){
    minVol = 100;
  }
  else if (prevAvg > 400 && volAccum > 400){
    minVol = 300;
  }
  
  prevAvg = latestAvg;
  latestAvg = 0;
  volAccum = 0;
}
