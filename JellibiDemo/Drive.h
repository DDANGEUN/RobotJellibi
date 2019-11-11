#ifndef __DRIVE_H__
#define __DRIVE_H__
#include <Arduino.h>

#include "Define.h"
#include "SonalControl.h"



class Drive
{
private: 
    uint8_t _rightWheelPwm;
    uint8_t _rightWheelDir;
    uint8_t _leftWheelPwm;
    uint8_t _leftWheelDir;
    uint8_t _pinBottomRight;
    uint8_t _pinBottomLeft; 

    int16_t  _rightValue;    
    int16_t  _leftValue; 
    int16_t  _centerValue;
    

    uint16_t _nLineCounter;

    const int _turnLowSpeed = TURN_INSIDE_WHEEL_SPEED;
    const int _turnSpeed = TURN_OUTSIDE_WHEEL_SPEED;
    const int _turnHighSpeed = TURN_INITIAL_WHEEL_SPEED;

public:

   Drive(){
     _rightWheelPwm = s_RightWheelPWM;
     _rightWheelDir = s_RightWheelDir;
     _leftWheelPwm = s_LeftWheelPWM;
     _leftWheelDir = s_LeftWheelDir;
     _pinBottomRight = s_SensorBottomRight;
     _pinBottomLeft = s_SensorBottomLeft;
     _nLineCounter = 0;
   }


    
   int Speed = NORMAL_DRIVE_SPEED;
   bool flag = 0;
   SonalControl _sonalCon;
   
   void Init();
   void InitSensor();
   void Sensing();
   
   void Forward();
   void Backward();
   void Stop();

   void PivotTurnLeft();
   void PivotTurnRight(); 
   
   int LineTrace();
   uint16_t LineCounter();
   void ResetLineCounter();
   void AlarmBeep();

   int16_t GetLeft();
   int16_t GetRight();
    
};

#endif//__DRIVE_H__
