#include <ams_as5048b.h>
#include <Wire.h>
//unit consts
#define U_RAW 1
#define U_TRN 2
#define U_DEG 3
#define U_RAD 4
#define U_GRAD 5
#define U_MOA 6
#define U_SOA 7
#define U_MILNATO 8
#define U_MILSE 9
#define U_MILRU 10

AMS_AS5048B mysensor;
// Motor variables
int motorSpeed = 127;
const int motorPin = 2; // Adjust this to your motor's pin
unsigned long lastTime;

void setup() {
	//Start serial
	Serial.begin(57600);
	while (!Serial) ; //wait until Serial ready
  // Set the I2C SDA and SCL pins for Wire2
	//Start Wire object. Unneeded here as this is done (optionally) by the AMS_AS5048B object (see lib code - #define USE_WIREBEGIN_ENABLED)
	Wire.begin();
	//init AMS_AS5048B object
	mysensor.begin();
	//consider the current position as zero
	mysensor.setZeroReg();

//Motor
  analogWriteFrequency(motorPin, 500);
  analogWriteResolution(8);
  analogWrite(motorPin, motorSpeed);
}

void loop() {
lastTime=millis();
	//print to serial the raw angle and degree angle every 2 seconds
	//print 2 times the exact same angle - only one measurement
	//Serial.print("Angle sensor raw : ");
//	Serial.println(mysensor.angleR(U_RAW, true), DEC);
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    //Serial.println(input[0]);
    processMotorInput(input[0]);
  }
 
  mysensor.angleR(U_RAW, true);
  //Serial.println(mysensor.getDiagReg());
	Serial.print("Angle degree : ");
	Serial.println(mysensor.angleR(U_DEG, false), DEC);

	while(millis()-lastTime<500);
}
void processMotorInput(char input) {
  switch (input) {
    case 'm':
      motorSpeed = min(motorSpeed + 5, 255);
      analogWrite(motorPin, motorSpeed);
      break;
    case 'n':
      motorSpeed = max(motorSpeed - 5, 127);
      analogWrite(motorPin, motorSpeed);
      break;
    case 's':
      motorSpeed = 127;
      analogWrite(motorPin, motorSpeed);
      break;
    default:
      Serial.println("Invalid input");
      break;
  }
}
