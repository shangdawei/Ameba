#ifndef __RTL8195AM_GPIO_H__
#define __RTL8195AM_GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

#define GPIO_PORTA_DR           0x00        // data register
#define GPIO_PORTA_DDR          0x04        // data direction
#define GPIO_PORTA_CTRL         0x08        // data source control, we should keep it as default: data source from software

#define GPIO_PORTB_DR           0x0c        // data register
#define GPIO_PORTB_DDR          0x10        // data direction
#define GPIO_PORTB_CTRL         0x14        // data source control, we should keep it as default: data source from software

#define GPIO_PORTC_DR           0x18        // data register
#define GPIO_PORTC_DDR          0x1c        // data direction
#define GPIO_PORTC_CTRL         0x20        // data source control, we should keep it as default: data source from software

//1 Only the PORTA can be configured to generate interrupts
#define GPIO_INT_EN             0x30        // Interrupt enable register
#define GPIO_INT_MASK           0x34        // Interrupt mask
#define GPIO_INT_TYPE           0x38        // Interrupt type(level/edge) register
#define GPIO_INT_POLARITY       0x3C        // Interrupt polarity(Active low/high) register
#define GPIO_INT_STATUS         0x40        // Interrupt status
#define GPIO_INT_RAWSTATUS      0x44        // Interrupt status without mask
#define GPIO_DEBOUNCE           0x48        // Interrupt signal debounce
#define GPIO_PORTA_EOI          0x4c        // Clear interrupt

#define GPIO_EXT_PORTA          0x50        // GPIO IN read or OUT read back
#define GPIO_EXT_PORTB          0x54        // GPIO IN read or OUT read back
#define GPIO_EXT_PORTC          0x58        // GPIO IN read or OUT read back

#define GPIO_INT_SYNC           0x60        // Is level-sensitive interrupt being sync sith PCLK

enum
{
  HAL_GPIO_HIGHZ = 0,
  HAL_GPIO_PULL_LOW = 1,
  HAL_GPIO_PULL_HIGH = 2
};

typedef enum
{
  GPIO_Mode_IN = 0x00, /*!< GPIO Input Mode             */
  GPIO_Mode_OUT = 0x01, /*!< GPIO Output Mode                */
  GPIO_Mode_INT = 0x02, /*!< GPIO Interrupt Mode                */
  GPIO_Mode_MAX = 0x03,
} GPIOMode_TypeDef;

/**
 * @brief  GPIO Configuration PullUp PullDown enumeration
 */
typedef enum
{
  GPIO_PuPd_NOPULL = 0x00, /*!< GPIO Interrnal HIGHZ */
  GPIO_PuPd_DOWN = 0x01, /*!< GPIO Interrnal Pull DOWN */
  GPIO_PuPd_UP = 0x02, /*!< GPIO Interrnal Pull UP */
} GPIOPuPd_TypeDef;

/**
 * @brief Setting interrupt's trigger type
 *
 * Setting interrupt's trigger type
 */
typedef enum
{
  GPIO_INT_Trigger_LEVEL = 0x0, /**< This interrupt is level trigger  */
  GPIO_INT_Trigger_EDGE = 0x1, /**< This interrupt is edge trigger  */
} GPIOIT_LevelType;

/**
 * @brief Setting interrupt active mode
 *
 * Setting interrupt active mode
 */
typedef enum
{
  GPIO_INT_POLARITY_ACTIVE_LOW = 0x0, /**< Setting interrupt to low active: falling edge or low level  */
  GPIO_INT_POLARITY_ACTIVE_HIGH = 0x1, /**< Setting interrupt to high active: rising edge or high level */
} GPIOIT_PolarityType;

/**
 * @brief Enable/Disable interrupt debounce mode
 *
 * Enable/Disable interrupt debounce mode
 */
typedef enum
{
  GPIO_INT_DEBOUNCE_DISABLE = 0x0, /**< Disable interrupt debounce  */
  GPIO_INT_DEBOUNCE_ENABLE = 0x1, /**< Enable interrupt debounce   */
} GPIOIT_DebounceType;

typedef struct
{
  GPIOMode_TypeDef GPIO_Mode; /*!< Specifies the operating mode for the selected pins. */
  GPIOPuPd_TypeDef GPIO_PuPd; /*!< Specifies the operating Pull-up/Pull down for the selected pins. */
  GPIOIT_LevelType GPIO_ITTrigger; /**< Interrupt mode is level or edge trigger */
  GPIOIT_PolarityType GPIO_ITPolarity; /**< Interrupt mode is high or low active trigger */
  GPIOIT_DebounceType GPIO_ITDebounce; /**< Enable or disable de-bounce for interrupt */
  u32 GPIO_Pin;    // Pin: [7:5]: port number, [4:0]: pin number
} GPIO_InitTypeDef;

