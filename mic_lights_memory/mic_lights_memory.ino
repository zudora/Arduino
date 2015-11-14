#include <Adafruit_NeoPixel.h>

#define PIN 6

int ledNum = 2;
int last20; //For keeping track of previous peaks

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
  for (int windowCount = 0; windowCount < 20; windowCount++)
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
    int brightness = map(peakToPeak, 0, 1023, 0, 255);
    
    for (int i = 0; i < ledNum; i++){
        strip.setPixelColor(i, strip.Color(brightness, 0, 0));
        strip.show();
    }
  
    // add peak to list
    last20 += brightness;   
    //double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
    //Serial.println(volts);    
  }
  int average = last20 / 20;
  Serial.println(average);
  last20 = 0;
}
