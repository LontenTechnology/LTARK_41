#include <AFMotor.h>
 
AF_DCMotor motor1(1);
AF_DCMotor motor4(4);
 
void setup() 
{
  //Set initial speed of the motor & stop
  motor1.setSpeed(200);
  motor4.setSpeed(200);
  motor1.run(RELEASE);
  motor4.run(RELEASE);
}
 
void loop() 
{
  motor1.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(200); 
  motor4.setSpeed(200); 
  delay(2000);
  motor1.run(RELEASE);
  motor4.run(RELEASE);
  delay(2000);
  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(200);
  motor4.setSpeed(200); 
  delay(2000);
  motor1.run(RELEASE);
  motor4.run(RELEASE);
  delay(2000);
}
