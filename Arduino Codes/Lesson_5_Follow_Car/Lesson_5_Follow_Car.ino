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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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

void loop() {
   DM=checkdistance();  //Get the current distance
   if(DM<=10){
    Serial.println("stop");
    pause();
    delay(300);
    DM = checkdistance();
    delay(500);
  }
  else { //There are no obstacles ahead, the car is moving forward
    Serial.println("forward");
    forward();
  }
 }
//===============
// forward
//===============
void forward(){
   Motor(Move_Forward, Speed1, Speed4);
}
//===============
// back
//===============
void backward(){
   Motor(Move_Backward, Speed1,Speed4);
}
//===============
// stop
//===============
void pause(){
   Motor(Stop, 0, 0);
}