//======================================================
// ROM Function prototype
extern PHAL_GPIO_ADAPTER _pHAL_Gpio_Adapter;
#ifndef CONFIG_RELEASE_BUILD_LIBRARIES
static __inline HAL_STATUS
GPIO_Lock( VOID )
{
  HAL_STATUS Status;

  if ( _pHAL_Gpio_Adapter->EnterCritical )
  {
    _pHAL_Gpio_Adapter->EnterCritical( );
  }

  if ( _pHAL_Gpio_Adapter->Locked )
  {
    Status = HAL_BUSY;
  }
  else
  {
    _pHAL_Gpio_Adapter->Locked = 1;
    Status = HAL_OK;
  }

  if ( _pHAL_Gpio_Adapter->ExitCritical )
  {
    _pHAL_Gpio_Adapter->ExitCritical( );
  }

  return Status;
}

static __inline VOID
GPIO_UnLock( VOID )
{
  if ( _pHAL_Gpio_Adapter->EnterCritical )
  {
    _pHAL_Gpio_Adapter->EnterCritical( );
  }

  _pHAL_Gpio_Adapter->Locked = 0;

  if ( _pHAL_Gpio_Adapter->ExitCritical )
  {
    _pHAL_Gpio_Adapter->ExitCritical( );
  }
}
#endif  // #ifndef CONFIG_RELEASE_BUILD_LIBRARIES

_LONG_CALL_ extern u32
HAL_GPIO_IrqHandler_8195a(
    IN VOID *pData
);

_LONG_CALL_ extern u32
HAL_GPIO_MbedIrqHandler_8195a(
    IN VOID *pData
);

_LONG_CALL_ HAL_STATUS
HAL_GPIO_IntCtrl_8195a( HAL_GPIO_PIN *GPIO_Pin, u32 En );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_Init_8195a( HAL_GPIO_PIN *GPIO_Pin );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_DeInit_8195a( HAL_GPIO_PIN *GPIO_Pin );

_LONG_CALL_ HAL_GPIO_PIN_STATE
HAL_GPIO_ReadPin_8195a( HAL_GPIO_PIN *GPIO_Pin );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_WritePin_8195a( HAL_GPIO_PIN *GPIO_Pin, HAL_GPIO_PIN_STATE Pin_State );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_RegIrq_8195a(
    IN PIRQ_HANDLE pIrqHandle
);

_LONG_CALL_ HAL_STATUS
HAL_GPIO_UnRegIrq_8195a(
    IN PIRQ_HANDLE pIrqHandle
);

_LONG_CALL_ HAL_STATUS
HAL_GPIO_UserRegIrq_8195a( HAL_GPIO_PIN *GPIO_Pin, VOID *IrqHandler, VOID *IrqData );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_UserUnRegIrq_8195a( HAL_GPIO_PIN *GPIO_Pin );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_MaskIrq_8195a( HAL_GPIO_PIN *GPIO_Pin );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_UnMaskIrq_8195a( HAL_GPIO_PIN *GPIO_Pin );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_IntDebounce_8195a( HAL_GPIO_PIN *GPIO_Pin, u8 Enable );

_LONG_CALL_ u32
HAL_GPIO_GetIPPinName_8195a( u32 chip_pin );

_LONG_CALL_ HAL_STATUS
HAL_GPIO_PullCtrl_8195a( u32 chip_pin, u8 pull_type );

_LONG_CALL_ u32
GPIO_GetChipPinName_8195a( u32 port, u32 pin );

_LONG_CALL_ VOID
GPIO_PullCtrl_8195a( u32 chip_pin, u8 pull_type );

_LONG_CALL_ VOID
GPIO_Int_SetType_8195a( u8 pin_num, u8 int_mode );

_LONG_CALL_ HAL_STATUS HAL_GPIO_IntCtrl_8195aV02( HAL_GPIO_PIN *GPIO_Pin, u32 En );
_LONG_CALL_ u32 GPIO_Int_Clear_8195aV02( u32 irq_clr );

HAL_STATUS
HAL_GPIO_ClearISR_8195a( HAL_GPIO_PIN *GPIO_Pin );

/********** HAL In-Line Functions **********/

/**
 * @brief  Reads the specified input port pin.
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin.
 *
 * @retval The input port pin current status(High or Low).
 */
