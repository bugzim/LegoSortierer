#include <Servo.h>

const int BUTTON = 8;
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 6;
const int motorPin = 2;

int toggle = -1;
int angle;
Servo servo;

void setup()
{

    Serial.begin(9600);

    servo.attach(motorPin);

    pinMode(buzzerPin, OUTPUT);

    pinMode(07, OUTPUT);

    pinMode(12, OUTPUT);

    pinMode(13, OUTPUT);

    pinMode(A0, INPUT);

    pinMode(BUTTON, INPUT);

    pinMode(trigPin, OUTPUT);

    pinMode(echoPin, INPUT);

}

 

void loop()

{
  digitalWrite(motorPin, HIGH);
  getSwitch();
  while(toggle == 1){
    measure();
    getSwitch();
  }
}

void getSwitch(){
  if(digitalRead(BUTTON) == HIGH){
    toggle *= -1;
    wait();
  }
}

void measure()
{
  servo.write(90);
  float distance = measureDistance();
  if(distance < 45){
    tone(buzzerPin, 1000);
    expressColor('r');
    wait();
    noTone(buzzerPin);
    rgbOff();
    shortWait();
  }
  else if(distance < 60){
    longWait();
    measureColor();
  }
}

void renderValue(int value){
  for(int i = 0; i < value; i++){
    Serial.print("|");
  }
  Serial.println();
}

float measureDistance()
{
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.343)/2;
  //Serial.print("Distanz: ");
  //Serial.println(distance);
  shortWait();
  return distance;
}
 

void blink(char color){
  expressColor(color);
  shortWait();
  rgbOff();
  wait();
}

void measureColor(){

  double rotFaktor = 0.5;

  double gruenFaktor = 0.8;

  double blauFaktor = 1;

  //Serial.println("-----------------------------------------------");

  double baseline = analogRead(A0);
  
  shortWait();

  expressColor(true, false, false);

  shortWait();

  double rot = (analogRead(A0)-baseline) * rotFaktor;

  //Serial.print("r: ");

  //Serial.println(rot);

  shortWait();

  rgbOff();

  expressColor(false, true, false);

  shortWait();

  double gruen = (analogRead(A0)-baseline) * gruenFaktor;

  //Serial.print("g: ");

  //Serial.println(gruen);

  shortWait();

  rgbOff();

  expressColor(false, false, true);

  shortWait();

  double blau = (analogRead(A0)-baseline) * blauFaktor;

  //Serial.print("b: ");

  //Serial.println(blau);

  shortWait();

  rgbOff();

  char colorMeasured = color(rot, gruen, blau);

  //Serial.print("-> ");

  Serial.println(colorMeasured);

  expressColor(colorMeasured);
  sortColor(colorMeasured);

  //longWait();

  rgbOff();

}

void shortWait(){

  delay(50);

}

void wait(){

  delay(400);

}

void longWait(){

  delay(1000);

}

void sortColor(char color){
  if(color == 'w'){
    servo.write(120);
  }
  else if(color == 'r'){
    servo.write(140);
  }
  else if(color == 'y'){
    servo.write(160);
  }
  else if(color == 'g'){
    servo.write(60);
  }
  else if(color == 'c'){
    servo.write(40);
  }
  else if(color == 'b'){
    servo.write(20);
  }
  else if(color == 'm'){
    servo.write(1);
  }
  longWait();
  servo.write(90);
  longWait();
}
 

void expressColor(char color){

  if(color == 'w'){

    expressColor(true, true, true);

  }

  else if(color == 'r'){

    expressColor(true, false, false);

  }

  else if(color == 'y'){

    expressColor(true, true, false);

  }

  else if(color == 'g'){

    expressColor(false, true, false);

  }

  else if(color == 'c'){

    expressColor(false, true, true);

  }

  else if(color == 'b'){

    expressColor(false, false, true);

  }

  else if(color == 'm'){

    expressColor(true, false, true);

  }

  else{

    rgbOff();

  }

}

 

void expressColor(bool r, bool g, bool b){

  if(r == true){

    digitalWrite(13, HIGH);

  }

  else{

    digitalWrite(13, LOW);

  }

  if(g == true){

    digitalWrite(12, HIGH);

  }

  else{

    digitalWrite(12, LOW);

  }

  if(b == true){

    digitalWrite(07, HIGH);

  }

  else{

    digitalWrite(07, LOW);

  }

}

 

void rgbOff(){

  expressColor(false, false, false);

}

 

char color(double r, double g, double b){

  if(muchBrighter(r, g)){

    if(muchBrighter(r, b)){

      return 'r';

    }

    else if(muchBrighter(b, r)){

      return 'b';

    }

    else{

      return 'm';

    }

  }

  else if(muchBrighter(g, r)){

    if(muchBrighter(g, b)){

      return 'g';

    }

    else if(muchBrighter(b, g)){

      return 'b';

    }

    else{

      return 'c';

    }

  }

  else if(muchBrighter(b, r)){

    return 'b';

  }

  else if(muchBrighter(r, b)){

    return 'y';

  }

  else{

    return 'w';

  }

}

 

bool muchBrighter(double c1, double c2){

  if(c2 == 0){

    if(c1 == 0){

      return false;

    }

    else return true;

  }

  double ratio = c1/c2;

  if(ratio > 1.2){

    return true;

  }

  return false;

}
