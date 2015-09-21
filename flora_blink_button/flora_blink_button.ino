#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

int led1 = 1;
int led2 = 10;
int led3 = 9;
int led4 = 6;
int led5 = 12;

int ledCount = 5;
int ledArray[] = {led1, led2, led3, led4, led5};

unsigned long prevMillis = 0;
unsigned long currMillis;
long interval = 200;
int sequence = 0;     //which sequence is running
int seqBookmark = 0;  //last seq that ran, for return after pause routine
int cycleCount = 0;   //number of times a blink program has run



long sweepInterval = 200;
int yLedState = HIGH;
int wLedState = LOW;
int altCount = 0;     //number of alt cycles performed
int sweepCount = 0;   //number of sweeps performed
int senseCount = 0;   //number of sensor cycles 
int dir = 0;          //pos-neg direction of time interval increment

unsigned long accelStart = 0;

//accelerometer
Adafruit_MMA8451 mma = Adafruit_MMA8451();
int xAccel;
int yAccel;
int zAccel;
int accelArray[3];

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for(int pin = 0; pin < ledCount; pin++)
  {
    pinMode(ledArray[pin], OUTPUT);
  }

  //set up serial monitor for accelerometer
  Serial.begin(9600);
    
  Serial.println("Adafruit MMA8451 test!");
  
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  mma.setRange(MMA8451_RANGE_2_G);
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");
 
}

void loop() 
{

 // The loop runs over and over
 // Each run, it checks the state
 // Outer state variables and their effect:
 //   Time: seconds till doom
 //   sequence: which sequence is running
 //     Inner state variables
 //       cycleCount: Count of runs of this sequence. Reset to 0 each time sequence changes. Each sequence has its own desired number of repeats 
 //       interval: current delay used in current sequence

 // Check current time
    
 currMillis = millis();
 
 // Subtract last time; compare to interval
 
  if (currMillis - prevMillis >= interval)
  {
    // If it's equal or greater, update lights and state
      // Choose sequence
      
      
      switch(sequence)
      {
        case 0:
          //Alternate
          if (cycleCount <= 1)
          {
           cycleCount++; 
          }
          else
          {
            // Go to pause
            sequence = 3;
          }
          break;
          
        case 1:
          // Sweep
          if (cycleCount <= 2)
          {
           cycleCount++; 
          }
          else
          {
            // Go to pause
            sequence = 3;
          }
          break;
          
        case 2:
          if (cycleCount <= 20)
          {
           cycleCount++; 
          }
          else
          {
            // Go to pause
            sequence = 3;
          }
          break;

        case 3:
          // Pause between sequences     
          if (cycleCount <= 1)
          {
           // Set lights low
           for (int led = 0; led <= 5; led++)
           {
            digitalWrite(ledArray[led], LOW); 
           }
           cycleCount++; 
          }
          else
          {
            // Go back to bookmark
            sequence = 3;
          }
          break;
          
        break;
      }
      
    
    // increment cycleCount

    // if done with cycles, increment sequence
  }  
 
 
 
 // Data for Sweep
 //   Sequence number
 //   Interval
 //   Current light state
 //   Direction of sweep

 // Date for Alternate
 //   Sequence number
 //   Interval
 //   Current light state






 
// while (cycleCount < 1)
// {
//   currMillis = millis();  
//   if (currMillis - prevMillis >= interval)
//   {
//    if (progMode == 0)
//    {        
//      dir = 0;
//      alternate();                 
//    }
//    else if (progMode == 1)
//    {                
//     sweep();
//    }
//    else
//    {           
//        for (int flash = 0; flash < 2; flash++)
//        {
//          digitalWrite(led3, HIGH);
//          delay(500);
//          digitalWrite(led3, LOW);
//          delay(500);
//        }
//        
//        while (senseCount < 50)
//        {
//        // Read the 'raw' data in 14-bit counts
//        mma.read();
//        accelArray[0] = mma.x;        
//        accelArray[1] = mma.y;
//        accelArray[2] = mma.z;

        //Serial.print("X: \t"); Serial.print(accelArray[0]); Serial.print("\t");
        //Serial.print("Y: \t"); Serial.print(accelArray[1]); Serial.print("\t");
        //Serial.print("Z: \t"); Serial.print(accelArray[2]); Serial.print("\t");
        //Serial.print("Count: \t"); Serial.print(senseCount); Serial.print("\t");
        //Serial.println();
        
        accel(accelArray);
                  
        delay(500);
        senseCount++;
      }
        cycleCount = 2;                    
    }      
    prevMillis = currMillis;      
   }    
  }
  
  for(int led = 0; led < ledCount; led++)
  {    
    digitalWrite(ledArray[led], LOW); 
  }
  delay(500);

  prevMillis = currMillis;      
  progMode++;
  if (progMode > 2)
  {
    progMode = 0;
  }
  //reset all counts
  cycleCount = 0;
  interval = 200;
  sweepInterval = 200;  
  altCount = 0;     //number of alt cycles performed
  sweepCount = 0;   //number of sweeps performed
  senseCount = 0;   //number of sensor cycles 
}

void alternate()
{           
  yLedState = ! yLedState;
  wLedState = ! wLedState;    
  if (altCount == 6) //have gone through two passes of alternate() at a certain interval
  {
    int timeInc = 0;
    if (dir == 0)
    {
      timeInc = 100; 
    }
    else
    {
      timeInc = -100;
    }
    interval = interval + timeInc;
    if (interval >= 900 | interval <= 100)
    {
      if (dir == 0){dir = 1;}
      else{dir = 0;}
      cycleCount++;     
    }
    altCount = 0;    
  }  
  for(int led = 0; led < ledCount; led++)
  {    
   if (led % 2 == 0)
   {
    digitalWrite(ledArray[led], wLedState); 
   }
   else
   {
    digitalWrite(ledArray[led], yLedState);
   }
  }
  altCount++;     
}

void sweep()
{  
  // Turn on each line in turn
  while (sweepCount < 4)    //default 10
  {
    int onLine = -1;
    while (onLine < 5)
    { 
      chooseLine(onLine);
      delay(interval);
      onLine++;
    }
    while (onLine >= -1)
    { 
      chooseLine(onLine);
      delay(interval);
      onLine--;
    }
    interval = interval + 100;
    
    sweepCount++;
  }    
  cycleCount++;
}

void chooseLine(int onLine)
{
  for(int i = 0; i < ledCount; i++)
  {
    int ledState = LOW;
    if (i == onLine | i == onLine - 1 | i == onLine + 1)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(ledArray[i], ledState);        
  }
}

void accel(int accelArray[])
{
  // x values max out around +-5000
  // y values as high as 7000

  //Choose line to light up based on x value
  int onLine;

  if (accelArray[0] < -1400)
  {
    onLine = 0;
  }
  else if (accelArray[0] < -400)
  {
    onLine = 1;  
  }
  else if (accelArray[0] < 400)
  {
    onLine = 2;  
  }  
  else if (accelArray[0] < 1400)
  {
    onLine = 3;  
  }
    else
  {
    onLine = 4;  
  }
  
  for(int i = 0; i < ledCount; i++)
  {
    int ledState = LOW;
    if (i == onLine)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(ledArray[i], ledState);        
  }
}

