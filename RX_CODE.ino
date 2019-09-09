//Rx

#include <SPI.h>    // ( Net surf for SPI pins )
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Servo.h>    //Servo library

Servo ESC;        // create servo object to control the ESC
Servo Elevon;     // create servo object to control the Elevon
Servo Aileron;    // create servo object to control the Aileron
Servo Rudder;     // create servo object to control the Rudder
Servo Tilt;       // create servo object to control the Tilt
Servo Pan;        // create servo object to control the Pan
Servo Gear;       // create servo object to control the Landing Gear

// initialize the library with the numbers of the interface pins


//Device IP & MAC (Variable)
byte mac[] = { 0x2A, 0x00, 0x22, 0x22, 0x22, 0x44 }; //(Naming rules)
IPAddress ip(192, 168, 1, 10);                       //(IP rules according to subnet/gateway)

// -------- Do not change the section below -----------------
const unsigned int localPort = 1369;    // Process ID port (TCP/UDP Alternate port = 8888)
char remote_IP1[]="192.168.1.20";
int remote_Port1 = 9631;
char UDP_TX_Buffer[80];
char recvdBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; // Buffer for incoming data
EthernetUDP Udp;  //Class variable (Initiates process of UDP)
// ------------------------------------------------------------

void setup()
{

  Ethernet.begin(mac, ip);   // Set up the Ethernet Shield
  Udp.begin(localPort);      // Open a socket for this port
  Serial.begin(9600);        // Set up serial monitor with PC4
  delay(500);

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
 
  //transmit
int recvdSize = Udp.parsePacket();

int Thrust;    // value from the analog pin  (used for throttle)
int Pitch;     // value from the analog pin  (used for pitching)
int Roll;      // value from the analog pin  (used for rolling)
int Yaw;       // value from the analog pin  (used for yawing)
int CamTilt;   // value from the analog pin  (used for tilting camera)
int CamPan;    // value from the analog pin  (used for panning camera)
int Land;      // value from the analog pin  (used for landing gear)
  
  ESC.write(Thrust);      // Send the signal to the ESC
  Elevon.write(Pitch);   // Send the signal to the Elevons
  Aileron.write(Roll);   // Send the signal to the Ailerons
  Rudder.write(Yaw);     // Send the signal to the Split Rudder
  Tilt.write(CamTilt);   // Send the signal to the Tilt servo
  Pan.write(CamPan);     // Send the signal to the Pan servo
  Gear.write(Land);     // Send the signal to the Landing Gear servo
  
    delay(50);


 if (Udp.available()) {
    IPAddress remote = Udp.remoteIP();
    Udp.read(recvdBuffer, UDP_TX_PACKET_MAX_SIZE);
    recvdBuffer[recvdSize] = '\0';
    recvdSize -= 8;               // Gets rid of the message header

 }
}

void remote_send(int data)
{
itoa(data,UDP_TX_Buffer,10);
Udp.beginPacket(remote_IP1,remote_Port1);
Udp.write(UDP_TX_Buffer);
Udp.endPacket();
delay(200);

}
