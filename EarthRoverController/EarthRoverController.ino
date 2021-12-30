//Including server class to connect to.
#include <Servo.h>

//Servo Pin Numbers
int servoSteerPin = 2;
int servoDrivePin = 0;

//Servos
//Sevro settings. 90 stright, 30 full right, 150 full left
Servo servoSteer;

//Drive servo stop is 50, <50 is backwards, >50 is forward. 85 max forward.
Servo servoDrive;

int servoSteerSetting = 90;
int servoDriveSetting = 50;

//Voltage input
int analogPin = A0;
int voltage = 0;


void setup() {
  //Setting up the servos.
  servoSteer.attach(servoSteerPin);
  servoDrive.attach(servoDrivePin);

  //Setting up serial communications.
  Serial.begin(115200);

}

void loop() {
  
  //servoStear.write(30);
  servoSteer.write(servoSteerSetting);
  servoDrive.write(servoDriveSetting);
  delay(1);

  if (Serial.available()){
    String inCommand = Serial.readString();
    int indexLoc = inCommand.indexOf(',');
    int steer = inCommand.substring(0,indexLoc).toInt();
    int drive = inCommand.substring(indexLoc + 1, inCommand.length()).toInt();

    //Passing the setting to the command loop.
    servoSteerSetting = steer;
    servoDriveSetting = drive;
  }


  //Reading the voltage
  voltage = analogRead(analogPin);

  Serial.print("Current Setting: ");
  Serial.print(servoSteerSetting);
  Serial.print(",");
  Serial.print(servoDriveSetting);
  Serial.print(",");
  Serial.println(voltage);

}
