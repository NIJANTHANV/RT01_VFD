/*
 * File:   INITIATE.c
 * Author: nijanthan.v
 *
 * Created on May 27, 2017, 2:27 PM
 */

#include "ISR.h"
#include "UART.h"
#include "INITIATE.h"
#include "PWM_MODULE.h"
#include "ADC.h"
#include "ONE_SEC_FUNCTION.h"
#include <xc.h>

void TIMER0_INITIATE(void)
{
    TMR0ON=0;
    T016BIT=1;
    T0CS=0;
    T0SE=0;
    PSA=0;
    T0PS0=1;
    T0PS1=1;
    T0PS2=1;    //256 Pre-Scale 
    TMR0IF = 0;
    TMR0IE=1;
    TMR0ON=1;      //Now start the timer!
}

void IO_Initiation (void)
{
    TRISC3 = 0;
    TRISA2 = 1;
    ANS2 = 0;
    TRISA3 = 1;
    ANS3 = 0;
    TRISA4 = 1;
    ANS4 = 0;
    TRISA7 = 1;
    TRISC1 = 1;
    
    TRISA6 = 0; //VFD O/p Error IO
    RA6 = 0;
    
    TRISC0 = 1; //Logic I/p Error Io
}
