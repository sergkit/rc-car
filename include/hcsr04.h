#include <Arduino.h>

#define ECHO_REW 3
#define ECHO_FRW 4
#define TRIG_REW 2
#define TRIG_FRW 5
#define MAX_DELAY  7000 //120 sm
#define DISTANSE_STOP 50
#define DISTANSE_1 70

#define TRIG_REW_Low PORTD &= B11111011
#define TRIG_FRW_Low PORTD &= B11011111
#define TRIG_REW_High PORTD |=B00000100
#define TRIG_FRW_High PORTD |=B00100000 
#define TRIG_REW_Out DDRD |=B00000100
#define TRIG_FRW_Out DDRD |=B00100000
#define ECHO_REW_In DDRD &=B11110111
#define ECHO_FRW_In DDRD &=B11101111

uint16_t getDistance (int dir);

void  initHCSR04();

void delay_us(uint16_t tic_us);

uint16_t getFrw();
uint16_t getRew();
