/**
 * \file io_operator.c
 * \version 0.1
 * \date 2020-4-21
 * 
 * \brief io操作接口实现
 */

#include <wiringPi.h>

void digital_set(int number, int value)
{
    wiringPiSetup() ;
	pinMode(number, OUTPUT) ;
    if (1 == value)
    {
        digitalWrite(number, HIGH);
    }
    else 
    {
        digitalWrite(number, LOW);
    }
}
