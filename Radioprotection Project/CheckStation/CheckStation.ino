
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>         // needed for Arduino versions later than 0018


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 79, 100);
byte packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

int i, j, k;

EthernetUDP Udp;

void setup() {

  Ethernet.begin(mac,ip);
  Udp.begin(5005);
  Serial.begin(9600);

  
  /* {buttonPin = 2, emergencyPin = 3, greenLedPin = 4, orangeLedPin = 5, redLedPin = 6, alarm1Pin = 7, alarm2Pin = 8 }*/
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  for(i=4; i<9; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

}

void loop() {

  int packetSize = Udp.parsePacket();
  byte transmit[3]  = {0, 0, 0};
  int  theBit = 0;
  byte theByte = 0;
  int written = 0, received = 0;


  if(packetSize)
  {
    for(i=2; i<9; i++){
      bitWrite(transmit[0], i-2, digitalRead(i));
    }  

    Serial.print("transmit[0]  = ");
    Serial.println(transmit[0] );
    
    
    received = Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    
    for(i=0; i<3; i++){ 
       for (k=0; k<8; k++){
         theBit = (*(transmit + i) & ( 1 << k )) >> k;
         Serial.print(theBit);
       }
      Serial.println("");
     }

    

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    written = Udp.write(transmit, 3);
    Serial.print(written);
    Serial.println("bytes written ");

 
    Udp.endPacket();

    delay(1000);


  }//end of if(packetsize){}
}//end of loop







