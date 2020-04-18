#include <Arduino.h>
#include "HC595.h"

void hcInit()
{
  pinMode(HC_OE, OUTPUT);
  digitalWrite(HC_OE, LOW);
  //сброс
  pinMode(HC_RS, OUTPUT);
  digitalWrite(HC_RS, LOW);
  delay(1);
  digitalWrite(HC_RS, HIGH);

  pinMode(HC_SC, OUTPUT);
  digitalWrite(HC_SC, LOW);
  pinMode(HC_LC, OUTPUT);
  digitalWrite(HC_LC, LOW);

  pinMode(HC_A, OUTPUT);
  digitalWrite(HC_A, LOW);
  hcWrite(STOP_HC);
}

void hcWrite(byte b)
{
  //устанавливаем LOW на latchPin пока не окончена передача байта
  digitalWrite(HC_LC, LOW);
  shiftOut(HC_A, HC_SC, MSBFIRST, b);
  //устанавливаем HIGH на latchPin, чтобы проинформировать регистр, что передача окончена.
  digitalWrite(HC_LC, HIGH);
  //digitalWrite(HC_OE, LOW);
  //Serial.println(b,BIN);

}

byte setlight(byte state, bool backlight, bool frontlight)
{
 // byte b;
  if(!backlight){
    state=state | B00010000;
    //Serial.print("-"); Serial.println(state,BIN);
  }
  if (!frontlight){
    state=state | B00100000;
    //Serial.print("--");Serial.println(state,BIN);
  }
  return state;
}