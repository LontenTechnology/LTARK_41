const int trac1 = A4; //Sort from the leftmost direction of the front of the vehicle (sensors)
const int trac2 = A5; 

void setup() {
  Serial.begin(9600);  //initialization Serialport
  pinMode(trac1, INPUT);
  pinMode(trac2, INPUT);
}

void loop()
{
   int data[2];             
   data[0] = digitalRead(trac1);//the left
   data[1] = digitalRead(trac2);
   Serial.print(data[0]);
   Serial.print("---");
   Serial.print(data[1]);
   Serial.println();
   delay(1000);
}
