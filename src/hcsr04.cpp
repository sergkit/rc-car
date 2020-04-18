#include <Arduino.h>
#include "hcsr04.h"

#include "testmode.h"

//#include <CyberLib.h>  куча примитивов для включения конкретных выводов

uint8_t c=0, last_dir=0;
uint16_t avg_dist=120;

#ifdef testmode
uint16_t dist[]={40,40,40,40,40,65,65,65,65,120,120};
extern uint8_t cnt;

uint16_t getDistance(int dir)
{
   return dist[cnt]; 
}

#else
uint16_t dist[]={0,0,0};
uint16_t getDistance(int dir)
{
    uint16_t d;
    if(last_dir!=dir){
        c=0;
        last_dir=dir;
        avg_dist=120;
        dist[0]=dist[1]=dist[2]=0;
    }

    if (dir == 1)
    {
        d= getFrw();
    }
    else if (dir == -1)
    {
        d= getRew();
    }
    else {
        d=avg_dist;
    }
    if(d>0){
        dist[c]=d;
        c++;
    }
    //Serial.print("-");Serial.println(d);
    if( c==3){
        c=0;
        d=(uint16_t)((dist[0]+dist[1]+dist[2])/3);
        return  d;
    }else{
        if (c>0){
            return d=(uint16_t)((dist[0]+dist[1]+dist[2])/c);;
        }else{
            return avg_dist;
        }
         
    }
}
#endif

void initHCSR04()
{

    TRIG_REW_Out;
    TRIG_FRW_Out;
    ECHO_REW_In;
    ECHO_FRW_In;
    TRIG_FRW_Low;
    TRIG_REW_Low;
}

uint16_t getFrw()
{
    uint16_t dist;
    TRIG_FRW_High;
    delay_us(10);
    TRIG_FRW_Low;
    dist = pulseIn(ECHO_FRW, HIGH, MAX_DELAY); //считываем длительность времени прохождения эха, ограничить время ожидания
    if (dist == 0)
        dist = MAX_DELAY;
    return dist / 58;
}

uint16_t getRew()
{
    uint16_t dist;
    TRIG_REW_High;
    delay_us(10);
    TRIG_REW_Low;
    dist = pulseIn(ECHO_REW, HIGH, MAX_DELAY); //считываем длительность времени прохождения эха, ограничить время ожидания
    if (dist == 0)
        dist = MAX_DELAY;
    return dist / 58;
}

void delay_us(uint16_t tic_us)
{
    tic_us *= 4; //1us = 4 öèêëà
    __asm__ volatile(
        "1: sbiw %0,1"
        "\n\t" //; âû÷åñòü èç ðåãèñòðà çíà÷åíèå N
        "brne 1b"
        : "=w"(tic_us)
        : "0"(tic_us));
}