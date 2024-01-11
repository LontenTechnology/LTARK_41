#include <Servo.h>
const int PWM2A = 11;      //M1 motor PWM signal pin
const int PWM0B = 5;       //M4 motor PWM signal pin
const int DIR_CLK = 4;     // Data input clock line
const int DIR_EN = 7;      //Equip the L293D enabling pins
const int DATA = 8;        // USB cable
const int DIR_LATCH = 12;  // Output memory latch clock

const int Move_Forward = 39;       //Move Forward
const int Move_Backward = 216;     //Move Backward
const int Left_Move = 116;         //Left translation
const int Right_Move = 139;        //Right translation
const int Stop = 0;                //Stop

int Speed1 = 255;//Set the default speed between 1 and 255
int Speed4 = 255;//Set the default speed between 1 and 255

void Motor(int Dir, int Speed1, int Speed4) {
  analogWrite(PWM2A, Speed1);  //Motor PWM speed regulation
  analogWrite(PWM0B, Speed4);  //Motor PWM speed regulation

  digitalWrite(DIR_LATCH, LOW);            //DIR_LATCH sets the low level and writes the direction of motion in preparation
  shiftOut(DATA, DIR_CLK, MSBFIRST, Dir);  //Write Dir motion direction value
  digitalWrite(DIR_LATCH, HIGH);           //DIR_LATCH sets the high level and outputs the direction of motion
}
Servo myservo;
volatile int DL;
volatile int DM;
volatile int DR;

float checkdistance() {
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  float distance = pulseIn(A0, HIGH) / 58.00;
  delay(10);
  return distance;
}


void Detect_obstacle_distance() {
  myservo.write(160);
  for (int i = 0; i < 3; i = i + 1) {
    DL = checkdistance();
    delay(100);
  }
  myservo.write(20);
  for (int i = 0; i<3; i = i + 1) {
    DR = checkdistance();
    delay(100);
  }
}

void setup(){
  myservo.attach(10);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(DIR_CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(DIR_EN, OUTPUT);
  pinMode(DIR_LATCH, OUTPUT);
  pinMode(PWM0B, OUTPUT);
  pinMode(PWM2A, OUTPUT);
  DL = 0;
  DM = 0;
  DR = 0;
  myservo.write(90);
}

void loop(){
  DM = checkdistance();
  if (DM < 30) {
    stopp();
    delay(1000);
    Detect_obstacle_distance();
    if (DL < 50 || DR < 50) {
      if (DL > DR) {
        myservo.write(90);
        turnL();
        delay(200);
        advance();

      } else {
        myservo.write(90);
        turnR();
        delay(200);
        advance();
      }
    } else {
      if (random(1, 10) > 5) {
        myservo.write(90);
        turnL();
        delay(200);
        advance();

      } else {
        myservo.write(90);
        turnR();
        delay(200);
        advance();
      }
    }
  } else {
    advance();
  }
}

void advance()    //  going forward
    {
     Motor(Move_Forward, Speed1, Speed4);
    }
void turnR()        //turning right(dual wheel)
    {
     Motor(Right_Move, Speed1, Speed4);
    }
void turnL()         //turning left(dual wheel)
    {
     Motor(Left_Move, Speed1, Speed4);
    }    
void stopp()        //stop
    {
     Motor(Stop, 0, 0);
    }
void back()         //back up
    {
     Motor(Move_Backward, Speed1,Speed4);
    }

