/**
 *  @file clbBitstream.s
 *
 *  @brief CLB bitstream data for the PIC18FxyQ35 device family
 *
 **/
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

/*
    The bitstream data can be accesed from C source code by referencing the 'start_clb_config' symbol as such:

    extern uint16_t start_clb_config;
    uint16_t clbStartAddress = (uint16_t) &start_clb_config;

    IMPORTANT: You must always use the address of these symbols and not the value of the symbols themselves.
               If values instead of addresses are used, the linker will silently generate incorrect code.

    uint16_t clbStartAddress = start_clb_config; // This is incorrect!

    NOTE: This module requires C preprocessing.
          This can be enabled via the command line option: -xassembler-with-cpp
*/


#include <xc.inc>


#if !(defined (_18F26Q35) || defined (_18F46Q35) || defined (_18F56Q35) \
    || defined (_18F25Q35) || defined (_18F45Q35) || defined (_18F55Q35) \
    || defined (_18F24Q35) || defined (_18F44Q35) || defined (_18F54Q35))
	
    #error This module is only suitable for PIC18F56Q35 family devices
#endif

GLOBAL  _start_clb_config
GLOBAL  _end_clb_config

PSECT  clb_config,global,class=CONST,delta=1,noexec,keep,reloc=100h

_start_clb_config:
    DW  0x0048
    DW  0x0049
    DW  0x004A
    DW  0x004B
    DW  0x004C
    DW  0x004D
    DW  0x004E
    DW  0x004F
    DW  0x006B
    DW  0x0068
    DW  0x0051
    DW  0x00E8
    DW  0x0040
    DW  0x00E2
    DW  0x0052
    DW  0x00D0
    DW  0x0050
    DW  0x0054
    DW  0x0057
    DW  0x0041
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0040
    DW  0x0060
    DW  0x0000
    DW  0x0186
    DW  0x0267
    DW  0x4747
    DW  0xE4CC
    DW  0xBF80
    DW  0x03F3
    DW  0x0000
    DW  0x0033
    DW  0xF0F0
    DW  0x0000
    DW  0x0161
    DW  0x9324
    DW  0x2595
    DW  0x1510
    DW  0x0000
    DW  0x5030
    DW  0x0500
    DW  0x0000
    DW  0x0069
    DW  0x0010
    DW  0x00C0
    DW  0x0080
    DW  0x0000
    DW  0x0206
    DW  0x0243
    DW  0x0051
    DW  0x11DD
    DW  0xC0F3
    DW  0x0103
    DW  0xF0F0
    DW  0xCCCC
    DW  0x4444
    DW  0xF0F0
    DW  0xFF00
    DW  0x10A1
    DW  0x7230
    DW  0x9119
    DW  0x0900
    DW  0x0010
    DW  0x0014
    DW  0x0500
    DW  0x5000
    DW  0x00FD
    DW  0x0008
    DW  0x0000
    DW  0x0070
    DW  0xF300
    DW  0x0706
    DW  0x01E4
    DW  0x0005
    DW  0x550F
    DW  0xDF80
    DW  0x3232
    DW  0xF0F0
    DW  0x0000
    DW  0x0000
    DW  0xF0F0
    DW  0xCCCC
    DW  0xA101
    DW  0x2767
    DW  0x0412
    DW  0x0500
    DW  0x0000
    DW  0x0000
    DW  0x0500
    DW  0x0060
    DW  0x00C9
    DW  0x0010
    DW  0x0000
    DW  0x00E0
    DW  0x020B
    DW  0x0200
    DW  0x0001
    DW  0x01A0
    DW  0x1D1D
    DW  0xCAAA
    DW  0xCAAA
    DW  0x0000
    DW  0xF0F0
    DW  0x0000
    DW  0x0000
    DW  0xF0F0
    DW  0x0161
    DW  0x1532
    DW  0x1352
    DW  0x0000
    DW  0x0500
    DW  0x0000
    DW  0x0000
    DW  0x0500
    DW  0x0091
    DW  0x0000
    DW  0x0008
    DW  0x0050
    DW  0x0000
    DW  0x0308
    DW  0x000B
    DW  0x0250
    DW  0xFFF0
    DW  0x7020
    DW  0x33BB
    DW  0xFF00
    DW  0xFF00
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x4700
    DW  0x2161
    DW  0x1065
    DW  0x1000
    DW  0x9000
    DW  0x0001
    DW  0x0000
    DW  0x0000
    DW  0x0039
    DW  0x0000
    DW  0x0010
    DW  0x0030
    DW  0x0900
    DW  0x0501
    DW  0x022A
    DW  0x01A0
    DW  0x4477
    DW  0xE4CC
    DW  0x4444
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x4011
    DW  0x1724
    DW  0x0054
    DW  0x0050
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x000C
    DW  0x2000
    DW  0x0000
    DW  0x0020
    DW  0x0E00
    DW  0x0200
    DW  0x0000
    DW  0x01A0
    DW  0x0ACC
    DW  0xE2AA
    DW  0xD8F0
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xA377
    DW  0x1492
    DW  0x1254
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0001
    DW  0x0040
    DW  0x0000
    DW  0x0040
    DW  0x002F
    DW  0x0300
    DW  0x0128
    DW  0x01CB
    DW  0x5533
    DW  0xC000
    DW  0xCF80
    DW  0xF0F0
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x1011
    DW  0xA590
    DW  0x2165
    DW  0x0100
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x000B
    DW  0x0010
    DW  0x0000
    DW  0x0FB0
    DW  0x0D00
    DW  0x0B00
    DW  0x0008
    DW  0x0009
    DW  0xF0E2
    DW  0x3333
    DW  0xD058
    DW  0xCCCC
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x5171
    DW  0x0060
    DW  0x32A4
    DW  0x0050
    DW  0x0050
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x001B
    DW  0x0010
    DW  0x0000
    DW  0x0090
    DW  0x0130
    DW  0x0205
    DW  0x0000
    DW  0x0160
    DW  0x4455
    DW  0x0C0F
    DW  0x5500
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xF0F0
    DW  0x1067
    DW  0x1360
    DW  0x1004
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0500
    DW  0x0084
    DW  0x0000
    DW  0x0000
    DW  0x0090
    DW  0x0002
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x001B
    DW  0xC03F
    DW  0xCCCC
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x3774
    DW  0x3560
    DW  0x0050
    DW  0x0050
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x000F
    DW  0x0010
    DW  0x0000
    DW  0x00E0
    DW  0x0860
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x4700
    DW  0x9333
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x9767
    DW  0xA494
    DW  0x0004
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0007
    DW  0x1000
    DW  0x0000
    DW  0x00F0
    DW  0x0608
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x00CC
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x9030
    DW  0x0090
    DW  0x0000
    DW  0x0000
    DW  0x0090
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0011
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0D00
    DW  0x0500
    DW  0x000D
    DW  0x0000
    DW  0xCCCC
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0060
    DW  0x0001
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0002
    DW  0x1000
    DW  0x0000
    DW  0x0080
    DW  0x0700
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xAAAA
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0003
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0002
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0xCCCC
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0050
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0004
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
    DW  0x0000
_end_clb_config:
 