        MODULE  ?cstartup

//------------------------------------------------------------------------------

        EXTERN  SystemInit
        EXTERN  __iar_program_start

        PUBLIC  __vector_table
        PUBLIC  Reset_Handler

        PUBWEAK BusFault_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK MemManage_Handler
        PUBWEAK NMI_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SVC_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK UsageFault_Handler


        SECTION CSTACK:DATA:NOROOT(3)
//------------------------------------------------------------------------------
        SECTION .intvec:CONST:ROOT(2)
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler             ; Reset Handler
        DCD     NMI_Handler               ; NMI Handler
        DCD     HardFault_Handler         ; Hard Fault Handler
        DCD     MemManage_Handler         ; MPU Fault Handler
        DCD     BusFault_Handler          ; Bus Fault Handler
        DCD     UsageFault_Handler        ; Usage Fault Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     SVC_Handler               ; SVCall Handler
        DCD     DebugMon_Handler          ; Debug Monitor Handler
        DCD     0                         ; Reserved
        DCD     PendSV_Handler            ; PendSV Handler
        DCD     SysTick_Handler           ; SysTick Handler


//------------------------------------------------------------------------------
        SECTION .text:CODE:REORDER:NOROOT(2)
        THUMB

Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0

        LDR     R0, =__iar_program_start
        BX      R0

        SECTION .text:CODE:REORDER:NOROOT(1)
        THUMB


//------------------------------------------------------------------------------
// Default interrupt handlers
//
BusFault_Handler
DebugMon_Handler
HardFault_Handler
MemManage_Handler
NMI_Handler
PendSV_Handler
SVC_Handler
SysTick_Handler
UsageFault_Handler
        B       .

#include "IAR_AARM_Define.h"

//------------------------------------------------------------------------------
// head and tail
//------------------------------------------------------------------------------
#if ( __GEN_IMAGE__ > 0 )

        PUBLIC __image_magic0
        PUBLIC __image_magic1
        PUBLIC __image_magic2
        PUBLIC __image_magic3

        PUBLIC __image_size
        PUBLIC __image_addr

        PUBLIC __image_start

#if ( __BOOT_LOADER__ > 0 )
        PUBLIC __image_app_offset
        PUBLIC __image_dummy
        PUBLIC __image_valid_patten

#else
        PUBLIC __sdram_start_val
        PUBLIC __sdram_end_val
        PUBLIC __image_magic4
        PUBLIC __image_magic5
        PUBLIC __image_magic6
        PUBLIC __image_magic7
        PUBLIC __image_vector_table
#endif

        PUBLIC __image_date
        PUBLIC __image_time
        PUBLIC __image_version
        PUBLIC __image_type
        PUBLIC __image_checksum
        PUBLIC __image_end

        PUBLIC __sdram_start
        PUBLIC __sdram_checksum
        PUBLIC __sdram_end

//------------------------------------------------------------------------------
        SECTION `.image.head`:CONST:ROOT(2)
//------------------------------------------------------------------------------
// image[signature] + image[head] + image[body] + image[tail]
// 0x1000-0BA8        0x1000-0BC8   0x1000-0C00
//
// Stored :  0x98000000  : Bootloader
// Stored :  0x9800B000  : Default Application
// Stored : [0x98009000] : OTA Application
//
// Loaded : Never
//
#if ( __BOOT_LOADER__ > 0 )

//------------------------------------------------------------------------------
// Bootloader -- Loaded By ROM Loader, We can change nothing
//------------------------------------------------------------------------------
__image_magic0                    // 0x10000BA8
        DCD     0x96969999
__image_magic1                    // 0x10000BAC
        DCD     0xFC66CC3F
__image_magic2                    // 0x10000BB0
        DCD     0x03CC33C0
__image_magic3                    // 0x10000BB4
        DCD     0x6231DCE5
//------------------------------------------------------------------------------
__image_size                      // 0x10000BB8 : 0x00003A98
        DCD     __image_end - __image_start
__image_addr                      // 0x10000BBC : 0x10000BC8
        DCD     __image_start
__image_app_offset                // 0x10000BC0 : 0x002C * 1024 = 0xB000
        DCD     0xFFFF002C        //
__image_dummy                     // 0x10000BC4 : 0xFFFFFFFF
        DCD     0xFFFFFFFF
__image_start
        DCD     Reset_Handler     // 0x10000BC8
        DCD     Reset_Handler     // 0x10000BCC
        DCD     Reset_Handler     // 0x10000BD0
        DCD     Reset_Handler     // 0x10000BD4
        DCD     Reset_Handler     // 0x10000BD8
__image_valid_patten
        DCD     0x88167923        // 0x10000BDC
__image_date                      // 0x10000BE0
        DCD     __DATE__
__image_time                      // 0x10000BEC
        DCD     __TIME__
__image_version                   // 0x10000BF8
        DCD     0x00010000        // 1.0.0
__image_type                      // 0x10000BF8
        DCD     "BTL"             // 0x10000BFC : To Be filled
#else
//------------------------------------------------------------------------------
// ( __BOOT_LOADER__ == 0 ) : Application -- Loaded By Bootloader
//------------------------------------------------------------------------------
__image_magic0                    // 0x10000BA8
        DCD     0x96969999
__image_magic1                    // 0x10000BAC
        DCD     0xFC66CC3F
__image_magic2                    // 0x10000BB0
        DCD     0x03CC33C0
__image_magic3                    // 0x10000BB4
        DCD     0x6231DCE5
//------------------------------------------------------------------------------
__image_size                      // 0x10000BB8
        DCD     __image_end - __image_start
__image_addr                      // 0x10000BBC
        DCD     __image_start
__sdram_start_val                 // 0x10000BC0
        DCD     __sdram_start     //
__sdram_end_val                   // 0x10000BC4
        DCD     __sdram_end
__image_start
        DCD     Reset_Handler     // 0x10000BC8
__image_magic4
        DCD     0x96969999        // 0x10000BCC
__image_magic5
        DCD     0xFC66CC3F        // 0x10000BD0
__image_magic6
        DCD     0x03CC33C0        // 0x10000BD4
__image_magic7
        DCD     0x6231DCE5        // 0x10000BD8
__image_vector_table
        DCD     __vector_table    // 0x10000BDC
__image_date                      // 0x10000BE0
        DCD     __DATE__
__image_time                      // 0x10000BEC
        DCD     __TIME__
__image_version                   // 0x10000BF8
        DCD     0x00010000        // 1.0.0
__image_type                      // 0x10000BF8
        DCD     "APP"             // 0x10000BFC : To Be filled
#endif

//------------------------------------------------------------------------------
// 0x1000C000 : Vectot Table at here
//------------------------------------------------------------------------------

        SECTION `.image.tail`:CONST:ROOT(2)
//------------------------------------------------------------------------------
__image_checksum
        DCD     0x00000000
__image_end

        SECTION `.sdram.head`:CONST:ROOT(2)
//------------------------------------------------------------------------------
        DATA
__sdram_start
        DCD     0x55AA55AA

        SECTION `.sdram.tail`:CONST:ROOT(2)
//------------------------------------------------------------------------------
__sdram_checksum
        DCD     0x00000000
__sdram_end

#endif

        END