static __inline s32
HAL_GPIO_ReadPin( HAL_GPIO_PIN *GPIO_Pin )
{
  return (s32) HAL_GPIO_ReadPin_8195a( GPIO_Pin );
}

/**
 * @brief  Write the specified output port pin.
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin.
 *
 * @param  Pin_State: The state going to be set to the assigned GPIO pin.
 *
 * @retval None
 */
static __inline VOID
HAL_GPIO_WritePin( HAL_GPIO_PIN *GPIO_Pin, u32 Value )
{
  HAL_GPIO_WritePin_8195a( GPIO_Pin, (HAL_GPIO_PIN_STATE) Value );
}

/**
 * @brief  To register a user interrupt handler for a specified pin
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin.
 *
 * @param  IrqHandler: The IRQ handler to be assigned to the specified pin
 *
 * @param  IrqData: The pointer will be pass the the IRQ handler
 *
 * @retval None
 */
static __inline VOID
HAL_GPIO_UserRegIrq( HAL_GPIO_PIN *GPIO_Pin, VOID *IrqHandler, VOID *IrqData )
{
  HAL_GPIO_UserRegIrq_8195a( GPIO_Pin, IrqHandler, IrqData );
}

/**
 * @brief  To un-register a user interrupt handler for a specified pin
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin.
 *
 * @retval None
 */
static __inline VOID
HAL_GPIO_UserUnRegIrq( HAL_GPIO_PIN *GPIO_Pin )
{
  HAL_GPIO_UserUnRegIrq_8195a( GPIO_Pin );
}

/**
 * @brief  Enable/Disable GPIO interrupt
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin initialization.
 *
 * @param  En: Enable (1) or Disable (0)
 *
 * @retval HAL_STATUS
 */
static __inline VOID
HAL_GPIO_IntCtrl( HAL_GPIO_PIN *GPIO_Pin, u32 En )
{
  HAL_GPIO_IntCtrl_8195a( GPIO_Pin, En );
}

/**
 * @brief  Mask the interrupt of a specified pin
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin.
 *
 * @retval None
 */
static __inline VOID
HAL_GPIO_MaskIrq( HAL_GPIO_PIN *GPIO_Pin )
{
  HAL_GPIO_MaskIrq_8195a( GPIO_Pin );
}

/**
 * @brief  UnMask the interrupt of a specified pin
 *
 * @param  GPIO_Pin: The data structer which contains the parameters for the GPIO Pin.
 *
 * @retval None
 */
static __inline VOID
HAL_GPIO_UnMaskIrq( HAL_GPIO_PIN *GPIO_Pin )
{
  HAL_GPIO_ClearISR_8195a( GPIO_Pin );
  HAL_GPIO_UnMaskIrq_8195a( GPIO_Pin );
}

#define HAL_GPIO_PIN_INT_MODE       0x80

typedef enum
{
  _PORT_A = 0,
  _PORT_B = 1,
  _PORT_C = 2,
  _PORT_D = 3,
  _PORT_E = 4,
  _PORT_F = 5,
  _PORT_G = 6,
  _PORT_H = 7,
  _PORT_I = 8,
  _PORT_J = 9,
  _PORT_K = 10,

  _PORT_MAX
} HAL_GPIO_PORT_NAME;

