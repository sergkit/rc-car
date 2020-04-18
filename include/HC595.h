#include <Arduino.h>

#define HC_RS 8
#define HC_A 6 //data out
#define HC_OE 7 //output enable
#define HC_SC 9 //clock
#define HC_LC A4 //lanch
#define FRW_HC B00011100  //frw led + frw sen
#define REW_HC B00101010  //rew led + rew sen
#define BRK_HC B00110000  //brk led
#define STOP_HC B00111000 


/* 0 -nc
 * 1- задний датчик
  2 - передний датчик
  3- стопы
  4 - задний свет
  5 - передний свет
  
 */
void hcInit();

void hcWrite(byte b);

byte setlight(byte state, bool backlight, bool frontlight);