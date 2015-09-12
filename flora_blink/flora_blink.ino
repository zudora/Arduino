int led1 = 9;
int led2 = 10;
int led3 = 12;
int led4 = 6;
int led5 = 1;

int ledCount = 5;
int ledArray[] = {led1, led2, led3, led4, led5};

unsigned long prevMillis = 0;
long interval = 100;
int yLedState = HIGH;
int wLedState = LOW;
int altCount = 0;     //number of alt cycles performed
int sweepCount = 0;   //number of sweeps performed
int dir = 0;          //pos-neg direction of time interval increment
int cycleCount = 0;   //number of times a blink program has run
int progMode = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for(int pin = 0; pin < ledCount; pin++)
  {
    pinMode(ledArray[pin], OUTPUT);
  }
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);     
  pinMode(led5, OUTPUT);     
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
        //alternate();
        interval = 100;
        cycleCount = 2;   //keeps this prog from running
      }
      else
      {
        interval = 50;
        sweep();        
      }      
      prevMillis = currMillis;      
    }    
  }
  progMode++;
  if (progMode > 2)
  {
    progMode = 0;
  }
  cycleCount = 0;
}

void alternate()
{         
    if (yLedState == HIGH)
    {
      yLedState = LOW;
      wLedState = HIGH;
    }
    else
    {
      yLedState = HIGH;
      wLedState = LOW;
    }
    
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
  int onLine = 0;
  while (onLine < 5)
  { 
    chooseLine(onLine);
    delay(200);
    onLine++;
  }
  while (onLine >= 0)
  { 
    chooseLine(onLine);
    delay(200);
    onLine--;
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

