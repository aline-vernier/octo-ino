#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>

#include <Classes.h>
#include <SPI.h>         // needed for Arduino versions later than 0018


const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 4;  //led indicator pin
volatile int state = LOW;

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 79, 100);
//unsigned int localPort = 5005;      


State here(4, ip, mac);


/*char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged; state =";       // a string to send back
char  On[] = "On";       // a string to send back
char Off[] = "Off";

EthernetUDP Udp;*/

void setup() {
  // start the Ethernet and UDP:
//  Ethernet.begin(mac,ip);
 // Udp.begin(localPort);

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(0, blink, CHANGE); //INTERRUPT 0 ON PIN 2
  
}

void loop() {
  // if there's data available, read a packet
/*  int packetSize = Udp.parsePacket();
  digitalWrite(ledPin, state);
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

  }*/
  int machine = here.MState;
  String sentMessage;
  String remote;
  char answer[] = "Ich liebe Dich.";
 
  
  switch(machine){
    case 0:
      here.init();
      delay(1000);
    break;
    
    case 2:
      sentMessage = here.talkback(answer);
      Serial.println(sentMessage);
    break;
    
    case 1:
      remote = here.read();
       if(remote){
     Serial.println(remote);
     }
    break;
    
   


  }
  Serial.println(machine);
  delay(2000);
  
  
}

void blink()
{
  state = !state;
}



