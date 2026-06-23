/***************************************************************************************************************************************************************************
 * 
 * FileName:			swi_phy.c
 * 
 * Company:			Microchip Technology, Inc.
 * Summary:			C file for the Single-Wire protocol physical level  
 * 
 * Description:		C file for the Single-Wire protocol physical level  
***************************************************************************************************************************************************************************/

/****************************************************
 *  SWI interface 
 * 
 * Resources used:
 *   - CLB
 *   - PWM1 + CLC1 (or PWM1 + PWM2)
 *   - TMR2
 * 
 * Control/data interface
 *   - CLBSWINL[7:0] - input data
 *   - CLBSWINH0 - enable Tx/Rx 
 *   - CLBSWINH1 - 
 *   - CLBSWINH2 - ACK/NACK (read op)
 *   - CLBSWINH4 - enable bit-bang control on SWI pin 
 *
 *   - CLB_IRQ0     - Tx/Rx complete flag
 *   - CLBSWOUTH[0] - ACK/NACK 
 *   - CLBSWOUTH[4] - Tx/Rx in progress
 *   -  
 *   - CLBSWOUTL[7:0] - Received data * 
 * **************************************************/


#include "config.mcc/mcc_generated_files/system/system.h"
#include "SingleWire.h"
#include <stdbool.h>


bool OneWire_SwReset(void)
{
    PWM1_16BIT_Disable();
    CLBSWINHbits.CLBSWINH0 = 0;    
    __delay_us(SWI_INTERCMD);
    
    CLBSWINHbits.CLBSWINH4 = 1;    
    CLBSWINHbits.CLBSWINH1 = 1;
    __delay_us(SWI_RST);
    CLBSWINHbits.CLBSWINH1 = 0;
    __delay_us(SWI_RST_RECOVERY);
    
    //short low-pulse to initiate the ACK response
    CLBSWINHbits.CLBSWINH1 = 1;
    __delay_us(SWI_RD_START);
    CLBSWINHbits.CLBSWINH1 = 0;
    __delay_us(SWI_DACK);
   
    uint8_t read = (CLBSWOUTH & 0x01);
   
    CLBSWINHbits.CLBSWINH4 = 0;    
    
    __delay_us(SWI_INTERCMD);
    return (read == 0x01);
}

bool OneWire_WriteByte(uint8_t data)
{

    CLBSWINL = data;     
    
    CLBSWINHbits.CLBSWINH0 = 1;   
 
    PIR1bits.CLB0IF = 0;
    
    PWM1_16BIT_Enable();
    
     /* Wait for transmit data */
    while (PIR1bits.CLB0IF == 0);
    CLBSWINHbits.CLBSWINH0 = 0;    
    PWM1_16BIT_Disable();

    //read the ACK bit
    if ((CLBSWOUTH & 0x01) == 0) return NACK;    
    return ACK;
}

uint8_t OneWire_ReadByte(bool ack)
{
    uint8_t data;
    
    if (ack == ACK) CLBSWINHbits.CLBSWINH2 = 1;  
    else CLBSWINHbits.CLBSWINH2 = 0; 
    
    OneWire_WriteByte(0xFF);
    data = CLBSWOUTL;

    CLBSWINHbits.CLBSWINH2 = 0;      
    
    return data;
}
