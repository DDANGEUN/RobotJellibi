
#include <Arduino.h>
#include "Drive.h"
#include "Define.h"
Drive _drive;

#include "ServoControl.h"
ServoControl _servoCon;

#include "SonalControl.h"
SonalControl _sonalCon;


#include <SimpleTimer.h>
SimpleTimer timer;


bool line = 0;
int cnt = 0;
bool InLine = 0;


void search(){
     _drive.Stop();
     _servoCon.ServoMove();
     InLine = 0;
}
void setup() {
  // put your setup code here, to run once:
  
  _drive.Init();
  _drive.InitSensor();
  _servoCon.Init();
  _sonalCon.Init();
  

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  _drive.Sensing();
  int angle = _drive.LineTrace();
  _servoCon.WRITE(angle);

    
  if(line && InLine){
    timer.run();   
  }

 //시나리오
  int lineCnt = _drive.LineCounter();
  if(lineCnt == 1 && _drive.flag){  // 교차로 진입
    _drive.Stop();
    _drive.PivotTurnRight();
    _drive.flag = 0;
    line = 1; 
    InLine = 1;
    timer.setTimeout(1100,search);

  }
  else if(lineCnt == 2 && _drive.flag){ // 빠져나옴
    _drive.Stop();
    _drive.PivotTurnRight();
    _drive.flag = 0;
    line = 0;
  }
   else if(lineCnt == 3 && _drive.flag){ // 교차로 지나감
    _drive.flag = 0;
    line = 0;
  }
   else if(lineCnt == 4 && _drive.flag){ // 교차로 진입
    _drive.Stop();
    _drive.PivotTurnRight();
    _drive.flag = 0;
    line = 1;
    InLine = 1; 
    timer.setTimeout(1100,search);
  }
  else if(lineCnt == 5 && _drive.flag){ // 빠져나옴
    _drive.Stop();
    _drive.PivotTurnRight();
    _drive.flag = 0;
    line = 0;
    
  }
  else if(lineCnt == 6 && _drive.flag){ // 지나감, 초기화
    _drive.Stop();
    _drive.flag = 0;
    _drive.ResetLineCounter();
    line = 0;
  }

  if(_sonalCon.SonalRead() < 7){
   _drive.Stop();
   delay(600);
  }
}
