#include "Drive.h"
#include <Arduino.h>
#include "Tone_note.h"
#include "Define.h"


void Drive::Init()
{
    pinMode(_rightWheelDir, OUTPUT);
    pinMode(_leftWheelDir, OUTPUT);
    pinMode(_rightWheelPwm, OUTPUT);
    pinMode(_leftWheelPwm, OUTPUT);
    pinMode(_pinBottomRight, INPUT);
    pinMode(_pinBottomLeft, INPUT);

}
void Drive::InitSensor() 
{
    Stop();
    //_initLeftValue = GetLeft();
    //_initRightValue = GetRight();
    _centerValue = GetRight() - GetLeft();
}

void Drive::Sensing()
{
    _rightValue = GetRight();
    _leftValue = GetLeft();
}


void Drive::Forward()
{
   
    delay(10);
    digitalWrite(_leftWheelDir, 1);
    digitalWrite(_rightWheelDir, 0);
    delay(10);
    analogWrite(_leftWheelPwm, Speed);
    analogWrite(_rightWheelPwm, Speed);
}

void Drive::Backward()
{
    Serial.println(__FUNCTION__);
    
    delay(10);
    digitalWrite(_leftWheelDir, 0);
    digitalWrite(_rightWheelDir, 1); 
    delay(10);
    analogWrite(_leftWheelPwm, Speed);
    analogWrite(_rightWheelPwm, Speed);
}
void Drive::Stop() 
{
    analogWrite(_leftWheelPwm, 0);
    analogWrite(_rightWheelPwm, 0);
}

void Drive::PivotTurnLeft() 
{
    if (Serial) Serial.println("Enter Pivot turn Left");
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    delay(10);
    digitalWrite(_leftWheelDir, 0);
    digitalWrite(_rightWheelDir, 0);
    delay(10);
    analogWrite( _leftWheelPwm, _turnHighSpeed);
    analogWrite( _rightWheelPwm, _turnHighSpeed);
    delay(120);
    analogWrite( _leftWheelPwm, _turnLowSpeed);
    analogWrite( _rightWheelPwm, _turnSpeed);
    delay(400);
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);

    if (Serial) Serial.println("Leave Pivot turn Left");
}

// Half Pivot Turn for JellibiAGV
void Drive::PivotTurnRight()
{
    if (Serial) Serial.println("Enter Pivot turn Right");
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    delay(10);
    digitalWrite(_leftWheelDir, 1);
    digitalWrite(_rightWheelDir, 1);
    delay(10);
    analogWrite( _rightWheelPwm, _turnHighSpeed);
    analogWrite( _leftWheelPwm, _turnHighSpeed);
    delay(120);
    analogWrite( _rightWheelPwm, _turnLowSpeed);
    analogWrite( _leftWheelPwm, _turnSpeed);
    delay(570);
    analogWrite( _leftWheelPwm, 0);
    analogWrite( _rightWheelPwm, 0);
    if (Serial) Serial.println("Leave Pivot turn Right");
}


void Drive::AlarmBeep()
{
    tone(s_Buzzer, NOTE_FS4,300);
    delay(300);
}
int Drive::LineTrace() 
{
    int16_t turnSpeed = ((_rightValue-_leftValue) - _centerValue)/12;
    int16_t leftSpeed = Speed + turnSpeed;
    int16_t rightSpeed = Speed - turnSpeed;

    digitalWrite( _leftWheelDir, (leftSpeed > 0)?1:0);
    digitalWrite( _rightWheelDir, (rightSpeed > 0)?0:1);
    analogWrite( _leftWheelPwm, round(abs(leftSpeed)));
    analogWrite( _rightWheelPwm, round(abs(rightSpeed)));
    
    int servoAngle = SERVO_MIDDLE_ANGLE - turnSpeed;
    if(servoAngle>120) servoAngle = SERVO_RIGHT_ANGLE;
    else if(servoAngle<20) servoAngle = SERVO_LEFT_ANGLE;
    
    if(_sonalCon.SonalRead() < 7){
      Stop();
      delay(600);
    }
    return servoAngle;

}
uint16_t Drive::LineCounter() //사용안함
{
     
    static uint8_t bSignalHigh = 0;
    if (_rightValue > LINEDETECT_THRESHOLD_MIN && _leftValue > LINEDETECT_THRESHOLD_MIN) {
        if (bSignalHigh==0) {
            _nLineCounter++;
            flag = 1;
            Serial.println(String("LineCounter: ") + String(_nLineCounter));
            bSignalHigh = 1;
        }
    } else if (_rightValue < BLANKDETECT_THERSHOLD_MAX && _leftValue < BLANKDETECT_THERSHOLD_MAX) {
        if (bSignalHigh) {
            bSignalHigh = 0;
        }
    }
    return _nLineCounter;
}

void Drive::ResetLineCounter()
{
    _nLineCounter = 0;
}


int16_t Drive::GetLeft() 
{
    return analogRead(_pinBottomLeft);
}

int16_t Drive::GetRight() 
{
    return analogRead(_pinBottomRight);
}
