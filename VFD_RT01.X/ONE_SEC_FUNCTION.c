/*
 * File:   ONE_SEC_FUNCTION.c
 * Author: nijanthan.v
 *
 * Created on May 27, 2017, 2:37 PM
 */

#include "ISR.h"
#include "UART.h"
#include "INITIATE.h"
#include "PWM_MODULE.h"
#include "ADC.h"
#include "ONE_SEC_FUNCTION.h"
#include <xc.h>


void Voltage_Error_Trigger (void)
{
    if(R_Volt_1 <= DC_BUS_LOW_LIMIT)
    {
        Dc_Bus_Low_Counter++;
        if(Dc_Bus_Low_Counter >= 10)
        {
            Dc_Bus_Low_Counter  =0;
            DC_Bus_Voltage_Low = 1;
            Error_no = 3;
            RC3 = ~RC3;
        }
    }
    else
    {
        DC_Bus_Voltage_Low  = 0;
        Dc_Bus_Low_Counter = 0;
        RC3 = 0;
    }
    if(R_Volt_1 <= DC_BUS_EXTREM_LOW_LIMIT)
    {
        Dc_Bus_Extrem_Low_Counter++;
        if(Dc_Bus_Extrem_Low_Counter >= 1)
        {
            Dc_Bus_Extrem_Low_Counter  =0;
            DC_Bus_Voltage_Extrem_Low = 1;
            Error_no = 7;
            RC3 = ~RC3;
        }
    }
    else
    {
        DC_Bus_Voltage_Extrem_Low  = 0;
        Dc_Bus_Extrem_Low_Counter = 0;
        RC3 = 0;
    }
    if(R_Volt_1 >= DC_BUS_HIGH_LIMIT)
    {
        Dc_Bus_High_Counter++;
        if(Dc_Bus_High_Counter >= 4)
        {
            Dc_Bus_High_Counter  =0;
            DC_Bus_Voltage_High = 1;
            Error_no = 3;
            RC3 = ~RC3;
        }
    }
    else
    {
        DC_Bus_Voltage_High  = 0;
        Dc_Bus_High_Counter = 0;
        RC3 = 0;
    }
    if(RC1 == 1)
    {
        Error_no = 6;
        VFD_SHORT_CIRCUIT = 1;
        RC3 = ~RC3;
    }
    
}
void VFD_Current (void)
{
    if(R_Current_1 >= DC_BUS_CURRENT_LIMIT)
    {
        Dc_Bus_Current = 1;
        Error_no = 8;
        RC3 = ~RC3;
    }
    else
    {
        Dc_Bus_Current  = 0;
        RC3 = 0;;
    }
}
void VFD_SHORT_CIRCUIT_ERROR (void)
{
    if(RC1 == 1)
    {
        Error_no = 6;
        VFD_SHORT_CIRCUIT_ERROR_flag = 1;
        RC3 = ~RC3;
    }
    else
    {
        VFD_SHORT_CIRCUIT_ERROR_flag = 0;
        RC3 = 0;
    }
}
void Logic_Error_Io (void)
{
    if(RC0 == 1)
    {
        LOGIC_ERROR_FLAG = 1;
        RC3 = ~RC3;
    }
    else
    {
        LOGIC_ERROR_FLAG = 0;
        RC3 = 0;
    }
}
void Push_Button (void)
{
    if(RA2 == 0 && RA4 != 0 && Auto_Manual == 0)
    {
       Frequency = Frequency + 1;
       if(Frequency >= 55)
       {
           Frequency = 55;
       }
       Cal();
//       RC3 = ~RC3;
    }
    if(RA3 == 0 && Auto_Manual == 0)
    {
        Frequency = Frequency - 1;
       if(Frequency <= 5)
       {
           Frequency = 5;
       }
        Cal();
//        RC3 = ~RC3;
    }
    if(Auto_Manual == 0 && RA4 == 0 && RA2 == 0 && DC_Bus_Voltage_Low == 0 && DC_Bus_Voltage_High == 0 && Dc_Bus_Current == 0)    //ON  -- OFF
    {   //Manual Start
       if(ON_OFF == 0)
       {
           POWER_PWM();
           PTIE = 1;
           Cal();
           ON_OFF = 1;
           Dc_Bus_Current = 0;  DC_Bus_Voltage_Low = 0; DC_Bus_Voltage_High = 0;
       }           
    }
    
    if(RA7 == 0)    //Manual
    {
        Auto_Manual = 0;
    }
    else            //Auto
    {
        Auto_Manual = 1;    //Auto
    }
    
}