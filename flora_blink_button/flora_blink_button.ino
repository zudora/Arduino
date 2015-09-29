#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

const int led1 = 1;
const int led2 = 10;
const int led3 = 9;
const int led4 = 6;
const int led5 = 12;

const int ledCount = 5;
const int ledArray[] = {led1, led2, led3, led4, led5};

int stateArray[] = {LOW, LOW, LOW, LOW, LOW};

String stateString;
unsigned long prevMillis = 0;
unsigned long currMillis;
long interval = 200;
int sequence = 0;     //which sequence is running
int seqBookmark = 0;  //last seq that ran, for return after pause routine
int cycleCount = 0;   //number of times a blink program has run

// Inner counts
int timeDir = 1;      //pos-neg direction of time interval increment
int pauseRepeats = 0; //number of times to run pause routine
int altCount = 0;     //number of alt cycles performed
int sweepCount = 0;   //number of sweeps performed
int sweepDir = 1;     //direction of sweep
int prevLine = -2;     //last center line on sweep
int senseCount = 0;   //number of sensor cycles 

//accelerometer
Adafruit_MMA8451 mma = Adafruit_MMA8451();
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
  // For debugging: Hold off so there's time to open serial monitor 
  delay(5000);
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
      
      if (sequence != 3) seqBookmark = sequence;
      
      switch(sequence)
      {
        case 0:
          //Serial.print("Seq 0: Alternate");Serial.print("\n");
          alternate();
          break;
          
        case 1:
          Serial.print("Seq 0: Sweep");Serial.print("\n");
          sweep();         
          break;
          
        case 2:
          // Sensor
          if (cycleCount <= 20)
          {            
            // Read the 'raw' data in 14-bit counts
            mma.read();
            accelArray[0] = mma.x;        
            accelArray[1] = mma.y;
            accelArray[2] = mma.z;
    
            //Serial.print("X: \t"); Serial.print(accelArray[0]); Serial.print("\t");
            //Serial.print("Y: \t"); Serial.print(accelArray[1]); Serial.print("\t");
            //Serial.print("Z: \t"); Serial.print(accelArray[2]); Serial.print("\t");
            //Serial.print("Count: \t"); Serial.print(senseCount); Serial.print("\t");
            //Serial.println();
            
            accel(accelArray);            
          }
          else
          {
            // Go to pause
            sequence = 3;
          }
          break;

        case 3:
          // Pause between sequences
          // Set repeats based on provided interval--differs depending on seq handing in
          pauseRepeats = int(500 / interval);
               
          if (cycleCount <= pauseRepeats)
          {
           // Set lights low
           for (int led = 0; led < ledCount; led++)
           {
            if (ledArray[led] != LOW)
            {
              digitalWrite(ledArray[led], LOW);              
            }
           }           
           cycleCount++; 
          }
          else
          {
            // Go back to bookmark            
            sequence = seqBookmark;
            // reset to default interval starting value 
            interval = 100;
          }
          break;          
          
        prevMillis = currMillis;
        break;
      }                
  }   
} 
void alternate()
{
  //Serial.print("Alternate cycleCount: ");Serial.print(cycleCount);Serial.print("\n");
  if (cycleCount <= 2)
  {
    // change interval every third round
    if (altCount % 3 == 0 && altCount != 0)
    {
     //Serial.print("Mod\n");      
     interval = interval + (timeDir * 100);
     if (interval < 0) {Serial.print("Interval too low");}     
    }       
    Serial.print(cycleCount);Serial.print(": ");Serial.print(altCount); Serial.print("\n");
                
    if (altCount == 9)
    {
      Serial.print("Changing direction\n"); 
      // Change time interval direction
      timeDir = -1;
    }
    if (altCount == 18)
    {
     Serial.print("finished a cycle. Increment\n"); 
     // finished a cycle. Increment
     cycleCount++;      
     altCount = 0;
     timeDir = 1;
    }
    
    // If it's the first round, set up alternation
    //Serial.print("altCount: ");Serial.print(altCount);Serial.print("\n");
    if (altCount == 0)
    {
     Serial.print("First run\n");
     stateString = "";     
     for (int led = 0; led < ledCount; led++)
     {
      if (led % 2 == 0)
      {
         digitalWrite(ledArray[led], HIGH);         
         stateString += led;
         stateString += ": HIGH, "; 
       }
      else
      {
        digitalWrite(ledArray[led], LOW);
        stateString += led;
        stateString += ": LOW, "; 
      }
      Serial.print(stateString);
     }
    }            
    else
    {     
      stateString = "";
      for (int led = 0; led < ledCount; led++)
      {
        if (ledArray[led] == LOW)
        {
          digitalWrite(ledArray[led], HIGH);                  
          stateString += led;
          stateString += ": HIGH, ";          
          
        }               
        else
        {
          digitalWrite(ledArray[led], LOW);
          stateString += led;
          stateString += ": LOW, ";          
          }
      }
      Serial.print(stateString);
    }
    altCount++;
    
    
  }
  else
  {
    // Go to pause
    sequence = 3;
    cycleCount = 0;
    timeDir = 1;
    altCount = 0;
  }
}          

void sweep()
{
  if (cycleCount <= 2)
  {                                   
    int nextLine = prevLine + sweepDir;
    
    if (nextLine < ledCount && nextLine >= 0)
    {
      for (int led = 0; led < ledCount; led++)
      {
        if (nextLine - 1 <= led && led <= nextLine + 1)
        {
          digitalWrite(ledArray[led], HIGH);
        }
        else
        {
          digitalWrite(ledArray[led], LOW);
        }                       
      }              
    }
    else
    {
      //this round, don't update lights, just hold and change sweep direction
      sweepDir = -sweepDir;
    }
    
    // change interval every third round
    if (sweepCount % 2 == 0)
    {
     interval = interval + (timeDir * 100);
    }
                
    if (sweepCount == 10)
    {
       timeDir = -1;
    }
    
    if (sweepCount == 20)
    {
      cycleCount++;
      timeDir = 1;
      sweepDir = 1;
    }            
    prevLine = nextLine;                       
  }
  else
  {
    // Go to pause
    sequence = 3;
    cycleCount = 0;
    sweepCount = 0;
    timeDir = 1;
    sweepDir = 1;
    prevLine = -2;
  }
}

void accel(int accelArray[])
{
  if (cycleCount <= 50)
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
    cycleCount++;
  }
  else
  {
    // Go to pause
    sequence = 3;
    cycleCount = 0;    
  }
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


