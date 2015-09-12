#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

int led1 = 9;
int led2 = 10;
int led3 = 12;
int led4 = 6;
int led5 = 1;

int ledCount = 5;
int ledArray[] = {led1, led2, led3, led4, led5};

unsigned long prevMillis = 0;
unsigned long accelStart = 0;
long interval = 100;
int yLedState = HIGH;
int wLedState = LOW;
int altCount = 0;     //number of alt cycles performed
int sweepCount = 0;   //number of sweeps performed
int dir = 0;          //pos-neg direction of time interval increment
int cycleCount = 0;   //number of times a blink program has run
int progMode = 0;     //location in series of programs

//accelerometer
Adafruit_MMA8451 mma = Adafruit_MMA8451();


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
 while (cycleCount < 2)
 {
   unsigned long currMillis = millis();  
    if (currMillis - prevMillis >= interval)
    {
      if (progMode == 0)
      {
        interval = 100;
        //alternate();               
        cycleCount = 2;   //keeps this prog from running
      }
      else if (progMode == 1)
      { 
        interval = 200;     
        //sweep();
        cycleCount = 2;  //keeps this prog from running              
      }
      else
      {   
        accelStart = millis();
        accel();
      }      
      prevMillis = currMillis;      
    }    
  }
  progMode++;
  if (progMode > 3)
  {
    progMode = 0;
  }
  cycleCount = 0;
}

void alternate()
{           
  yLedState = ! yLedState;
  wLedState = ! wLedState;
    
  if (altCount == 2)
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
    if (interval >= 1000 | interval <= 100)
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
  while (sweepCount < 10)
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

void accel()
{
  while (millis() - accelStart < 8000)
  {
    // Read the 'raw' data in 14-bit counts
    mma.read();
    Serial.print("X:\t"); Serial.print(mma.x); 
    Serial.print("\tY:\t"); Serial.print(mma.y); 
    Serial.print("\tZ:\t"); Serial.print(mma.z); 
    Serial.println();
    
  
    /* Get a new sensor event */ 
    sensors_event_t event; 
    mma.getEvent(&event);
  
    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
    Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
    Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
    Serial.println("m/s^2 ");
    
    /* Get the orientation of the sensor */
    uint8_t o = mma.getOrientation();
    
    switch (o) {
      case MMA8451_PL_PUF: 
        Serial.println("Portrait Up Front");
        break;
      case MMA8451_PL_PUB: 
        Serial.println("Portrait Up Back");
        break;    
      case MMA8451_PL_PDF: 
        Serial.println("Portrait Down Front");
        break;
      case MMA8451_PL_PDB: 
        Serial.println("Portrait Down Back");
        break;
      case MMA8451_PL_LRF: 
        Serial.println("Landscape Right Front");
        break;
      case MMA8451_PL_LRB: 
        Serial.println("Landscape Right Back");
        break;
      case MMA8451_PL_LLF: 
        Serial.println("Landscape Left Front");
        break;
      case MMA8451_PL_LLB: 
        Serial.println("Landscape Left Back");
        break;
      }
    Serial.println();
    delay(500);
  }
}

