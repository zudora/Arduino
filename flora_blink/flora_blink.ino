int led1 = 9;
int led2 = 10;
int led3 = 12;
int led4 = 6;
int led5 = 1;
unsigned long prevMillis = 0;
long interval = 100;
int yLedState = HIGH;
int wLedState = LOW;
int roundCount = 0;
int dir = 0;
int cycleCount = 0;
int progMode = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
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
        alternate();
      }
      else
      {
        digitalWrite(led3, HIGH);
        digitalWrite(led2, HIGH);
        delay(1000);
        cycleCount++;
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
    
    if (roundCount == 2)
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
      roundCount = 0;    
    }  
    digitalWrite(led1, yLedState);
    digitalWrite(led2, wLedState);
    digitalWrite(led3, yLedState);
    digitalWrite(led4, wLedState);
    digitalWrite(led5, yLedState);
    roundCount++;   
}

int getState(int testLed)
{
      int ledState;
      if (testLed == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    return ledState;
}