typedef enum
{
  _PA_0 = ( _PORT_A << 4 | 0 ),
  _PA_1 = ( _PORT_A << 4 | 1 ),
  _PA_2 = ( _PORT_A << 4 | 2 ),
  _PA_3 = ( _PORT_A << 4 | 3 ),
  _PA_4 = ( _PORT_A << 4 | 4 ),
  _PA_5 = ( _PORT_A << 4 | 5 ),
  _PA_6 = ( _PORT_A << 4 | 6 ),
  _PA_7 = ( _PORT_A << 4 | 7 ),

  _PB_0 = ( _PORT_B << 4 | 0 ),
  _PB_1 = ( _PORT_B << 4 | 1 ),
  _PB_2 = ( _PORT_B << 4 | 2 ),
  _PB_3 = ( _PORT_B << 4 | 3 ),
  _PB_4 = ( _PORT_B << 4 | 4 ),
  _PB_5 = ( _PORT_B << 4 | 5 ),
  _PB_6 = ( _PORT_B << 4 | 6 ),
  _PB_7 = ( _PORT_B << 4 | 7 ),

  _PC_0 = ( _PORT_C << 4 | 0 ),
  _PC_1 = ( _PORT_C << 4 | 1 ),
  _PC_2 = ( _PORT_C << 4 | 2 ),
  _PC_3 = ( _PORT_C << 4 | 3 ),
  _PC_4 = ( _PORT_C << 4 | 4 ),
  _PC_5 = ( _PORT_C << 4 | 5 ),
  _PC_6 = ( _PORT_C << 4 | 6 ),
  _PC_7 = ( _PORT_C << 4 | 7 ),
  _PC_8 = ( _PORT_C << 4 | 8 ),
  _PC_9 = ( _PORT_C << 4 | 9 ),

  _PD_0 = ( _PORT_D << 4 | 0 ),
  _PD_1 = ( _PORT_D << 4 | 1 ),
  _PD_2 = ( _PORT_D << 4 | 2 ),
  _PD_3 = ( _PORT_D << 4 | 3 ),
  _PD_4 = ( _PORT_D << 4 | 4 ),
  _PD_5 = ( _PORT_D << 4 | 5 ),
  _PD_6 = ( _PORT_D << 4 | 6 ),
  _PD_7 = ( _PORT_D << 4 | 7 ),
  _PD_8 = ( _PORT_D << 4 | 8 ),
  _PD_9 = ( _PORT_D << 4 | 9 ),

  _PE_0 = ( _PORT_E << 4 | 0 ),
  _PE_1 = ( _PORT_E << 4 | 1 ),
  _PE_2 = ( _PORT_E << 4 | 2 ),
  _PE_3 = ( _PORT_E << 4 | 3 ),
  _PE_4 = ( _PORT_E << 4 | 4 ),
  _PE_5 = ( _PORT_E << 4 | 5 ),
  _PE_6 = ( _PORT_E << 4 | 6 ),
  _PE_7 = ( _PORT_E << 4 | 7 ),
  _PE_8 = ( _PORT_E << 4 | 8 ),
  _PE_9 = ( _PORT_E << 4 | 9 ),
  _PE_A = ( _PORT_E << 4 | 10 ),

  _PF_0 = ( _PORT_F << 4 | 0 ),
  _PF_1 = ( _PORT_F << 4 | 1 ),
  _PF_2 = ( _PORT_F << 4 | 2 ),
  _PF_3 = ( _PORT_F << 4 | 3 ),
  _PF_4 = ( _PORT_F << 4 | 4 ),
  _PF_5 = ( _PORT_F << 4 | 5 ),
//    _PF_6  = (_PORT_F<<4|6),
//    _PF_7  = (_PORT_F<<4|7),

  _PG_0 = ( _PORT_G << 4 | 0 ),
  _PG_1 = ( _PORT_G << 4 | 1 ),
  _PG_2 = ( _PORT_G << 4 | 2 ),
  _PG_3 = ( _PORT_G << 4 | 3 ),
  _PG_4 = ( _PORT_G << 4 | 4 ),
  _PG_5 = ( _PORT_G << 4 | 5 ),
  _PG_6 = ( _PORT_G << 4 | 6 ),
  _PG_7 = ( _PORT_G << 4 | 7 ),

  _PH_0 = ( _PORT_H << 4 | 0 ),
  _PH_1 = ( _PORT_H << 4 | 1 ),
  _PH_2 = ( _PORT_H << 4 | 2 ),
  _PH_3 = ( _PORT_H << 4 | 3 ),
  _PH_4 = ( _PORT_H << 4 | 4 ),
  _PH_5 = ( _PORT_H << 4 | 5 ),
  _PH_6 = ( _PORT_H << 4 | 6 ),
  _PH_7 = ( _PORT_H << 4 | 7 ),

  _PI_0 = ( _PORT_I << 4 | 0 ),
  _PI_1 = ( _PORT_I << 4 | 1 ),
  _PI_2 = ( _PORT_I << 4 | 2 ),
  _PI_3 = ( _PORT_I << 4 | 3 ),
  _PI_4 = ( _PORT_I << 4 | 4 ),
  _PI_5 = ( _PORT_I << 4 | 5 ),
  _PI_6 = ( _PORT_I << 4 | 6 ),
  _PI_7 = ( _PORT_I << 4 | 7 ),

  _PJ_0 = ( _PORT_J << 4 | 0 ),
  _PJ_1 = ( _PORT_J << 4 | 1 ),
  _PJ_2 = ( _PORT_J << 4 | 2 ),
  _PJ_3 = ( _PORT_J << 4 | 3 ),
  _PJ_4 = ( _PORT_J << 4 | 4 ),
  _PJ_5 = ( _PORT_J << 4 | 5 ),
  _PJ_6 = ( _PORT_J << 4 | 6 ),
//    _PJ_7  = (_PORT_J<<4|7),

  _PK_0 = ( _PORT_K << 4 | 0 ),
  _PK_1 = ( _PORT_K << 4 | 1 ),
  _PK_2 = ( _PORT_K << 4 | 2 ),
  _PK_3 = ( _PORT_K << 4 | 3 ),
  _PK_4 = ( _PORT_K << 4 | 4 ),
  _PK_5 = ( _PORT_K << 4 | 5 ),
  _PK_6 = ( _PORT_K << 4 | 6 ),
//    _PK_7  = (_PORT_K<<4|7),

  // Not connected
  _PIN_NC = (int) 0xFFFFFFFF
} HAL_PIN_NAME;

