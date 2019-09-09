//Tx

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

//PIN on board
int Thrust;    // value from the analog pin  (used for throttle)
int Pitch;     // value from the analog pin  (used for pitching)
int Roll;      // value from the analog pin  (used for rolling)
int Yaw;       // value from the analog pin  (used for yawing)
int CamTilt;   // value from the analog pin  (used for tilting camera)
int CamPan;    // value from the analog pin  (used for panning camera)
int Land;      // value from the analog pin  (used for landing gear)

//-------- system config -----------------
byte mac[] = {0x2A, 0x00, 0x22, 0x22, 0x22, 0x22};
IPAddress ip(192, 168, 1, 20);
const unsigned int localPort = 9631;

char remote_IP[] = "192.168.1.10";  //assign IP address
int remote_Port = 1369; //Assign a port to talk over

char UDP_TX_Buffer[80]; // For future use...

char recvdBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
//char UDP_RX_Buffer[80]; // For future use...
EthernetUDP Udp;  //create a UDP Object
//-----------------------------------------


void setup()
{

  Ethernet.begin(mac, ip);  // Set up the Ethernet Shield
  Udp.begin(localPort);     // Open a socket for this port
}

void loop() {
int recvdSize = Udp.parsePacket();



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



delay(1000);

   Udp.beginPacket(remote_IP, remote_Port);
   Udp.write(UDP_TX_Buffer);
   Udp.endPacket();
   strcpy(UDP_TX_Buffer,"");
   delay(200);
}

void remote_Send(int data)
{
  itoa(data, UDP_TX_Buffer, 10);
  Udp.beginPacket(remote_IP, remote_Port); // REMOTE IP/Port
  Udp.write(UDP_TX_Buffer);                         //Byte/string
  Udp.endPacket();
  delay(200);

}
