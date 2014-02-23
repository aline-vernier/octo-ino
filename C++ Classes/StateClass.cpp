
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "Arduino.h"
#include "StateClass.h"
#include "string.h"

State::State(int pin, IPAddress ip, byte * mac)
{
  MState = 0; 
  pinMode(pin, OUTPUT);
  _pin = pin;
  _ip = ip;
  _port = 5005;
  * _mac = * mac;
  IPAddress talkingToIP(0,0,0,0);



  char _packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
  char  _ReplyBuffer[] = "Yay! That's the Arduino talking back!";       // a string to send back
  char  _On[] = "On";       // a string to send back
  char _Off[] = "Off";
  EthernetUDP _udp;



}

void State::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void State::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}

void State::init()
{

  Ethernet.begin(_mac, _ip);
  _udp.begin(_port);
 // if(Ethernet.begin(_mac)==1){
  MState = 1; 
 // }
 // else{ MState = 0;}
 
}

IPAddress State::readIP()
{
  // if there's data available, read a packet
 int _packetSize = _udp.parsePacket();
 IPAddress _remote(0,0,0,0);
  if(_packetSize)
  {
    _remote = _udp.remoteIP(); 
    _udp.read(_packetBuffer,UDP_TX_PACKET_MAX_SIZE);

    MState = 2;

  }
  else{
    MState = 1;
  }
  return _remote;
    
}

String State::read()
{
  // if there's data available, read a packet
 int _packetSize = _udp.parsePacket();
 IPAddress _remoteIP(0,0,0,0);
  String _currentChat = "no blabla";
 
 String _remote = "no remote ip";
  if(_packetSize)
  {
    _remoteIP = _udp.remoteIP();
    talkingToIP = _udp.remoteIP();
   // _remote = String(talkingToIP);
    _udp.read(_packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    _currentChat = String(_packetBuffer);
    MState = 2;

  }
  else{
    MState = 1;
  }
  return _currentChat;
    
}

String State::talkback(char * answer)
{
  char * _answer = answer;
  _udp.beginPacket(_udp.remoteIP(), _udp.remotePort());

 // _Sanswer = String(_answer);
  _udp.write(_answer);

 
  _udp.endPacket();
  MState = 1;
  return String(_answer);
    
}



