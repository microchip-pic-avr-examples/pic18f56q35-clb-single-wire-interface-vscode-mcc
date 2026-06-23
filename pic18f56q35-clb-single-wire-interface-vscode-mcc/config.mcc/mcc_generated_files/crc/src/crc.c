/**
 * CRC Generated Driver File.
 * 
 * @file crc.c
 * 
 * @ingroup  crc
 * 
 * @brief This file contains the API implementation for the CRC driver.
 *
 * @version CRC Driver Version 1.0.3
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../crc.h"

static uint32_t CRC_ReverseValue(uint32_t crc);

void CRC_Initialize(void)
{
    CRCCON0 = 0x00;
    //CRC Configurations
    //CRCPLEN 7; 
    CRCCON1 = 0x7;
    //CRCDLEN 7; 
    CRCCON2 = 0x7;

    // Read/Write access to CRCXOR
    CRCCON0bits.SETUP = 0b10;
    //CRCXORT 0; 
    CRCXORT = 0x0;
    //CRCXORU 0; 
    CRCXORU = 0x0;
    //CRCXORH 0; 
    CRCXORH = 0x0;
    //CRCXORL 213; 
    CRCXORL = 0xD5;

    // Read/Write access to CRCOUT
    CRCCON0bits.SETUP = 0b00;
    //CRCOUTT 0; 
    CRCOUTT = 0x0;
    //CRCOUTU 0; 
    CRCOUTU = 0x0;
    //CRCOUTH 0; 
    CRCOUTH = 0x0;
    //CRCOUTL 0; 
    CRCOUTL = 0x0;

    //CRCDATAT 0; 
    CRCDATAT = 0x0;
    //CRCDATAU 0; 
    CRCDATAU = 0x0;
    //CRCDATAH 0; 
    CRCDATAH = 0x0;
    //CRCDATAL 0; 
    CRCDATAL = 0x0;

    //Scanner Configurations
    //
    SCANHADRU = 0x0;
    //
    SCANHADRH = 0x0;
    //
    SCANHADRL = 0x0;
    //LADR undefined; 
    SCANLADRU = 0x0;
    //
    SCANLADRH = 0x0;
    //
    SCANLADRL = 0x0;
    //SCANTSEL LFINTOSC; 
    SCANTRIG = 0x0;

    // Clearing CRC IF flag
    PIR0bits.CRCIF = 0;
    // Disabled CRCI CRC interrupt
    PIE0bits.CRCIE = 0;

    // Clearing Scanner IF flag.
    PIR0bits.SCANIF = 0;
    // Disabled SCANI CRC interrupt
    PIE0bits.SCANIE = 0;

    //CRCEN enabled; CRCGO disabled; CRCACCM data augmented with 0s; CRCSETUP ; CRCLENDIAN shift left; 
    CRCCON0 = 0x90;
    //SCANEN disabled; TRIGEN disabled; SCANGO disabled; MREG Data EEPROM; BURSTMD CRC request and Trigger; DPS CRC module is selected; 
    SCANCON0 = 0x4;
}

void CRC_Start(void)
{
    CRCCON0bits.CRCGO = 1;
}

bool CRC_WriteData(uint32_t data)
{
    bool result = false;

    if(!CRCCON0bits.FULL)
    {
        CRCDATAT = (uint8_t)((data >> 24U) & (uint32_t)0xFFU);
        CRCDATAU = (uint8_t)((data >> 16U) & (uint32_t)0xFFU);
        CRCDATAH = (uint8_t)((data >> 8U) & (uint32_t)0xFFU);
        CRCDATAL = (uint8_t)(data & (uint32_t)0xFFU);
        result = true;
    } 
      
    return result;
}

static uint32_t CRC_ReverseValue(uint32_t crc)
{
    uint32_t mask;
    uint32_t reverse;
    uint32_t crc_bits = crc;

    mask = 1U;
    mask <<= CRCCON1bits.PLEN;
    reverse = 0U;

    while (crc_bits != 0U)
    {
        if ((crc_bits & 0x01U) != 0U)
        {
            reverse |= mask;
        }
        mask >>= 1U;
        crc_bits >>= 1U;
    }
    return reverse;
}

uint32_t CRC_GetCalculatedResult(bool reverse, uint32_t xorValue)
{
    uint32_t result = 0x00;
    // Read/Write access to CRCOUT
    CRCCON0bits.SETUP = 0b00;
    result = (uint32_t)CRCOUTL;
    result = result | ((uint32_t)CRCOUTH << 8U);
    result = result | ((uint32_t)CRCOUTU << 16U);
    result = result | ((uint32_t)CRCOUTT << 24U);
    if(reverse)
    {
        result = CRC_ReverseValue(result);
    }
    result ^= xorValue;
    return (result & (uint32_t)0xFF);
}

bool CRC_IsBusy(void)
{
    return(CRCCON0bits.CRCBUSY);
}

void CRC_StartScanner(void)
{
    uint8_t gIntFlagStatus = 0;
    gIntFlagStatus = INTCON0bits.GIE;

    // Disable global Interrupts;
    INTCON0bits.GIE = 0;
    // Grant memory access to CRC Scanner peripherals
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 1;
    INTCON0bits.GIE = gIntFlagStatus;

    // Start the serial shifter
    CRCCON0bits.CRCGO = 1;
    // Start the scanner
    SCANCON0bits.SGO = 1;
}

void CRC_StopScanner(void)
{
    uint8_t gIntFlagStatus = 0;
    gIntFlagStatus = INTCON0bits.GIE;

    // Disable global Interrupts;
    INTCON0bits.GIE = 0;
    // Forbid memory access to CRC Scanner peripherals
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 0;
    INTCON0bits.GIE = gIntFlagStatus;

    // Stop the serial shifter
    CRCCON0bits.CRCGO = 0;
    // Stop the scanner
    SCANCON0bits.SGO = 0;
}

void CRC_StartNvmScanner(void)
{
    uint8_t gIntFlagStatus = 0;
    gIntFlagStatus = INTCON0bits.GIE;

    // Disable global Interrupts;
    INTCON0bits.GIE = 0;
    // Grant memory access to CRC Scanner peripherals
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 1;
    INTCON0bits.GIE = gIntFlagStatus;

    // Start the serial shifter
    CRCCON0bits.CRCGO = 1;
    //Enable the scanner
    SCANCON0bits.SCANEN = 1; 
    // Select CLB-peripheral for load
    SCANCON0bits.DPS = 1;
    // Start the scanner
    SCANCON0bits.SGO = 1;
}

void CRC_StopNvmScanner(void)
{
    uint8_t gIntFlagStatus = 0;
    gIntFlagStatus = INTCON0bits.GIE;

    // Disable global Interrupts;
    INTCON0bits.GIE = 0;
    // Forbid memory access to CRC Scanner peripherals
    PRLOCK = 0x55;
    PRLOCK = 0xAA;
    PRLOCKbits.PRLOCKED = 0;
    INTCON0bits.GIE = gIntFlagStatus;

    // Stop the serial shifter
    CRCCON0bits.CRCGO = 0;
    // De-select CLB-peripheral for load
    SCANCON0bits.DPS = 0;
    // Stop the scanner
    SCANCON0bits.SGO = 0;
    // Disable the scanner
    SCANCON0bits.SCANEN = 0;
}

void CRC_SetScannerAddressLimit(uint32_t startAddr, uint32_t endAddr)
{
    SCANHADRU = (uint8_t)((endAddr >> 16U) & (uint32_t)0xFFU);
    SCANHADRH = (uint8_t)((endAddr >> 8U) & (uint32_t)0xFFU);
    SCANHADRL = (uint8_t)(endAddr & (uint32_t)0xFFU);
    SCANLADRU = (uint8_t)((startAddr >> 16U) & (uint32_t)0xFFU);
    SCANLADRH = (uint8_t)((startAddr >> 8U) & (uint32_t)0xFFU);
    SCANLADRL = (uint8_t)(startAddr & (uint32_t)0xFFU);
}

bool CRC_IsScannerBusy(void)
{
    return (SCANCON0bits.BUSY);
}

bool CRC_IsDone(void)
{
    return (SCANCON0bits.SGO == 0);
}


