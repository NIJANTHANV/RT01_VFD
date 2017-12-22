/*
 * File:   UART.c
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


void UART_Data (void)
{
    
    temp = b++;
    vDisplayAscii(temp,INT_DATA_TYPE);
    usart_str_1(',');
    
    vDisplayAscii(Frequency,FLOAT_DATA_TYPE);
    usart_str_1(',');
    
    vDisplayAscii(R_Volt_1,INT_DATA_TYPE);
    usart_str_1(',');     
    
    vDisplayAscii(R_Current_1,FLOAT_DATA_TYPE);
    usart_str_1(','); 
    
    vDisplayAscii(DC_Bus_Voltage_Low,INT_DATA_TYPE);
    usart_str_1(',');
    
    vDisplayAscii(DC_Bus_Voltage_High,INT_DATA_TYPE);
    usart_str_1(',');
    
    vDisplayAscii(Dc_Bus_Current,INT_DATA_TYPE);
    usart_str_1(',');
            
    usart_str("\r");
    usart_str("\n");
}
void vDisplayAscii (float Data, int Storage_Type)
{
    int DivIndex = 3,Byte;
    float f32Temp,Data_1;
     int Check_1;
	unsigned int DivRatio[4] = {10,100,1000,10000},Data_Value;
    
    Data_Value = (int) Data;
    if(Data < 0)
	{
		usart_str_1('-');
		Data_Value  = Data_Value * -1;
	}
    while (DivIndex >= 0)
    {
        Byte = Data_Value/DivRatio[DivIndex];
       // if(Byte != 0)
        {
            usart_str_1(Byte + 0x30);
        }        
        Data_Value = Data_Value % DivRatio[DivIndex];
        --DivIndex;
    }
    usart_str_1(Data_Value + 0x30);
    
    if(Storage_Type == FLOAT_DATA_TYPE)    
    {
        usart_str_1('.');
        if(Data < 0)
        {
            Data = Data * -1;
        }
        else if(Data >= 0)
        {
            Data = Data * 1;
        }        
        Check_1 = Data;
        Data_1 = Data - Check_1;// -  Check_1;
        Data_1 *=100;
        digit1 = (unsigned int)(Data_1/10);
        digit2 = (unsigned int)(Data_1 - digit1*10);
        usart_str_1(digit1+0x30);
        usart_str_1(digit2+0x30);
    }
    
}
void usart_init()
{
    TXSTAbits.SYNC = 0;
	TXSTAbits.BRGH = 1;
	BAUDCONbits.BRG16 = 0;
	TRISCbits.TRISC6 = 1;
	TRISCbits.TRISC7 = 1;
	TXSTAbits.TXEN = 1;
	RCSTAbits.CREN = 1;
	RCSTAbits.SPEN = 1;
    SPBRG1=51;
   
    PIR1bits.RC1IF = 0; 
    PIE1bits.RC1IE = 1;
    
}
void usart_str(const char*str)
{
    while((*str)!='\0')
    {
        while(!TXIF);
        TXREG=(*str);
        str++;
    }
}
void usart_str_1(const char str)
{
        while(!TXIF);
        TXREG=(str);
}
