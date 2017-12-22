/*
 * File:   ISR.c
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
#define _XTAL_FREQ 8000000

void interrupt ISR(void)
{
    if(PIR1bits.RC1IF)
    {
        if(RCSTA1bits.OERR==1)
        {
            RCSTA1bits.CREN=0;
            RCSTA1bits.CREN=1;
        }
        Data[counter] = RCREG1;
        if(Data[0] == 0x07)
        {
            if(counter < 5)
            {
                counter++;
            }
        }
        if(counter == 5)
        {
            Data_Send_Flag = 1;
            counter = 0;
        }
        PIR1bits.RC1IF = 0;
    }
    if(PTIF)
    {
        PTIF = 0;
        ++gDutycount; // Increment the counter variable by 1

        if(gDutycount == 99)
        {
            gDutycount = 0;
        }
        gDutycount1 = gDutycount+66;
        if(gDutycount1 >= 99)
        {
            gDutycount1=gDutycount1 - 99;
        }
        gDutycount2 = gDutycount+33;
        if(gDutycount2 >= 99)
        {
            gDutycount2=gDutycount2 - 99;
        }    
        PDC0_1 = SINE_TABLE[gDutycount] ;
        PDC1_1 = SINE_TABLE[gDutycount1] ;
        PDC2_1 = SINE_TABLE[gDutycount2] ; 
        
        PDC0L = PDC0_1 & 0xFF ;
        PDC0H = PDC0_1 >> 8 ;
        
        PDC1L = PDC1_1 & 0xFF ;
        PDC1H = PDC1_1 >> 8 ;
        
        PDC2L = PDC2_1 & 0xFF ;
        PDC2H = PDC2_1 >> 8 ;
        
        
    }
    if (TMR0IF)
    {
       TMR0IF = 0;    
       if(ADC_Flag == 0)
       {
           ADC_Flag = 1;    
       }
       VFD_Current();
       VFD_SHORT_CIRCUIT_ERROR();
       Logic_Error_Io();
       
       if(Auto_Manual == 1 && Auto_VFD_ON == 1 && Error_no != 0)
        {
             PWMEN2 = 0;
             PWMEN1 = 0;
             PWMEN0 = 0;
             RA6 = 1;   //VFD Error IO to Logic
             Desired_Frequency = DEFULAT_FREQUENCY;  PWM_Init = 0;  
             TRISB0 = 0; TRISB1 = 0; TRISB2 = 0; TRISB3 = 0; TRISB4 = 0; TRISB5 = 0;
             RB0 = 0;    RB1 = 0;    RB2 = 0;    RB3 = 0;    RB4 = 0; RB5 = 0;
        }
        ///To Trigger Error///
        if(LOGIC_ERROR_FLAG == 1 || RC1 == 1 || DC_Bus_Voltage_Low == 1 || DC_Bus_Voltage_High == 1 || Dc_Bus_Current == 1 || VFD_SHORT_CIRCUIT_ERROR_flag == 1 || DC_Bus_Voltage_Extrem_Low == 1)  //Fault Stop Auto & Manual
        {
            PWMEN2 = 0;
            PWMEN1 = 0;
            PWMEN0 = 0;

           TRISB0 = 0; TRISB1 = 0; TRISB2 = 0; TRISB3 = 0; TRISB4 = 0; TRISB5 = 0;
           RB0 = 0;    RB1 = 0;    RB2 = 0;    RB3 = 0;    RB4 = 0;     RB5 = 0;
           ON_OFF = 0;
           Frequency = 5; 
           DC_Bus_Voltage_Low = 0,DC_Bus_Voltage_High = 0,Dc_Bus_Current = 0; 
           DC_Bus_Voltage_Extrem_Low = 0; VFD_SHORT_CIRCUIT_ERROR_flag = 0;
           LOGIC_ERROR_FLAG = 0; 
        }
       
       Timer0_Overflow_counter++;
       if(Timer0_Overflow_counter >= 30)
       { 
           RC5 = ~RC5;
           
           Temp_Counter++;
           Push_Button();
           Voltage_Error_Trigger();
           if(Flag == 0)
           {
               Flag = 1;
           }        
           
        
           if(ON_OFF == 0)
           {
               //RC3 = 1;
           }
           Timer0_Overflow_counter = 0;
           
           //********** PWM ***********/
           if( Auto_Manual == 1 && Auto_VFD_ON == 1 && PWM_Init == 0 && Error_no == 0)
           {
               PWM_Init = 1;    
               POWER_PWM();
               PTIE = 1;
               RA6 = 0; //VFD Error IO to Logic
               Dc_Bus_Current = 0;  DC_Bus_Voltage_Low = 0; DC_Bus_Voltage_High = 0; 
               VFD_SHORT_CIRCUIT_ERROR_flag = 0; DC_Bus_Voltage_Extrem_Low = 0;
               LOGIC_ERROR_FLAG = 0; 
           } 
           if(PWM_Init == 1 && Auto_VFD_ON == 1 && Error_no == 0)
           {
               Auto_PWM_Cal();
           }
           if(Auto_Manual == 1 && Auto_VFD_ON == 0)
           {
                RC2 = 1;     //Latch release at Initial Ramp-up
                PWMEN2 = 0;
                PWMEN1 = 0;
                PWMEN0 = 0;
                Desired_Frequency = DEFULAT_FREQUENCY;  PWM_Init = 0;
                TRISB0 = 0; TRISB1 = 0; TRISB2 = 0; TRISB3 = 0; TRISB4 = 0; TRISB5 = 0;
                RB0 = 0;    RB1 = 0;    RB2 = 0;    RB3 = 0;    RB4 = 0; RB5 = 0;
                DC_Bus_Voltage_Low = 0; Error_no = 0; Dc_Bus_Low_Counter = 0;
                Dc_Bus_High_Counter = 0; DC_Bus_Voltage_High = 0; DC_Bus_Voltage_Extrem_Low = 0;
                RC2 = 0; LOGIC_ERROR_FLAG = 0;
           }
       }
       /*************To Reset********************/
       Five_Second_counter++;
       if(Five_Second_counter == 150)
       {
           if(LOGIC_ERROR_FLAG == 0 && DC_Bus_Voltage_Low == 0 && DC_Bus_Voltage_High == 0 && Dc_Bus_Current == 0 && VFD_SHORT_CIRCUIT_ERROR_flag == 0 && DC_Bus_Voltage_Extrem_Low == 0)
            {
                Error_no = 0;
                RA6 = 0;
                RC3 = 0;
            }
           Five_Second_counter = 0;
       }
       if(RA4 == 0 && RA2 != 0 && Auto_Manual == 0)  //Stop button manual
        {
             if(ON_OFF == 1)
             {
                  PWMEN2 = 0;
                  PWMEN1 = 0;
                  PWMEN0 = 0;

                 TRISB0 = 0; TRISB1 = 0; TRISB2 = 0; TRISB3 = 0; TRISB4 = 0; TRISB5 = 0;
                 RB0 = 0;    RB1 = 0;    RB2 = 0;    RB3 = 0;    RB4 = 0; RB5 = 0;
                 ON_OFF = 0;
                 Frequency = 5; 
             }   
        }  
    }
}
