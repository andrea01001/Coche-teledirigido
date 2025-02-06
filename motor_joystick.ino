int speedPin=11; 
int dirPin1=12;
int dirPin2=13;
int speedMotor=250;
int yPin=A0;
int yVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(speedPin,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(yPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  yVal=analogRead(yPin);
  Serial.println(yVal);

  if(yVal<=550){
    //velocidad
    speedMotor=map(yVal,550,0,0,255);//varía la velocidad gradualmente

    Serial.println("positivo");
    digitalWrite(dirPin2,0);
    digitalWrite(dirPin1,1);//direcciones positiva y negativa
    analogWrite(speedPin, speedMotor);
    
  }

  if(yVal>550){
    //velocidad
    speedMotor=map(yVal,550,1023,0,255);//varía la velocidad gradualmente

    Serial.println("negativo");
    digitalWrite(dirPin1,0);//direcciones positiva y negativa
    digitalWrite(dirPin2,1);
    analogWrite(speedPin, speedMotor);
  }
  

}
