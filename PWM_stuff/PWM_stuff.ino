/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 This example code is in the public domain.
 */

int led = 3;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  //loop through duty cycles
  //duty is percentage of time pin is high
  //effective per-cycle high time is full_cycle/duty
  //reps are the number of cycles to run it
  
  //number of milliseconds in a full on-off cycle
  float full_cycle = 3;
  int num_reps = 100;
  
  for (int duty = 0; duty <=100; duty++)
  {
    for (int reps_done = 0; reps_done < num_reps; reps_done++)
    {    
      float high_time = full_cycle * duty / 100;
      digitalWrite(led, HIGH);      
      delay(high_time);
      digitalWrite(led, LOW);
      delay (full_cycle - high_time) ;
    }  
  }
}

