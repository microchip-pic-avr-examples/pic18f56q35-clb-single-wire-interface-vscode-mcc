 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
� [2026] Microchip Technology Inc. and its subsidiaries.

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
#include "mcc_generated_files/system/system.h"
#include "../SingleWire.h"

/*
    Main application
*/

int main(void)
{
    float temp;
    uint8_t dev_address = 0;
    static uint8_t dev_status = 0;

    uint8_t rd_data[8];
    
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    printf("\n\rSingle Wire interface using CLB");

    at21cs_interface_init();
    __delay_ms(10);
    at21cs_scan_address();
    __delay_ms(10);
   
    while(1)
    {
        
        at21cs_interface_init();
         __delay_ms(10);
        
        if (at21cs_scan_address() == true) 
        {
            
           dev_address = at21cs_get_addr();
           if (dev_address < 8) 
           {
               printf("\n\rAT21CS01 address: %x", dev_address);
                //read Dev ID
                if (at21cs_read_id(&rd_data[0])==true)
                {
                    printf(", ID: %02X-%02X-%02X", rd_data[0], rd_data[1], rd_data[2]);
                }

                if (at21cs_read_serial(&rd_data[0])==true)
                {
                    printf(", SN: %02X%02X%02X%02X%02X%02X", rd_data[0], rd_data[1], rd_data[2], rd_data[3], rd_data[4], rd_data[5] );
                } 
           }
        }   
        DBG_LED_Toggle();


        __delay_ms(1);
        
        ds18b20_interface_init();
        
       __delay_ms(1);
       switch (dev_status )
       {
           case 0x00:
                if (ds18b20_swi_detect())
                {
                    ds18b20_startTempMeas();
                    dev_status++;
                };
                break;
           case 0x01:
                    dev_status++;
               break;
           case 0x02:
                if (ds18b20_swi_detect())
                {

                    temp = ds18b20_readTempMeas();
                    printf("\n\rDS18B20 - Temp %0.2f C", temp);                       
                    dev_status ++;
                };
                break; 
           case 0x03:
                if (ds18b20_swi_detect())
                {
                    ds18b20_read_rom(&rd_data[0]);
                    printf("\n\rDS18B20 ROM: %02X%02X%02X%02X%02X%02X%02X%02X", rd_data[0], rd_data[1], rd_data[2], rd_data[3], rd_data[4], rd_data[5], rd_data[6], rd_data[7] );
                    dev_status = 0;
                }
               break;
                
           default:
               break;
               
       }
        CLBSWINHbits.CLBSWINH7 = 0;

        DBG_LED_Toggle();

        __delay_ms(400);
    }
   
}