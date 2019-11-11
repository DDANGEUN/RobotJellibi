#ifndef __SERVOCONTROL_H__
#define __SERVOCONTROL_H__
#include <Arduino.h>
#include <Servo.h>
#include "Define.h"
#include "SonalControl.h"
#include "Drive.h"


class ServoControl
{
private:
    const int MOVE_STEP = 20;
    uint8_t _servoPin;
public:
    ServoControl(){
      _servoPin = s_Servo;
    }
    Servo _servo;
    void Init();
    bool ServoMove();
    void AlarmBeep();
    void WRITE(int n);
    SonalControl _sonalCon;
    Drive _drive;
   
};

#endif//__SERVOCONTROL_H__
