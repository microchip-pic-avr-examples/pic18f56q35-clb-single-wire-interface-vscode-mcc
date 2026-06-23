
#include "config.mcc/mcc_generated_files/system/system.h"
#include "SingleWire.h"
#include <stdbool.h>


#define PERIOD_DIV(delay_us)    (((_XTAL_FREQ * delay_us) / (4 *1000000)) - 1)


#define SWI_BIT_TIME         12
#define SWI_WR_LOW0          5 
#define SWI_WR_LOW1          1



/******************************************
 * 
 * AT21CS01 OpCodes
 *  
 *****************************************/
#define EEPROM_ACCESS       0x0A
#define SEC_ACCESS          0x0B
#define LOCK_SEC            0x02
#define ROM_ACCESS          0x07
#define LOCK_ROM            0x01
#define READ_ID             0x0C
#define SET_STD_SPEED       0x0D
#define SET_HIGH_SPEED      0x0E   



static uint8_t dev_addr = 0xFF;



bool at21cs_swi_detect(void)
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

void at21cs_interface_init(void)
{
    //at21cs - high speed mode after reset
    
    static uint8_t temp;
    
    PWM1_16BIT_Disable();
    TMR2_Stop();
    
    CLBSWINHbits.CLBSWINH7 = 0;
    
    temp = PERIOD_DIV(SWI_RD_STROBE);
    TMR2_PeriodSet(temp);
    
    temp = PERIOD_DIV(SWI_BIT_TIME);
    PWM1_16BIT_WritePeriodRegister(temp);
    temp = PERIOD_DIV(SWI_WR_LOW1);
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(temp);
    temp = PERIOD_DIV(SWI_WR_LOW0);
    PWM1_16BIT_SetSlice1Output2DutyCycleRegister(temp);
    PWM1CONbits.LD = 1;    
    TMR2_Start();
    
}

uint8_t at21cs_get_addr(void)
{
    return dev_addr;
}

bool at21cs_send_cmd(uint8_t cmd, bool read_op)
{
    uint8_t send_byte;
 
    //start/stop delay
    __delay_us(SWI_INTERCMD); 
    
    send_byte = (uint8_t)((cmd << 4) | (dev_addr << 1));
    if (read_op == true) send_byte |= 0x01;      
    
    return OneWire_WriteByte(send_byte);    
}

bool at21cs_scan_address(void)
{
    uint8_t i;
    if (at21cs_swi_detect() == true)
    {
        for (i= 0; i < 8; i++)
        {
            dev_addr = i;
            //dummy read EEPROM to check ack/nack
            if (at21cs_send_cmd(EEPROM_ACCESS, true) == true) break;
        }
        if (i < 8) 
        {
           dev_addr = i;
           return true;
        }        
    }
    dev_addr = 0xFF;
    return false;
}
bool at21cs_read_id(uint8_t* rd_sn)           
{
    //Read Serial number  - rd sn        
    if (at21cs_send_cmd(READ_ID, true) == true)
    {
        rd_sn[0] = OneWire_ReadByte(ACK);
        rd_sn[1] = OneWire_ReadByte(ACK);
        rd_sn[2] = OneWire_ReadByte(NACK);
        return true;
    }  
    else return false;   
}

bool at21cs_read_serial(uint8_t* rd_id)           
{
    
//Read Serial number  - set address to 0x00         
    if (at21cs_send_cmd(SEC_ACCESS,false) == true)
    {
        OneWire_WriteByte(0x00);
    }
    else return false;

    //Read Serial number  - rd sn        
    if (at21cs_send_cmd(SEC_ACCESS, true) == true)
    {
        rd_id[0] = OneWire_ReadByte(ACK);
        rd_id[1] = OneWire_ReadByte(ACK);
        rd_id[2] = OneWire_ReadByte(ACK);
        rd_id[3] = OneWire_ReadByte(ACK);
        rd_id[4] = OneWire_ReadByte(ACK);
        rd_id[5] = OneWire_ReadByte(ACK);
        rd_id[6] = OneWire_ReadByte(ACK);
        rd_id[7] = OneWire_ReadByte(NACK);
        return true;
    }  
    else return false;   
}

bool at21cs_read_eeprom(uint8_t addr, uint8_t length, uint8_t* rd_data)           
{
    uint8_t i = 0;
    //Read EEPROM  - write address    
    if (at21cs_send_cmd(EEPROM_ACCESS, false)==true)
    {
        OneWire_WriteByte(addr);
    }
    else return false;

    //Read EEPROM data       
    if (at21cs_send_cmd(EEPROM_ACCESS, true) == true)
    {
        for (i=0; i < (length - 1); i++)
        {
             rd_data[i] = OneWire_ReadByte(ACK);
        }
        
        rd_data[i] = OneWire_ReadByte(NACK);
        
        return true;
    }  
    else return false;   
} 

bool at21cs_write_eeprom(uint8_t addr, uint8_t length, uint8_t* wr_data)           
{
    
    if ((addr > 128)||(length > 128)) return false;
    if ((addr + length) > 128) return false;
    
    //Write EEPROM  - set address to 0x00         
    if (at21cs_send_cmd(EEPROM_ACCESS, false)==true)
    {
        if (OneWire_WriteByte(addr) == false) return false;
        for (uint8_t i=0; i < length; i++)
        {
            if (OneWire_WriteByte(wr_data[i]) == false) return false;
        } 
        return true;
    }
    else return false;
}

bool at21cs_check_lock(void)           
{
    if (at21cs_send_cmd(LOCK_SEC, false)==true)
    {
        if (OneWire_WriteByte(0x60) == true) return false;
        return true;
    }
    else return false;
} 
/* The lock is ireversible. Uncomment if used
 */
//bool at21cs_lock(void)           
//{
//    if (at21cs_send_cmd(LOCK_SEC, false)==true)
//    {
//        if (OneWire_WriteByte(0x60) == false) return false;
//        if (OneWire_WriteByte(0x00) == false) return false;
//        return true;
//    }
//    else return false;
//} 