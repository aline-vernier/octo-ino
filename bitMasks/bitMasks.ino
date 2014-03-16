
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>         // needed for Arduino versions later than 0018


const int buttonPin = 2;    // the number of the pushbutton pin
const int emergencyPin = 3;

const int greenLedPin = 4;  //led indicator pin
const int orangeLedPin = 5;
const int redLedPin = 6;
const int alarm1Pin = 7;
const int alarm2Pin = 8;

volatile int state = LOW;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 79, 100);

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,



EthernetUDP Udp;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(5005);

  Serial.begin(9600);

}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  int i;
  int currentState = 0;
  byte transmit[3]  = {0b01110110, 0, 0};
  int theBit ;
  int k;
  int written=0;

 // Serial.println("");


//  Serial.println(transmit);
  
  digitalWrite(greenLedPin, state);
  if(packetSize)
  {
    Serial.println("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
  //  Serial.println("Contents:");
    for (k=0; k<8; k++){
      theBit = (packetBuffer[0] & ( 1 << k )) >> k;
      Serial.print(theBit);
  }
     Serial.println("");
      for (k=0; k<8; k++){
      theBit = (packetBuffer[1] & ( 1 << k )) >> k;
      Serial.print(theBit);
  }
      Serial.println("");
   // currentState = atoi(packetBuffer);
   // Serial.println(currentState);
    

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    written = Udp.write(transmit, 3);
    Serial.print("bytes written ");
    Serial.println(written);
 
    Udp.endPacket();

    delay(1000);

  }
}







