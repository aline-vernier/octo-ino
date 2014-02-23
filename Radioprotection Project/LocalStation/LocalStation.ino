
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
unsigned int localPort = 5005;      



char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "this is my answer";     // an array to send back


EthernetUDP Udp;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(5005);

  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(emergencyPin, INPUT);

  pinMode(greenLedPin, OUTPUT);
  pinMode(orangeLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(alarm1Pin, OUTPUT);
  pinMode(alarm2Pin, OUTPUT);

  
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  digitalWrite(greenLedPin, state);
  if(packetSize)
  {
    Serial.print("Received packet of size ");
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
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);

 
    Udp.endPacket();

    delay(1000);

  }
}

void blink()
{
  state = !state;
}



