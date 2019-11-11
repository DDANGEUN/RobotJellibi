#ifndef __SONALCONTROL_H__
#define __SONALCONTROL_H__
#include <Arduino.h>

#include "Define.h"

class SonalControl
{
private:
    uint8_t _trigPin;
    uint8_t _echoPin;
public:
    SonalControl(){
      _trigPin = s_Trig;
      _echoPin = s_Echo;
    }
    void Init();
    float SonalRead();

};

#endif//__SERVOCONTROL_H__
