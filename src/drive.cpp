#include <Arduino.h>
#include "drive.h"

void driveOff() {
  DRU_Low;
  DRD_High;
  DLU_Low;
  DLD_High;
}
void driveStop() {
  driveOff();
  DRU_Low;
  DRD_Low;
  DLU_Low;
  DLD_Low;
}
void driveFrw() {
  driveOff();
  DRU_High;
  DRD_High;
  DLU_Low;
  DLD_Low;
}
void driveRew() {
  driveOff();
  DLU_High;
  DLD_High;
  DRU_Low;
  DRD_Low;
}
void initDrive() {
  DRU_Out;
  DRD_Out;
  DLU_Out;
  DLD_Out;
  driveOff();
  
  RRU_Out;
  RRD_Out;
  RLU_Out;
  RLD_Out;
  steerOff();
}
void steerOff(){
  RRU_Low;
  RRD_Low;
  RLU_Low;
  RLD_Low;  
}

void steerLeft() {
  Serial.println("steerLeft");
  steerOff();
  RRU_High;
  RRD_Low;
  RLU_Low;
  RLD_High;
}
void steerRight() {
  Serial.println("steerRight");
  steerOff();
  RRU_Low;
  RRD_High;
  RLU_High;
  RLD_Low;

}
void steerFrw() {
  Serial.println("steerFrw");
  steerOff();
}
void setMotors(int dir, int steer){
  switch (dir)
  {
  case 1:
    driveFrw();
    break;
  case -1:
    driveRew();
    break;
  case 0:
    driveOff();
    break;
  }
  switch (steer)
  {
  case 1:
    steerRight();
    break;
  case -1:
    steerLeft();
    break;
  case 0:
    steerFrw();
    break;
  }

}

void move_back(int dir, int steer){
  Serial.println("move_back");
  setMotors(-dir, -steer);
  delay(500);
  Serial.println("move_frw");
}