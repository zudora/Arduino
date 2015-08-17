int indLed = 2; //traces go right and then over right shoulder as indicator
int anLed1 = 5;
int anLed2 = 6;
int digLed3 = 7;  //this is the digital one
int anLed4 = 9;
int anLed5 = 10;
int anLed6 = 11;

int blink1 = 0; //used for executing patterns
int blink2 = 0;
int blink3 = 0;
int delayVal = 0;

int i = 0; //counter

int ledLow = 8; //return traces from all LEDs to low

int run = 3; //one side of switch. Other side goes to battery board

//don/t know how to deal with battery hookup. Not sure this pin needs to be mentioned or initialized.
int powerPin = 4; //one side of battery. Other goes to ground 

int randStart;
int cycleNum;


void setup()
{
  pinMode(indLed, OUTPUT);
  pinMode(anLed1, OUTPUT);
  pinMode(anLed2, OUTPUT);
  pinMode(digLed3, OUTPUT);
  pinMode(anLed4, OUTPUT);
  pinMode(anLed5, OUTPUT);
  pinMode(anLed6, OUTPUT);
  pinMode(ledLow, OUTPUT);

  pinMode(run, INPUT);
  digitalWrite(run, HIGH);  //preset switch to off

  digitalWrite(ledLow, LOW);

}

void loop()
{
  checkSwitch();
  indicator(); 
}

void checkSwitch();
{
  if (digitalRead(run)==LOW)
  {
  //initialize random value
    randStart=random(0,5); //random between 0 and 4

    for (cycle=0, cycle<=4, cycle=cycle+1)
    {
     
     randStart=randStart+1
      if (randStart>=4) randStart=0; 
    }
  }

}


void indicator()
{
  //blink indicator light now and then
  digitalWrite(indLed, LOW);
  delay(50);
  digitalWrite(indLed, HIGH);
  delay(3000); 
}



