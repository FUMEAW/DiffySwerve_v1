#include <PCA9685.h>
#include <Encoder.h>
#include <PID_v1.h>
//384.5 ticks per rotation

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(2, 3);

double Setpoint, Input, Output;
//PLS TUNE
double Kp=0.5, Ki=0.5, Kd=0.03;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

const int en = 13;
const int in1 = 11;
const int in2 = 10;
unsigned long exec = millis();
void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  Input = 10;
  Setpoint = 400;
  myPID.SetMode(AUTOMATIC);
}
long oldPosition  = 0;
void loop() {
  // put your main code here, to run repeatedly:
 
  myPID.Compute();
  digitalWrite(en, HIGH);
  analogWrite(in2, LOW);
  analogWrite(in1, map(Output, 0, 255, 0, 250));
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    int ticks = abs(abs(newPosition) - abs(oldPosition));
    //difference in distance.
    if ((millis() - exec) > 1000){
      int rpm = (((ticks/384.5) / (millis() - exec)) * 60000);
      Serial.println(rpm);

      Input = rpm;
      myPID.Compute();
      
      exec = millis();
      oldPosition = newPosition;
    }
  }
}
