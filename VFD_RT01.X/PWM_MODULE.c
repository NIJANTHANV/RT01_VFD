/*
 * File:   PWM_MODULE.c
 * Author: nijanthan.v
 *
 * Created on May 27, 2017, 2:28 PM
 */

#include "ISR.h"
#include "UART.h"
#include "INITIATE.h"
#include "PWM_MODULE.h"
#include "ADC.h"
#include "ONE_SEC_FUNCTION.h"
#include <xc.h>

void POWER_PWM (void)
{
    TRISB = 0;                 /* All PORTB bits are unconnected outputs. */
    
    PTCON0 = 0b000000100;         /* 1:1 postscale, 1:1 prescale, continuous up/down count mode enabled. */
    PTEN = 0;           /* PWM is turned off. */
    PWMCON0 = 0b01000000;  /* PWM1 pin is enabled for PWM output, PWM outputs are in complementary mode. */
    PWMCON1 = 0b00000001;  /* 1:1 postscale for PWM special event trigger, duty cycle and period update enabled. */
    OVDCOND = 0xFF;
    OVDCONS = 0x00;
    SEVTCMPH:SEVTCMPL = 0x00;
    DTCON = 10;
    PTEN=1;           /* Turn on the PWM module. */
}

void Cal (void)
{        
    B= B_1 * Frequency;
    Vab = (A / B) - 1;
    PTPERL = Vab & 0xFF;
    PTPERH = Vab >> 8;
} 

void RS485_Data (void)
{
        Auto_VFD_ON = Data[1];
        if( Data[2] >=5 && Data[2] <61)
        {
            Desired_Frequency = Data[2];
        }
     
}
void Auto_PWM_Cal (void)
{        
    B= B_1 * Desired_Frequency;
    Vab = (A / B) - 1;
    PTPERL = Vab & 0xFF;
    PTPERH = Vab >> 8;
}