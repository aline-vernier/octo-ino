
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>         // needed for Arduino versions later than 0018


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 79, 100);
int i, j, k;


byte state[2]  = {0, 0};
int here[2] = {0, 0};
int hereNoDup[2] = {0, 0};

EthernetUDP Udp;

void setup() {

  Ethernet.begin(mac,ip);
  Udp.begin(5005);
  
//  Serial.begin(9600); //pour tests
  
  /* {buttonPin = 2, emergencyPin = 3, greenLedPin = 4, orangeLedPin = 5, redLedPin = 6, alarm1Pin = 7, alarm2Pin = 8 }*/
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  for(i=4; i<9; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

}

void loop() {

  int packetSize = Udp.parsePacket();
  int chkSm = 0;
  double dt = 0.0;

/*******************************************
L'etat du bouton est enregistre jusqu'a la 
reception d'une demande de paquets du systeme
central. Sur reception d'un paquet, l'etat 
du bouton est remis a zero.
********************************************/
    
  for(i=0; i<2; i++){
    if(digitalRead(i) && !hereNoDup[i]){
    here[i]=digitalRead(i+2);
    }
  }
/*******************************************
Verification continue de l'etat des boutons, 
evite le comptage double si le bouton est 
presse trop longtemps.
********************************************/

  if(packetSize)
   
  {
    Udp.read(state, UDP_TX_PACKET_MAX_SIZE);
    
    for(i=0;i<2;i++){
      bitWrite(state[0], i, here[i]);
      chkSm = chkSm + bitRead(state[0], i);
    }
    for(i=4; i<9; i++){
      digitalWrite(i, bitRead(state[0], i-2));
      chkSm = chkSm + bitRead(state[0], i-2);
    }/*Ecriture de l'etat du systeme sur les LED*/
    
    bitWrite(state[1], 7, chkSm%2);
    
    for(i=0;i<2;i++){
      for(j=0;j<8;j++){
        Serial.print(bitRead(state[i], j));
      }
    }
    Serial.println("");
    
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(state, 2);
    Udp.endPacket();

    for(i=0; i<2; i++){
      hereNoDup[i] = here[i];
      here[i] = 0;
    } 

 }//end of if(packetsize){}

 
 
}//end of loop







