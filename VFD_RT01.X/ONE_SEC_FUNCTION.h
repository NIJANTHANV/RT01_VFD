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
#ifndef ONE_SEC_FUNCTION_H
#define	ONE_SEC_FUNCTION_H

#include <xc.h> // include processor files - each processor file is guarded.

#define DC_BUS_LOW_LIMIT (400)
#define DC_BUS_HIGH_LIMIT (700)
#define DC_BUS_CURRENT_LIMIT (10)
#define DC_BUS_EXTREM_LOW_LIMIT (100)

char Dc_Bus_Low_Counter = 0,Dc_Bus_High_Counter  = 0,VFD_SHORT_CIRCUIT = 0,VFD_SHORT_CIRCUIT_ERROR_flag = 0,Dc_Bus_Extrem_Low_Counter = 0;
char Error_no = 0,DC_Bus_Voltage_Extrem_Low = 0, LOGIC_ERROR_FLAG = 0;

void VFD_SHORT_CIRCUIT_ERROR (void);
void Push_Button (void);
void Voltage_Error_Trigger(void);
void VFD_Current (void);
void Logic_Error_Io (void);
#endif	/* XC_HEADER_TEMPLATE_H */

