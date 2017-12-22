/*
 * File:   ADC.c
 * Author: nijanthan.v
 *
 * Created on May 27, 2017, 2:35 PM
 */

#include "ISR.h"
#include "UART.h"
#include "INITIATE.h"
#include "PWM_MODULE.h"
#include "ADC.h"
#include "ONE_SEC_FUNCTION.h"
#include <xc.h>

void VFD_Current_INITIATE (void)
{    
    ADCON1 = 0;
    ADCON3 = 0;
    ADCON2 = 0b00111101;  //conversion time 12, TAD 2 minimum
    GASEL0 = 0;
    GASEL1 = 0;//GROUP A AN0
    GBSEL0 = 0;
    GBSEL1 = 0;//GROUP B AN1
    ANS0 = 1;
    ANS1 = 1;   
}
unsigned int DC_Bus_Volt_ADC (void)
{ //AN0    
    ACSCH = 0; // Single CHANNEL MODE
    ACMOD0 = 0;
    ACMOD1 = 0;  //Single CHANNEL GROUP SELECT MODE
    ACONV = 0; // CONVERSION SINGLE SHOT MODE
    ADON = 1; //ADC ON BIT
    GO_DONE = 1; // ADC CONVERSION START BIT
    while(GODONE); //wait for the conversion to finish
    ADON=0;  //switch off adc
    return ((ADRESH<<8)+ADRESL);//ADRES;
}
unsigned int VFD_CURRENT_ADC (void)
{ //AN1    
    ACSCH = 0; // Single CHANNEL MODE
    ACMOD0 = 1;
    ACMOD1 = 0;  //Single CHANNEL GROUP SELECT MODE
    ACONV = 0; // CONVERSION SINGLE SHOT MODE
    ADON = 1; //ADC ON BIT
    GO_DONE = 1; // ADC CONVERSION START BIT
    while(GODONE); //wait for the conversion to finish
    ADON=0;  //switch off adc
    return ((ADRESH<<8)+ADRESL);//ADRES;
}