typedef enum
{
  GPIO_PIN_LOW = 0,
  GPIO_PIN_HIGH = 1,
  GPIO_PIN_ERR = 2     // read Pin error
} HAL_GPIO_PIN_STATE;

typedef enum
{
  DIN_PULL_NONE = 0,    //floating or high impedance ?
  DIN_PULL_LOW = 1,
  DIN_PULL_HIGH = 2,

  DOUT_PUSH_PULL = 3,
  DOUT_OPEN_DRAIN = 4,

  INT_LOW = ( 5 | HAL_GPIO_PIN_INT_MODE ),    // Interrupt Low level trigger
  INT_HIGH = ( 6 | HAL_GPIO_PIN_INT_MODE ),    // Interrupt High level trigger
  INT_FALLING = ( 7 | HAL_GPIO_PIN_INT_MODE ),    // Interrupt Falling edge trigger
  INT_RISING = ( 8 | HAL_GPIO_PIN_INT_MODE )     // Interrupt Rising edge trigger
} HAL_GPIO_PIN_MODE;

enum
{
  GPIO_PORT_A = 0,
  GPIO_PORT_B = 1,
  GPIO_PORT_C = 2,
  GPIO_PORT_D = 3
};

typedef enum
{
  hal_PullNone = 0,
  hal_PullUp = 1,
  hal_PullDown = 2,
  hal_OpenDrain = 3,
  hal_PullDefault = hal_PullNone
} HAL_PinMode;

typedef struct _HAL_GPIO_PORT_
{
  u32 out_data;       // to write the GPIO port
  u32 in_data;        // to read the GPIO port
  u32 dir;            // config each pin direction
} HAL_GPIO_PORT, *PHAL_GPIO_PORT;

#define HAL_GPIO_PIN_NAME(port,pin)         (((port)<<5)|(pin))
#define HAL_GPIO_GET_PORT_BY_NAME(x)        ((x>>5) & 0x03)
#define HAL_GPIO_GET_PIN_BY_NAME(x)         (x & 0x1f)

typedef struct _HAL_GPIO_PIN_
{
  HAL_GPIO_PIN_MODE pin_mode;
  u32 pin_name;    // Pin: [7:5]: port number, [4:0]: pin number
} HAL_GPIO_PIN, *PHAL_GPIO_PIN;

typedef struct _HAL_GPIO_OP_
{
#if defined(__ICCARM__)
  void* dummy;
#endif
} HAL_GPIO_OP, *PHAL_GPIO_OP;

typedef void (*GPIO_IRQ_FUN)( VOID *Data, u32 Id );
typedef void (*GPIO_USER_IRQ_FUN)( u32 Id );

typedef struct _HAL_GPIO_ADAPTER_
{
  IRQ_HANDLE IrqHandle;   // GPIO HAL IRQ Handle
  GPIO_USER_IRQ_FUN UserIrqHandler;   // GPIO IRQ Handler
  GPIO_IRQ_FUN PortA_IrqHandler[ 32 ]; // The interrupt handler triggered by Port A[x]
  VOID *PortA_IrqData[ 32 ];
  VOID (*EnterCritical)( void );
  VOID (*ExitCritical)( void );
  u32 Local_Gpio_Dir[ 3 ];  // to record direction setting: 0- IN, 1- Out
  u8 Gpio_Func_En;    // Is GPIO HW function enabled ?
  u8 Locked;
} HAL_GPIO_ADAPTER, *PHAL_GPIO_ADAPTER;

u32
HAL_GPIO_GetPinName( u32 chip_pin );

VOID
HAL_GPIO_PullCtrl( u32 pin, u32 mode );

VOID
HAL_GPIO_Init( HAL_GPIO_PIN *GPIO_Pin );

VOID
HAL_GPIO_Irq_Init( HAL_GPIO_PIN *GPIO_Pin );

VOID
HAL_GPIO_IP_DeInit( VOID );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_GPIO_H__ */
