/**
 * CLB1 Generated Driver API Source File
 *
 * @file clb1.c
 *
 * @ingroup clb1
 *
 * @brief This file contains the implementation of the public and private functions for the CLB1 driver.
 *
 * @version CLB1 Driver Version 1.1.2
*/
/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../clb1.h"
#include <xc.h>
#include "../../system/system.h"

static void (*CLB1_CLB0I_InterruptHandler)(void);

extern uint32_t start_clb_config;
extern uint32_t end_clb_config;

void CLB1_Initialize(void)
{
    /* Disable CLB */
    CLBCONbits.CLBEN = 0U;

    /* Load the bitstream */
    CLB1_Configure((uint32_t) &start_clb_config);

    /* CLKSEL HFINTOSC; CLKPRE 4;  */
    CLBCLK = (uint8_t) 0x92;

    
    /* Clearing CLB0I IF flag before enabling the interrupt. */
    PIR1bits.CLB0IF = 0U;
    /* Enabled CLB0I CLB1 interrupt */
    PIE1bits.CLB0IE = 1U;
    /* Clearing CLB1I IF flag. */
    PIR1bits.CLB1IF = 0U;
    /* Disabled CLB1I CLB1 interrupt */
    PIE1bits.CLB1IE = 0U;

    /* Clearing CLB2I IF flag. */
    PIR1bits.CLB2IF = 0U;
    /* Disabled CLB2I CLB1 interrupt */
    PIE1bits.CLB2IE = 0U;

    /* Clearing CLB3I IF flag. */
    PIR1bits.CLB3IF = 0U;
    /* Disabled CLB3I CLB1 interrupt */
    PIE1bits.CLB3IE = 0U;

    /* EN enabled; */
    CLBCONbits.CLBEN = (uint8_t)0x1U;

}

void CLB1_TristatePPSInitialize(void)
{
    
	/* TRISC3 controlled by CLBOUTL0 */
	TRISC3PPS = (uint8_t)0x01U;
	/* TRISC4 controlled by CLBOUTL1 */
	TRISC4PPS = (uint8_t)0x02U;
    
	TRISC |= (uint8_t)0x18U;
}

void CLB1_Enable(void)
{
    CLBCONbits.CLBEN = 1U;
}

void CLB1_Disable(void)
{
    CLBCONbits.CLBEN = 0U;
}
void CLB1_Configure(uint32_t start_address)
{
    uint32_t end_address;
    // Bitstream length is given in words, multiply by 2 to get byte address
    // The end address is the last address to be written
    end_address = start_address + (BITSTREAM_SIZE - 1) * 2;
    
    /* Set the bitstream address */
    CRC_SetScannerAddressLimit(start_address, end_address);

    /* Start CLB bitstream load */
    CRC_StartNvmScanner();

    /* Wait to complete */
    while (!CRC_IsDone());

    /* Switch back to the CRC peripheral */
    CRC_StopNvmScanner();
}

void CLB1_SWIN_Write8(uint8_t data)
{
    CLBSWINL = data;
}

void CLB1_SWIN_Write16 (uint16_t data)
{
	CLBSWINH = (uint8_t)((data >> 8) & 0xFF);
	/* Write to the CLBSWINL register trigger load of CLBSWINM into CLB */
	CLBSWINL = (uint8_t)(data & 0xFF);

}
uint8_t CLB1_SWIN_Read8(void)
{
    uint8_t result = 0x00;

    result = (uint8_t)CLBSWINL;

	return result;
}

uint16_t CLB1_SWIN_Read16(void)
{
    uint16_t result = 0x00;

    result = (uint16_t)CLBSWINL;
    result = result | ((uint16_t)CLBSWINH << 8);
	return result;
}

void CLB1_CLB0I_SetInterruptHandler(void (* InterruptHandler)(void))
{
    CLB1_CLB0I_InterruptHandler = InterruptHandler;
}

void CLB1_CLB0I_Task(void)
{
    if (PIR1bits.CLB0IF == 1U)
    {
        PIR1bits.CLB0IF = 0U;
        if (CLB1_CLB0I_InterruptHandler != NULL)
        {
            CLB1_CLB0I_InterruptHandler();
        }
    }
}

