/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PWM_MODULE_H
#define	PWM_MODULE_H

#include <xc.h> // include processor files - each processor file is guarded.  
float Frequency = 5;
const unsigned int SINE_TABLE[100] = 
{
    160,170,180,190,200,209,219,228,237,246,
    254,262,270,277,283,289,295,300,305,308,
    312,315,317,318,319,319,318,317,316,313,
    310,307,302,298,292,286,280,273,266,258,
    250,241,233,223,214,204,195,185,175,165,
    154,144,134,124,115,105,96,86,78,69,
    61,53,46,39,33,27,21,17,12,9,
    6,3,2,1,0,0,1,2,4,7,
    11,14,19,24,30,36,42,49,57,65,
    73,82,91,100,110,119,129,139,149,160
};
unsigned int PDC0_1 = 0,PDC1_1 = 0,PDC2_1 = 0;
float  A,B,B_1;
unsigned long int Vab_1 = 0,Vab = 0;
unsigned char gDutycount = 0,gDutycount1 = 0,gDutycount2 = 0;
char Auto_VFD_ON = 0,Desired_Frequency = 0,PWM_Init = 0;

void RS485_Data (void);
void Cal (void);
void POWER_PWM (void);
void Auto_PWM_Cal (void);
#endif	/* XC_HEADER_TEMPLATE_H */

