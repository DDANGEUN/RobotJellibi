
#include "ServoControl.h"
#include <Arduino.h>
#include "Tone_note.h"

void ServoControl::Init(){
   _servo.attach(_servoPin);
   _servo.write(SERVO_MIDDLE_ANGLE);
}
void ServoControl::AlarmBeep()
{
    tone(s_Buzzer, NOTE_FS4,300);
    delay(300);
}
bool ServoControl::ServoMove(){
   bool InReturn = 0;
   _drive.Speed = 50;   
   for ( int i =0; i < MOVE_STEP; i++) {
        int angle = map(i, 0, MOVE_STEP, SERVO_MIDDLE_ANGLE, 160);
        _servo.write(angle);
        if(_sonalCon.SonalRead() < 20){
         AlarmBeep();
         delay(100);
         InReturn = 1;
        }  
        delay(10);
   }
   
   for ( int i =0; i < MOVE_STEP; i++) {
        int angle = map(i, 0, MOVE_STEP, 160, SERVO_MIDDLE_ANGLE);
        _servo.write(angle);
        if(_sonalCon.SonalRead() < 20){
         AlarmBeep();
         delay(100);
         InReturn = 1;
        }  
        delay(10);
   }
   
  _drive.Speed = 65;
  return InReturn;
}

void ServoControl::WRITE(int n){
  _servo.write(n);
}
