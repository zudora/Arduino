
int ledPin = 13; 	// LED is connected to digital pin 13
int switchPin = 2; 	// switch connected to digital pin 2
int switchValue; 	// a variable to keep track of when switch is pressed

void setup() 	 
{ 	 
  pinMode(ledPin, OUTPUT); 	// sets the ledPin to be an output
  pinMode(switchPin, INPUT); 	// sets the switchPin to be an input
  digitalWrite(switchPin, HIGH); 	// sets the default (unpressed) state of switchPin to HIGH
} 	 

void loop() 	// run over and over again
{ 	 
  switchValue = digitalRead(switchPin); 	// check to see if the switch is pressed
  if (switchValue == LOW) { 	// if the switch is pressed then,
    digitalWrite(ledPin, HIGH); 	// turn the LED on
  } 	 
  else { 	// otherwise,
    digitalWrite(ledPin, LOW); 	// turn the LED off
  } 	 
} 	 


