

#include "config.mcc/mcc_generated_files/system/system.h"
#include "SingleWire.h"
#include <stdbool.h>

// OneWire commands
#define GETTEMP                 0x44  // Tells device to take a temperature reading and put it on the scratchpad
#define READROM                 0x33  // Command to address the device on the bus - can be used only when a single client is present 
#define SKIPROM                 0xCC  // Command to address all devices on the bus
#define SELECTDEVICE            0x55  // Command to address all devices on the bus
#define COPYSCRATCH             0x48  // Copy scratchpad to EEPROM
#define READSCRATCH             0xBE  // Read from scratchpad
#define WRITESCRATCH            0x4E  // Write to scratchpad
#define RECALLSCRATCH           0xB8  // Recall from EEPROM to scratchpad
#define READPOWERSUPPLY         0xB4  // Determine if device needs parasite power
#define ALARMSEARCH             0xEC  // Query bus for devices with an alarm condition

#define PERIOD_DIV(delay_us)    (uint16_t)(((64000000UL * delay_us) / (4 *1000000)) - 1)

#define SWI_BIT_TIME            125.0f
#define SWI_WR_LOW0             5 
#define SWI_WR_LOW1             1




uint8_t byte_reverse(uint8_t input_byte)
{
    uint8_t reversed_byte;
    reversed_byte = input_byte;
    reversed_byte = (uint8_t)((reversed_byte & 0xF0) >> 4 | (reversed_byte & 0x0F) << 4);
    reversed_byte = (uint8_t)((reversed_byte & 0xCC) >> 2 | (reversed_byte & 0x33) << 2);
    reversed_byte = (uint8_t)((reversed_byte & 0xAA) >> 1 | (reversed_byte & 0x55) << 1);
    return reversed_byte;
}


bool ds18b20_swi_detect(void)
{
    PWM1_16BIT_Disable();
    
    CLBSWINHbits.CLBSWINH0 = 1;
    
   
    CLBSWINHbits.CLBSWINH4 = 1;    
    CLBSWINHbits.CLBSWINH1 = 1;
    __delay_us(500);
    CLBSWINHbits.CLBSWINH1 = 0;
    __delay_us(80);
  
    uint8_t read = (CLBSWOUTH & 0x01);
   
    CLBSWINHbits.CLBSWINH4 = 0;    
    
    __delay_us(400);
    return (read == 0x01);
}


void ds18b20_interface_init(void)
{
    /* at21cs - high speed mode after reset */
    
    static uint16_t temp;
    
    PWM1_16BIT_Disable();
    TMR2_Stop();
    
    CLBSWINHbits.CLBSWINH7 = 1;
    
    temp = PERIOD_DIV(12);
    TMR2_PeriodSet((uint8_t)temp);
    
    temp = PERIOD_DIV(SWI_BIT_TIME);
    PWM1_16BIT_WritePeriodRegister(temp);
    temp = PERIOD_DIV(6);
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(temp);
    temp = PERIOD_DIV(64);
    PWM1_16BIT_SetSlice1Output2DutyCycleRegister(temp);
    PWM1CONbits.LD = 1;    
    TMR2_Start();
    
}

void ds18b20_write_byte(uint8_t data)
{
   OneWire_WriteByte(byte_reverse(data));
    __delay_us(SWI_BIT_TIME);
}

uint8_t ds18b20_read_byte(void)
{
    uint8_t data = byte_reverse(OneWire_ReadByte(false));
    __delay_us(SWI_BIT_TIME);
    return data; 
}

void ds18b20_startTempMeas(void)
{
    ds18b20_write_byte(SKIPROM);
    ds18b20_write_byte(GETTEMP);  
}

float ds18b20_readTempMeas(void)
{
    uint8_t rd_data0, rd_data1;
    float temp;
    
    ds18b20_write_byte(SKIPROM);
    ds18b20_write_byte(READSCRATCH);  

    
    rd_data0 = ds18b20_read_byte();
    rd_data1 = ds18b20_read_byte();
    temp = (rd_data0 * 1.0f);
    temp += (rd_data1*256.0f);
    temp =  (float)(temp/16.0f);
   
    return temp;   
}

/* uint8_t - ds18b20_searchbus */ 

void ds18b20_read_rom(uint8_t* rd_id)           
{
    ds18b20_write_byte(READROM);

    for (uint8_t i = 0;i <8;i++)
    {
       rd_id[i] = ds18b20_read_byte();
    }
}
