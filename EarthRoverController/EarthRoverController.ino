//Including server class to connect to.
#include <Servo.h>
#include <Adafruit_ADS1X15.h>

//Servo Pin Numbers
int servoSteerPin = D5;
int servoDrivePin = D7;

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

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

void setup() {
  //Setting up the servos.
  servoSteer.attach(servoSteerPin);
  servoDrive.attach(servoDrivePin);

  //Setting up serial communications.
  Serial.begin(115200);

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
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
  float vOut = (0.00912 * voltage) - 0.0465;


  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  volts0 = ads.computeVolts(adc0);
  volts1 = (0.000464 * adc1) + 0.064; //ads.computeVolts(adc1);
  volts2 = (0.000464 * adc2) + 0.064; //ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

  //Serial.print("Current Setting: ");
  Serial.print(servoSteerSetting);
  Serial.print(",");
  Serial.print(servoDriveSetting);
  Serial.print(",");
  Serial.print(voltage);
  Serial.print(",");
  Serial.print(vOut);
  Serial.print(",");
  Serial.print(adc0);
  Serial.print(",");
  Serial.print(volts0);
  Serial.print(",");
  Serial.print(adc1);
  Serial.print(",");
  Serial.print(volts1);
  Serial.print(",");
  Serial.print(adc2);
  Serial.print(",");
  Serial.print(volts2);
  Serial.print(",");
  Serial.print(adc3);
  Serial.print(",");
  Serial.println(volts3);


  //Serial.println(adc1);

}
