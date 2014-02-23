#ifndef StateClass_h
#define StateClass_h

#include "Arduino.h"
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "StateClass.h"
#include "string.h"

class State
{
  public:
    State(int pin, IPAddress ip, byte * mac);
    void dot();
    void dash();
    void init();
    IPAddress readIP();
    String read();
    String talkback(char * answer);

    IPAddress talkingToIP;

    int MState;
  private:
    int _pin;
    IPAddress _ip;
    byte * _mac;
    int _port;
    EthernetUDP _udp;


    char _packetBuffer[]; //buffer to hold incoming packet,
  	char  _ReplyBuffer[];       // a string to send back
  	char  _On[];       // a string to send back
  	char _Off[];
    

};

#endif