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

int switchPress; //tracks switch presses to choose which cycle is run. Resets when value reaches some limit


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
  switchPress=0;
}

void loop()
{
  checkSwitch();
  indicator();
}

void checkSwitch()
{
  if (digitalRead(run) == LOW);
  {
    if (switchPress=0)
    {
      //pattern1
      //      pin1 = 5; 
      //      pin2 = 7;
      //      pin3 = 9;
      //      delay = 100;
      //      
      pattern(5,7,9,500);
    } 

    if (switchPress = 1)
    {
      //pattern2
      //      pin1 = 11; 
      //      pin2 = 10;
      //      pin3 = 6;
      //      
      pattern(11,10,6,1000);
    }

    if (switchPress = 2)
    {
      //pattern3
      //      pin1 = 5; 
      //      pin2 = 7;
      //      pin3 = 11;
      //      
      pattern(7,5,11,300);

    }

    if (switchPress = 3)
    {
      //pattern4
      //pin1 = 9;
      //pin2 = 6;
      //pin3 = 0;
      pattern(9,6,0,200); 
    }

    if (switchPress = 4)
    {
      //pattern5
      //      pin1 = 10; 
      //      pin2 = 6;
      //      pin3 = 9;
      //      
      pattern(10,6,9,1000);
    }

    switchPress = switchPress + 1;
    if (switchPress > 4) switchPress = 0;
  }

}

void pattern(blink1, blink2, blink3, delayVal)
{
  for(i=1; i>=3; i=i+1)
  {
    //for each blink, check if pin is 0 then blink LED
    switch(i)
    {
      case 1:
        
        break;
        
      case 2:
      
        break;
        
      case 3:
        
        break;
    }
  }
  
}

void indicator()
{
  //blink indicator light now and then
  digitalWrite(indLed, LOW);
  delay(50);
  digitalWrite(indLed, HIGH);
  delay(2000); 
}






