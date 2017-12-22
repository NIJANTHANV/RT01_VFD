/*
 * File:   newmain_2431.c
 * Author: nijanthan.v
 *
 * Created on May 27, 2017, 2:27 PM
 */


#include <xc.h>
#pragma config OSC = IRCIO, WDTEN = OFF, MCLRE = ON, BOREN = OFF, PWRTEN = OFF, LVP = OFF
#include "ISR.h"
#include "UART.h"
#include "INITIATE.h"
#include "PWM_MODULE.h"
#include "ADC.h"
#include "ONE_SEC_FUNCTION.h"

#define LEM_KC_Constant (16256)  //=1.3115V(65535/5.03)
#define DC_BUS_KV_constant (0.02132) //700DC bus voltage 
#define _XTAL_FREQ 8000000

unsigned int R_Current_Data = 0,DC_Voltage_Data = 0,DC_Volt_Low  = 0,DC_Volt_High = 0;


void main(void) 
{
    OSCCON = 0b01110011;        /* Configure the internal oscillator. */
    TIMER0_INITIATE();
    IO_Initiation();
    usart_init();
    VFD_Current_INITIATE();
    
    TRISB0 = 0; TRISB1 = 0; TRISB2 = 0; TRISB3 = 0; TRISB4 = 0; TRISB5 = 0;
    RB0 = 0;    RB1 = 0;    RB2 = 0;    RB3 = 0;    RB4 = 0; RB5 = 0;
    TRISC4 = 0; 
    TRISC5 = 0;
    RC4 = 0;    
    RC5 = 0;
    TRISC2 = 0;
    RC2 = 0;
    A = 8000000 / 4;
    B_1 = 4 * 99;
    
    GIE = 1;
    PEIE =1;
    PTIF = 0;
    
    RC2 = 1;
    __delay_ms(90);
    RC2 = 0;    //Latch Release
            
    while(1)
    {
        if(Flag == 1)
        {
            Flag = 0;
            //UART_Data();
            
        }
        if(ADC_Flag == 1)
        {
            ADC_Flag = 0;
            
            R_V_Max = 0; 
            R_C_Max = 0;
            for(i=0; i<70; i++)  
            {
                R_V = DC_Bus_Volt_ADC();
                R_C = VFD_CURRENT_ADC();
                if(R_V_Max < R_V)
                {
                   R_V_Max = R_V;
                }
                

                if(R_C_Max < R_C)
                {
                   R_C_Max = R_C;
                }
            }
            R_V_Arr[5] = R_V_Arr[4]; 
            R_V_Arr[4] = R_V_Arr[3];
            R_V_Arr[3] = R_V_Arr[2]; 
            R_V_Arr[2] = R_V_Arr[1]; 
            R_V_Arr[1] = R_V_Arr[0];
            R_V_Arr[0] = R_V_Max;
            
          /*  R_C_Arr[5] = R_C_Arr[4]; 
            R_C_Arr[4] = R_C_Arr[3];
            R_C_Arr[3] = R_C_Arr[2]; */
            R_C_Arr[2] = R_C_Arr[1]; 
            R_C_Arr[1] = R_C_Arr[0];
            R_C_Arr[0] = R_C_Max;            
        }
        R_Voltage = ( ( R_V_Arr[0] + R_V_Arr[1] + R_V_Arr[2] + R_V_Arr[3] + R_V_Arr[4] + R_V_Arr[5]) / 6);
        R_Volt_1 = (R_Voltage * DC_BUS_KV_constant);// * 0.707106781;
        
        R_Current = ( ( R_C_Arr[0] + R_C_Arr[1] + R_C_Arr[2] ) / 3 );//+ R_C_Arr[3] + R_C_Arr[4] + R_C_Arr[5]) / 6);
        R_Current_1 = (R_Current - LEM_KC_Constant)* 0.004386;
        
        
        R_Current_Data = R_Current_1 * 10;
        DC_Voltage_Data = R_Volt_1;
        DC_Volt_Low  = DC_Voltage_Data & 0xff;
        DC_Volt_High = DC_Voltage_Data >> 8;
        
        if(Data_Send_Flag)
        {
            Data_Send_Flag = 0;
            if(Data[3] == 0x30)
            {
                RS485_Data();
            }
//            Temp_Counter++;
            RC4 = 1;
            __delay_ms(22);
            usart_str_1(0x20);              //0
            usart_str_1(Data[4]);      //1
            usart_str_1(Desired_Frequency); //2
            usart_str_1(DC_Volt_Low);       //3
            usart_str_1(DC_Volt_High);      //4
            usart_str_1(R_Current_Data);    //5
            usart_str_1(Error_no);          //6
            usart_str_1(Data[4]);      //7
            usart_str_1(0x40);              //8
            usart_str_1(Data[4]);           //9
            __delay_ms(22);
            RC4 = 0;
            counter = 0;
            
        }
    }    
    
}
