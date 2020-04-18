//https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller

#include "testmode.h"
#include <Arduino.h>
#include "drive.h"
#include "HC595.h"
#include "hcsr04.h"




char command = 'S', oldCommand = 'S';
int velocity = 0;
byte state;
bool frontlight = false;
bool backlight = false;
int dir = 0, steer = 0,steer_ = 0;
int prevDir = 0, prevSteer = 0;
int mode=2;
bool xMode=false;
#ifdef testmode
  extern uint8_t cnt;
  uint8_t cnt1 =0;
  char commands[]="FBIJGH";
#endif
 
void setup()
{
  initDrive();
  #ifndef testmode
    Serial.begin(115200); //Set the baud rate to that of your Bluetooth module.
  #else
  Serial.begin(115200);
  #endif
  Serial.println("Run");
  hcInit();
  initHCSR04();
}

void loop()
{
#ifndef testmode
  if (Serial.available() > 0)
  {

    command = Serial.read();
#else
  if (true)
    {
      if(cnt==10){
        command=commands[cnt1];
        Serial.print("*************");Serial.println(command);
      }
      
#endif
    if (command != oldCommand)
    {
      //Change pin mode only if new command is different from previous.
      if (!xMode){
        if (command=='X'){
          xMode=true;
        }else{
          command='S';
        }
      }
      oldCommand = command;

      switch (command)
      {
      case 'F':
        dir = 1;
        steer = 0;
        state = FRW_HC;
        break;
      case 'B':
        dir = -1;
        steer = 0;
        state = REW_HC;
        break;
      case 'L':
        dir = 0;
        steer = -1;
        state = STOP_HC;
        break;
      case 'R':
        dir = 0;
        steer = 1;
        state = STOP_HC;
        break;
      case 'S':
      case 'M': //RING 0 fe:1e:46:65:92:3e 1 RFCOMM
        steer = 0;
        dir = 0;
        state = STOP_HC;
        break;
      case 'I': //FR
        dir = 1;
        steer = 1;
        state = FRW_HC;
        break;
      case 'J': //BR
        dir = -1;
        steer = 1;
        state = REW_HC;
        break;
      case 'G': //FL
        dir = 1;
        steer = -1;
        state = FRW_HC;
        break;
      case 'H': //BL
        dir = -1;
        steer = -1;
        state = REW_HC;
        break;
      case '0': //потер связи
        state = STOP_HC;
        steer = 0;
        break;
      case 'W': //Font ON
        frontlight = true;
        break;
      case 'w': //Font OFF
        frontlight = false;
        break;
      case 'U': //Back ON
        backlight = true;
        break;
      case 'u': //Back OFF
        backlight = false;
        break;
      case 'D': //Everything OFF /DNO CARRIER 0 ERROR 0 
      case 'x': // аварийный выключатель
        backlight = false;
        frontlight = false;
        state = STOP_HC;
        xMode=false;
        break;
      default: //Get velocity
        if (command == 'q')
        {
          mode=0;  //0 - отрабатывает два расстояния
          velocity = 255; //Full velocity
          //yellowCar.SetSpeed_4W(velocity);
        }
        else
        {
          //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
          if ((command >= 48) && (command <= 57))
          {
            //Subtracting 48 changes the range from 48-57 to 0-9.
            //Multiplying by 25 changes the range from 0-9 to 0-225.
            if(command-48>7){
              mode=0;
            }else if(command-48>=3){
              mode=1; //1 - только DISTANSE_STOP

            }else{
              mode=2; //2 - не работают датчики

            }
            //yellowCar.SetSpeed_4W(velocity);
            //0 - отрабатывает два расстояния
            //1 - только DISTANSE_STOP
            //>=2 - не работают датчики
          }
        }
        break;
      }
    //  Serial.print("state");Serial.println(state,BIN);
      state = setlight(state, backlight, frontlight);
      hcWrite(state);
    //  Serial.print("state-end");Serial.println(state,BIN);
    }
  }

  if (dir !=0)
  {
    //движение
    uint32_t dist = getDistance(dir);
    Serial.print(dist); Serial.print("-");Serial.print(dir); Serial.print("-");Serial.println(steer);
    if (dist < DISTANSE_1 && dist >= DISTANSE_STOP && mode==0)
    {
      Serial.println("DISTANSE_1");
      state &=~B00001000; //  включить стопы
      hcWrite(state);
      if (steer == 0){
        steer_ = 1;
      }else{
        steer_ = -steer;
      }
        
    }else if(dist < DISTANSE_STOP && mode<2){
      Serial.println("DISTANSE_STOP");
      if(dir==1){
        state = REW_HC;
      }else{
        state = FRW_HC;
      }
      state = setlight(state, backlight, frontlight);
      state &=~B00001000; //  включить стопы
      hcWrite(state);
      if(steer==0){
        move_back(dir,1);
      }else{
        move_back(dir,steer);
      }
      dist = getDistance(dir);
      if(dist < DISTANSE_STOP){
        dir=0;
        state &=~B00001000; //  включить стопы
        hcWrite(state);
      }
      steer_ = steer;
    }else{
      steer_ = steer;
    }
    //Serial.print("dist");
    
    
  }else{
    //только руль
      steer_ = steer;
  }
  if (prevDir!=dir || prevSteer!=steer_){
    prevDir=dir;
    prevSteer=steer_;
    Serial.print(dir); Serial.print("-");Serial.println(steer_);
    setMotors(dir, steer_);
  }
#ifdef testmode
  Serial.print(command); Serial.print("-");Serial.print(dir); Serial.print("-");Serial.println(steer_);
  cnt--;
  if (cnt==0){
    cnt=10;
    cnt1++;
    if (cnt1>5){
      while(1);
    }
  }
#endif
}
