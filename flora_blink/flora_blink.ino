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
unsigned long accelStart = 0;
long interval = 200;
long sweepInterval = 200;
int yLedState = HIGH;
int wLedState = LOW;
int altCount = 0;     //number of alt cycles performed
int sweepCount = 0;   //number of sweeps performed
int senseCount = 0;   //number of sensor cycles 
int dir = 0;          //pos-neg direction of time interval increment
int cycleCount = 0;   //number of times a blink program has run
int progMode = 0;     //location in series of programs

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

// the loop routine runs over and over again forever:
void loop() 
{
 while (cycleCount < 1)
 {
   unsigned long currMillis = millis();  
    if (currMillis - prevMillis >= interval)
    {
      if (progMode == 0)
      {        
        alternate();                 
      }
      else if (progMode == 1)
      {                
       sweep();
      }
      else
      {           
        while (senseCount < 20)
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
                    
          delay(500);
          senseCount++;
        }
        cycleCount = 2;
        interval = 200;             
      }      
      prevMillis = currMillis;      
    }    
  }
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
    if (interval >= 800 | interval <= 100)
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
  while (sweepCount < 2)    //default 10
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

  if (accelArray[0] < -1000)
  {
    onLine = 0;
  }
  else if (accelArray[0] < -100)
  {
    onLine = 1;  
  }
  else if (accelArray[0] < 100)
  {
    onLine = 2;  
  }  
  else if (accelArray[0] < 1000)
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

