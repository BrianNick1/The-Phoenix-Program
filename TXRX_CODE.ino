#include <Servo.h>    //Servo library

Servo ESC;        // create servo object to control the ESC
Servo Elevon;     // create servo object to control the Elevon
Servo Aileron;    // create servo object to control the Aileron
Servo Rudder;     // create servo object to control the Rudder
Servo Tilt;       // create servo object to control the Tilt
Servo Pan;        // create servo object to control the Pan
Servo Gear;       // create servo object to control the Landing Gear

int Thrust;    // value from the analog pin  (used for throttle)
int Pitch;     // value from the analog pin  (used for pitching)
int Roll;      // value from the analog pin  (used for rolling)
int Yaw;       // value from the analog pin  (used for yawing)
int CamTilt;   // value from the analog pin  (used for tilting camera)
int CamPan;    // value from the analog pin  (used for panning camera)
int Land;      // value from the analog pin  (used for landing gear)


void setup() 
{ 
  ESC.attach(9,1000,2000);  // (pin, min pulse width, max pulse width in microseconds) 
  Elevon.attach(1);         // (pin, min pulse width, max pulse width in microseconds) 
  Aileron.attach(2);        // (pin, min pulse width, max pulse width in microseconds) 
  Rudder.attach(3);         // (pin, min pulse width, max pulse width in microseconds) 
  Tilt.attach(4);           // (pin, min pulse width, max pulse width in microseconds) 
  Pan.attach(5);            // (pin, min pulse width, max pulse width in microseconds) 
  Gear.attach(6);           // (pin, min pulse width, max pulse width in microseconds) 
} 
  
void loop() 
{ 
  Thrust = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  Pitch = analogRead(A1);    // reads the value of the Joystick (value between 0 and 1023)
  Roll = analogRead(A2);     // reads the value of the Joystick (value between 0 and 1023)
  Yaw = analogRead(A3);      // reads the value of the Joystick (value between 0 and 1023)
  CamTilt = analogRead(A4);  // reads the value of the Joystick (value between 0 and 1023)
  CamPan = analogRead(A5);   // reads the value of the Joystick (value between 0 and 1023)
  Land = analogRead(A6);     // reads the value of the Joystick (value between 0 and 1023)

  Thrust =map(Thrust, 0, 1023, 0, 180);       // scale it to use it with the servo library (value between 0 and 180)
  Pitch =map(Pitch, 0, 1023, 10, 170);        // scale it to use it with the servo library (value between 0 and 180)
  Roll =map(Roll, 0, 1023, 10, 170);          // scale it to use it with the servo library (value between 0 and 180)
  Yaw =map(Yaw, 0, 1023, 10, 170);            // scale it to use it with the servo library (value between 0 and 180)
  CamTilt =map(CamTilt, 0, 1023, 10, 170);    // scale it to use it with the servo library (value between 0 and 180)
  CamPan =map(CamPan, 0, 1023, 10, 170);      // scale it to use it with the servo library (value between 0 and 180)
  Land =map(Land, 0, 1023, 10, 170);          // scale it to use it with the servo library (value between 0 and 180)

  ESC.write(Thrust);      // Send the signal to the ESC
  Elevon.write(Pitch);   // Send the signal to the Elevons
  Aileron.write(Roll);   // Send the signal to the Ailerons
  Rudder.write(Yaw);     // Send the signal to the Split Rudder
  Tilt.write(CamTilt);   // Send the signal to the Tilt servo
  Pan.write(CamPan);     // Send the signal to the Pan servo
  Gear.write(Land);     // Send the signal to the Landing Gear servo
  
    delay(50);
}

                  
