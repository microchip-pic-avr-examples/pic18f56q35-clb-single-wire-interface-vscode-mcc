/**
 * CLC1 Generated Driver File.
 * 
 * @file clc1.c
 * 
 * @ingroup  clc1
 * 
 * @brief This file contains the API implementations for the CLC1 driver.
 *
 * @version CLC1 Driver Version 1.2.1
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


#include <xc.h>
#include "../clc1.h"


static void (*CLC1_Callback)(void);
static void CLC1_DefaultCallback(void);

void CLC1_Initialize(void) 
{
    
    // SLCT 0x0; 
    CLCSELECT = (uint8_t)0x0;
    // LCG1POL not_inverted; LCG2POL not_inverted; LCG3POL not_inverted; LCG4POL not_inverted; LCPOL not_inverted; 
    CLCnPOL = (uint8_t)0x0;
    // LCD1S PWM1_OUT2; 
    CLCnSEL0 = (uint8_t)0x1B;
    // LCD2S CLCIN0PPS; 
    CLCnSEL1 = (uint8_t)0x0;
    // LCD3S CLCIN0PPS; 
    CLCnSEL2 = (uint8_t)0x0;
    // LCD4S CLCIN0PPS; 
    CLCnSEL3 = (uint8_t)0x0;
    // LCG1D1N disabled; LCG1D1T enabled; LCG1D2N disabled; LCG1D2T disabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLCnGLS0 = (uint8_t)0x2;
    // LCG2D1N disabled; LCG2D1T disabled; LCG2D2N disabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLCnGLS1 = (uint8_t)0x0;
    // LCG3D1N disabled; LCG3D1T disabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLCnGLS2 = (uint8_t)0x0;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLCnGLS3 = (uint8_t)0x0;
    // LCOUT 0x00; 
    CLCDATA = (uint8_t)0x0;
    // LCMODE OR-XOR; LCINTN disabled; LCINTP disabled; LCEN enabled; 
    CLCnCON = (uint8_t)0x81;

    //Set default callback for CLC1 interrupt Overflow.
    CLC1_CallbackRegister(CLC1_DefaultCallback);

    // Clear the CLC interrupt flag
    PIR2bits.CLC1IF = 0U;
}

void CLC1_Enable(void) 
{
    CLCSELECTbits.SLCT = (uint8_t)0U;
    CLCnCONbits.EN = (uint8_t)1U;
}

void CLC1_Disable(void) 
{
    CLCSELECTbits.SLCT = (uint8_t)0U;
    CLCnCONbits.EN = (uint8_t)0U;
}

void CLC1_RisingEdgeDetectionEnable(void) 
{
    CLCSELECTbits.SLCT = (uint8_t)0U;
    CLCnCONbits.INTP = (uint8_t)1U;
}

void CLC1_RisingEdgeDetectionDisable(void) 
{
    CLCSELECTbits.SLCT = (uint8_t)0U;
    CLCnCONbits.INTP = (uint8_t)0U;
}

void CLC1_FallingEdgeDetectionEnable(void) 
{
    CLCSELECTbits.SLCT = (uint8_t)0U;
    CLCnCONbits.INTN = (uint8_t)1U;
}

void CLC1_FallingEdgeDetectionDisable(void) 
{
    CLCSELECTbits.SLCT = (uint8_t)0U;
    CLCnCONbits.INTN = (uint8_t)0U;
}

/* cppcheck-suppress misra-c2012-8.7 */
void CLC1_CallbackRegister(void (* CallbackHandler)(void))
{
    CLC1_Callback = CallbackHandler;
}

static void CLC1_DefaultCallback(void)
{
    //Add your interrupt code here or
    //Use CLC1_CallbackRegister function to use Custom ISR
}

void CLC1_Tasks(void)
{
    if(PIR2bits.CLC1IF == 1U)
    {
        if(CLC1_Callback != NULL)
        {
            CLC1_Callback();
        }
        PIR2bits.CLC1IF = (uint8_t)0U;
    }
}


bool CLC1_OutputStatusGet(void) 
{
    return(CLCDATAbits.CLC1OUT);
}
/**
 End of File
*/
