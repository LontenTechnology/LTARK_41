const int trac1 = A4; //Sort from the leftmost direction of the front of the vehicle (sensors)
const int trac2 = A5; 
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

void setup() {
  Serial.begin(9600);  //initialization Serialport
  pinMode(trac1, INPUT);
  pinMode(trac2, INPUT);
}

void loop()
{
  tracing(); 
}

void tracing()          
{
  int data[2];             
  data[0] = digitalRead(trac1);//the left
  data[1] = digitalRead(trac2);
  //High level - off state (without reflection) - black line - light not on; Low level - reception (reflection) - no black line - light on
  //No black lines detected on either side, straight ahead
  if(!data[0] && !data[1])     //00 Lighting
  {
     Motor(Move_Forward, Speed1, Speed4);
  }
  if(!data[0] && data[1])   //01
  {
     Motor(Left_Move, Speed1, Speed4);
  }
  //Black line detected on the left, turn left
  if(data[0] && !data[1])    //10
  {
     Motor(Right_Move, Speed1, Speed4);
  }
  if(data[0] && data[1])   //11
  {
    Motor(Stop, 0, 0);
  }
  Serial.print(data[0]);
  Serial.print("---");
  Serial.print(data[1]);
}
