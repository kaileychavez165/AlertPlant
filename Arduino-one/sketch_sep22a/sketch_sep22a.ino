#define motor1  12
#define motor2  13

void setup() {

  // put your setup code here, to run once:
  //pick two pins
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  //turn it on
  digitalWrite(motor1, HIGH); 
  //Have to be different
  digitalWrite(motor2,LOW); 
  //one sec delay
  delay(1000);
  //turn it off
  digitalWrite(motor1, LOW); 
  //Same stops
  digitalWrite(motor2,LOW); 
  //delays for 2 sec
  delay(2000); 

}
