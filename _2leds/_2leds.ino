int led1 = 9;
int led2 =10;
int i=0;   //brightness

void setup(){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

}

void loop(){
  for (i=255; i>=0; i=i-3)
  {
    analogWrite(led1, i);
    delay(10);
  }
  for (i=0; i<=255; i=i+100)
  {
    analogWrite(led1, i);
    delay(10);
  }
  
  digitalWrite(led1, HIGH);
  delay(10);
  
  for (i=255; i>=0; i=i-1)
  {
    
    analogWrite(led2, i);
    delay(6);
   
  }
  
  for (i=0; i<=255; i=i+4)
  {
    analogWrite(led2, i);
    delay(8);
  }
  digitalWrite(led2, HIGH);
  delay(50);
}


