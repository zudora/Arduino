/*
 PWM Fade

Fading using software PWM
 
 */

const int led = 9;           // the pin that the LED is attached to

int ledState = HIGH; 

//get current time
unsigned long Timer;
unsigned long last_time;

const float full_cycle = 2;  //number of milliseconds in a full on-off cycle   -- or microseconds
const int num_reps = 100;   //number of off-on cycles and thus the time spent at a voltage level
const int tick_size = 30;   //micros. Smallest on period

struct Pin_Data
{
  int pinNum;
  int pinState;
  long ticksLeft;
};

typedef struct Pin_Data pinData[5];
        
// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);   
}

// the loop routine runs over and over again forever:
void loop() {

  //On start, and after each tick, generate data package for each pin: pin number and state.
  //To determine state for each pin, check remaining number of ticks for current state. If time has expired, get next state.
  
  //Record start time when initializing. We use tick size for checking timer. Loop constantly checks to see if tick time has passed.
  //Each tick, send all data to pins. Some pins will not get data because they don't change state. 

  Timer = micros();  

  if (Timer - last_time >= tick_size)
  {
    
    
    last_time = Timer;     
  }
  
  for (int fadeRiseCycles = 0; fadeRiseCycles < 5; fadeRiseCycles++)
  { 
    int ledOpposite;
    if (ledState == HIGH)
    {
      ledOpposite = LOW;
    }
    else
    {
      ledOpposite = HIGH;
    }
    
    for (int duty = 0; duty <=100; duty++)
    {          
      //percentage of cycle spent on and off, when ledState = HIGH
      int full_cycle = 3;
      float first_time = full_cycle * duty / 100;
      float second_time = full_cycle - first_time;
      
      for (int reps_done = 0; reps_done < num_reps; reps_done++)
      {             
        
        digitalWrite(led, ledState);           
        delay(first_time);
        digitalWrite(led, ledState);
        delay (second_time) ;

      }  
    }
    //flip ledState for next side
    ledState = ledOpposite;
  }
}
