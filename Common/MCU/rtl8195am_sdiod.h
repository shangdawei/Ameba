#ifndef __RTL8195AM_SDIO_DEVICE_H__
#define __RTL8195AM_SDIO_DEVICE_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"


#if defined(CONFIG_SDIO_BOOT_SIM) || defined(CONFIG_SDIO_BOOT_ROM)
#define SDIO_BOOT_DRIVER                            1   // is this SDIO driver works for booting
#else

#define SDIO_BOOT_DRIVER                            0   // is this SDIO driver works for booting
#endif

#if defined(__IAR_SYSTEMS_ICC__) //for IAR SDK

#endif

#ifndef CONFIG_INIC_EN
#define CONFIG_INIC_EN 0
#endif
#if CONFIG_INIC_EN
#define CONFIG_INIC_SKB_TX 1 //use SKB for trx to improve the throughput
#define CONFIG_INIC_SKB_RX 1
#endif

#if defined(__IAR_SYSTEMS_ICC__) && (CONFIG_INIC_EN == 0)//for IAR SDK
#define SDIO_API_DEFINED	 1
#else
#define SDIO_API_DEFINED	 0
#endif

#ifndef PRIORITIE_OFFSET //PRIORITIE_OFFSET in FreeRTOSConfig.h
#define PRIORITIE_OFFSET 0
#endif

#define SDIO_DEBUG									0
#define SDIO_MP_MODE								0	// if includes MP mode function
#define SDIO_MAX_WAIT_RX_DMA						100	// Wait RX DMA done
#define SDIO_RX_PKT_SIZE_OVER_16K					0	/* is support SDIO RX packet size > 16K. if true,
															a big packet will be transmited via multiple RX_BD */
#define SDIO_MAILBOX_SIZE                           10  // the maximum number of message block can be stored in this mailbox
#define SDIO_PERIODICAL_TIMER_INTERVAL              2000    // in ms, the interval of SDIO periodical timer
#define SDIO_AVG_TP_WIN_SIZE                        20      // the number of entry to log the byte count for every periodical timer statistic, to calculate throughput

#define HAL_SDIO_READ32(addr)            			HAL_READ32(SDIO_DEVICE_REG_BASE, addr)
#define HAL_SDIO_WRITE32(addr, value)    			HAL_WRITE32(SDIO_DEVICE_REG_BASE, addr, value)
#define HAL_SDIO_READ16(addr)						HAL_READ16(SDIO_DEVICE_REG_BASE, addr)
#define HAL_SDIO_WRITE16(addr, value)    			HAL_WRITE16(SDIO_DEVICE_REG_BASE, addr, value)
#define HAL_SDIO_READ8(addr)						HAL_READ8(SDIO_DEVICE_REG_BASE, addr)
#define HAL_SDIO_WRITE8(addr, value)    			HAL_WRITE8(SDIO_DEVICE_REG_BASE, addr, value)

/*****  Register Address *****/
#define REG_SPDIO_TXBD_ADDR 						0xA0        // 4 Bytes
#define REG_SPDIO_TXBD_SIZE							0xA4        // 4 Bytes
#define REG_SPDIO_TXBD_WPTR							0xA8        // 2 Bytes
#define REG_SPDIO_TXBD_RPTR							0xAC        // 2 Bytes
#define REG_SPDIO_RXBD_ADDR							0xB0		// 4 Bytes
#define REG_SPDIO_RXBD_SIZE							0xB4		// 2 Bytes
#define REG_SPDIO_RXBD_C2H_WPTR						0xB6		// 2 Bytes
#define REG_SPDIO_RXBD_C2H_RPTR						0xB8		// 2 Bytes
#define REG_SPDIO_HCI_RX_REQ						0xBA		// 1 Byte
#define REG_SPDIO_CPU_RST_DMA						0xBB		// 1 Byte
#define REG_SPDIO_RX_REQ_ADDR						0xBC		// 2 Bytes
#define REG_SPDIO_CPU_INT_MASK						0xC0		// 2 Bytes
#define REG_SPDIO_CPU_INT_STAS						0xC2		// 2 Bytes
#define REG_SPDIO_CCPWM								0xC4		// 1 Byts
#define REG_SPDIO_CPU_IND							0xC5		// 1 Byte
#define REG_SPDIO_CCPWM2							0xC6		// 2 Bytes
#define REG_SPDIO_CPU_H2C_MSG						0xC8		// 4 Bytes
#define REG_SPDIO_CPU_C2H_MSG						0xCC		// 4 Bytes
#define REG_SPDIO_CRPWM								0xD0		// 1 Bytes
#define REG_SPDIO_CRPWM2							0xD2		// 2 Bytes
#define REG_SPDIO_AHB_DMA_CTRL						0xD4		// 4 Bytes
#define REG_SPDIO_RXBD_CNT					        0xD8		// 4 Bytes
#define REG_SPDIO_TX_BUF_UNIT_SZ			        0xD9		// 1 Bytes
#define REG_SPDIO_RX_BD_FREE_CNT			        0xDA		// 2 Bytes
#define REG_SPDIO_CPU_H2C_MSG_EXT					0xDC		// 4 Bytes
#define REG_SPDIO_CPU_C2H_MSG_EXT					0xE0		// 4 Bytes

// Register REG_SPDIO_CPU_RST_DMA
#define BIT_CPU_RST_SDIO_DMA						BIT(7)

// Register REG_SPDIO_CPU_INT_MASK, REG_SPDIO_CPU_INT_STAS
#define BIT_TXFIFO_H2C_OVF							BIT(0)
#define BIT_H2C_BUS_RES_FAIL						BIT(1)
#define BIT_H2C_DMA_OK								BIT(2)
#define BIT_C2H_DMA_OK								BIT(3)
#define BIT_H2C_MSG_INT								BIT(4)
#define BIT_RPWM1_INT								BIT(5)
#define BIT_RPWM2_INT								BIT(6)
#define BIT_SDIO_RST_CMD_INT						BIT(7)
#define BIT_RXBD_FLAG_ERR_INT						BIT(8)
#define BIT_RX_BD_AVAI_INT							BIT(9)
#define BIT_HOST_WAKE_CPU_INT						BIT(10)

// Register REG_SPDIO_CPU_IND
#define BIT_SYSTEM_TRX_RDY_IND						BIT(0)

// Register REG_SPDIO_HCI_RX_REQ
#define BIT_HCI_RX_REQ								BIT(0)

/* Register for SOC_HCI_COM_FUN_EN */
#define BIT_SOC_HCI_SDIOD_OFF_EN					BIT(1)		// SDIO Function Block on Power_Off domain
#define BIT_SOC_HCI_SDIOD_ON_EN						BIT(0)		// SDIO Function Block on Power_On domain

/* Register REG_PESOC_HCI_CLK_CTRL0 */
#define BIT_SOC_SLPCK_SDIO_HST_EN					BIT(3)		// SDIO_HST clock enable when CPU sleep command
#define BIT_SOC_ACTCK_SDIO_HST_EN					BIT(2)		// SDIO_HST clock enable in CPU run mode
#define BIT_SOC_SLPCK_SDIO_DEV_EN					BIT(1)		// SDIO_DEV clock enable when CPU sleep command
#define BIT_SOC_ACTCK_SDIO_DEV_EN					BIT(0)		// SDIO_DEV clock enable in CPU run mode

/***** Structer for each Register *****/
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
// Little Endian
// Register REG_SPDIO_HCI_RX_REQ @ 0xBA
typedef struct _SPDIO_HCI_RX_REQ
{
  u8 HCI_RX_REQ :1; /* bit[0], CPU trigger this bit to enable SDIO IP RX transfer by fetch BD info */
  u8 Reserved :7; /* bit[7:1], Reserved */
} SPDIO_HCI_RX_REQ, *PSPDIO_HCI_RX_REQ;

// Register REG_SPDIO_CPU_RST_DMA @ 0xBB
typedef struct _SPDIO_CPU_RST_DMA
{
  u8 Reserved :7; /* bit[6:0], Reserved */
  u8 CPU_RST_SDIO :1; /* bit[7], CPU set this bit to reset SDIO DMA */
} SPDIO_CPU_RST_DMA, *PSPDIO_CPU_RST_DMA;

// Register REG_SPDIO_CPU_INT_MASK @ 0xC0
typedef struct _SPDIO_CPU_INT_MASK
{
  u16 TXFIFO_H2C_OVF :1; /* bit[0], set 0 to mask TXFIFO_H2C_OVF_INT */
  u16 H2C_BUS_RES_FAIL :1; /* bit[1], set 0 to mask H2C_BUS_RES_FAIL_INT */
  u16 H2C_DMA_OK :1; /* bit[2], set 0 to mask H2C_DMA_OK_INT */
  u16 C2H_DMA_OK :1; /* bit[3], set 0 to mask C2H_DMA_OK_INT */
  u16 H2C_MSG_INT :1; /* bit[4], set 0 to mask H2C_MSG_INT_INT */
  u16 RPWM_INT :1; /* bit[5], set 0 to mask RPWM_INT */
  u16 RPWM2_INT :1; /* bit[6], set 0 to mask RPWM2_INT */
  u16 SDIO_RST_CMD_INT :1; /* bit[7], set 0 to mask SDIO_RST_CMD_INT */
  u16 BD_FLAG_ERR_INT :1; /* bit[8], set 0 to mask BD_FLAG_ERR_INT */
  u16 Reserved :7; /* bit[15:9], Reserved */
} SPDIO_CPU_INT_MASK, *PSPDIO_CPU_INT_MASK;

// Register REG_SPDIO_CPU_INT_STATUS @ 0xC2
typedef struct _SPDIO_CPU_INT_STAS
{
  u16 TXFIFO_H2C_OVF :1; /* bit[0], set 0 to mask TXFIFO_H2C_OVF_INT */
  u16 H2C_BUS_RES_FAIL :1; /* bit[1], set 0 to mask H2C_BUS_RES_FAIL_INT */
  u16 H2C_DMA_OK :1; /* bit[2], set 0 to mask H2C_DMA_OK_INT */
  u16 C2H_DMA_OK :1; /* bit[3], set 0 to mask C2H_DMA_OK_INT */
  u16 H2C_MSG_INT :1; /* bit[4], set 0 to mask H2C_MSG_INT_INT */
  u16 RPWM_INT :1; /* bit[5], set 0 to mask RPWM_INT */
  u16 RPWM2_INT :1; /* bit[6], set 0 to mask RPWM2_INT */
  u16 SDIO_RST_CMD_INT :1; /* bit[7], set 0 to mask SDIO_RST_CMD_INT */
  u16 BD_FLAG_ERR_INT :1; /* bit[8], set 0 to mask BD_FLAG_ERR_INT */
  u16 Reserved :7; /* bit[15:9], Reserved */
} SPDIO_CPU_INT_STAS, *PSPDIO_CPU_INT_STAS;

// Register REG_SPDIO_CCPWM @ 0xC4
typedef struct _SPDIO_CCPWM
{
  u8 :1; /* bit[0] */
  u8 WLAN_TRX :1; /* bit[1], 0: WLAN Off; 1: WLAN On */
  u8 RPS_ST :1; /* bit[2], 0/1: AP Register Sleep/Active state */
  u8 WWLAN :1; /* bit[3], 0/1: "Wake on WLAN"/"Normal" state */
  u8 Reserved :3; /* bit[6:4], Reserved */
  u8 TOGGLING :1; /* bit[7], issue interrupt when 0->1 or 1->0 */
} SPDIO_CCPWM, *PSPDIO_CCPWM;

// Register REG_SPDIO_CPU_IND @ 0xC5
typedef struct _SPDIO_CPU_IND
{
  u8 SYS_TRX_RDY :1; /* bit[0], To indicate the Host system that CPU is ready for TRX
   , to be sync to 0x87[0] */
  u8 Reserved :7; /* bit[7:1], Reserved */
} SPDIO_CPU_IND, *PSPDIO_CPU_IND;

// Register REG_SPDIO_CPU_H2C_MSG @ 0xC8
typedef struct _SPDIO_CPU_H2C_MSG
{
  u32 CPU_H2C_MSG :30; /* bit[30:0], Host CPU to FW message, sync from REG_SDIO_H2C_MSG */
  u32 Reserved :1; /* bit[31], Reserved */
} SPDIO_CPU_H2C_MSG, *PSPDIO_CPU_H2C_MSG;

// Register REG_SPDIO_CPU_C2H_MSG @ 0xCC
typedef struct _SPDIO_CPU_C2H_MSG
{
  u32 CPU_C2H_MSG :30; /* bit[30:0], FW to Host CPU message, sync to REG_SDIO_C2H_MSG */
  u32 Reserved :1; /* bit[31], Reserved */
} SPDIO_CPU_C2H_MSG, *PSPDIO_CPU_C2H_MSG;

// Register REG_SPDIO_CRPWM @ 0xD0
typedef struct _SPDIO_CRPWM
{
  u8 :1; /* bit[0] */
  u8 WLAN_TRX :1; /* bit[1], 0: WLAN Off; 1: WLAN On */
  u8 RPS_ST :1; /* bit[2], 0/1: AP Register Sleep/Active state */
  u8 WWLAN :1; /* bit[3], 0/1: "Wake on WLAN"/"Normal" state */
  u8 Reserved :3; /* bit[6:4], Reserved */
  u8 TOGGLING :1; /* bit[7], issue interrupt when 0->1 or 1->0 */
} SPDIO_CRPWM, *PSPDIO_CRPWM;

// Register REG_SPDIO_AHB_DMA_CTRL @ 0xD4
typedef struct _SPDIO_AHB_DMA_CTRL
{
  u32 TXFF_WLEVEL :7; /* bit[6:0], SPDIO TX FIFO water level */
  u32 :1; /* bit[7] */
  u32 RXFF_WLEVEL :7; /* bit[14:8], SPDIO RX FIFO water level */
  u32 :1; /* bit[15] */
  u32 AHB_DMA_CS :4; /* bit[19:16], AHB DMA state */
  u32 :1; /* bit[20] */
  u32 AHB_MASTER_RDY :1; /* bit[21], AHB Master Hready signal */
  u32 AHB_DMA_TRANS :2; /* bit[23:22], AHB DMA Trans value, for debugging */
  u32 AHB_BUSY_WAIT_CNT :4; /* bit[27:24], timeout for AHB controller to wait busy */
  u32 AHB_BURST_TYPE :3; /* bit[30:28], AHB burst type */
  u32 DISPATCH_TXAGG :1; /* bit[31], Enable to dispatch aggregated TX packet */
} SPDIO_AHB_DMA_CTRL, *PSPDIO_AHB_DMA_CTRL;

#else	/* else of '#if LITTLE_ENDIAN' */
// Big Endian
typedef struct _SPDIO_HCI_RX_REQ
{
  u8 Reserved:7; /* bit[7:1], Reserved */
  u8 HCI_RX_REQ:1; /* bit[0], CPU trigger this bit to enable SDIO IP RX transfer by fetch BD info */
}SPDIO_HCI_RX_REQ, *PSPDIO_HCI_RX_REQ;

// Register REG_SPDIO_CPU_RST_DMA @ 0xBB
typedef struct _SPDIO_CPU_RST_DMA
{
  u8 CPU_RST_SDIO:1; /* bit[7], CPU set this bit to reset SDIO DMA */
  u8 Reserved:7; /* bit[6:0], Reserved */
}SPDIO_CPU_RST_DMA, *PSPDIO_CPU_RST_DMA;

// Register REG_SPDIO_CPU_INT_MASK @ 0xC0
typedef struct _SPDIO_CPU_INT_MASK
{
  u16 Reserved:7; /* bit[15:9], Reserved */
  u16 BD_FLAG_ERR_INT:1; /* bit[8], set 0 to mask BD_FLAG_ERR_INT */
  u16 SDIO_RST_CMD_INT:1; /* bit[7], set 0 to mask SDIO_RST_CMD_INT */
  u16 RPWM2_INT:1; /* bit[6], set 0 to mask RPWM2_INT */
  u16 RPWM_INT:1; /* bit[5], set 0 to mask RPWM_INT */
  u16 H2C_MSG_INT:1; /* bit[4], set 0 to mask H2C_MSG_INT_INT */
  u16 C2H_DMA_OK:1; /* bit[3], set 0 to mask C2H_DMA_OK_INT */
  u16 H2C_DMA_OK:1; /* bit[2], set 0 to mask H2C_DMA_OK_INT */
  u16 H2C_BUS_RES_FAIL:1; /* bit[1], set 0 to mask H2C_BUS_RES_FAIL_INT */
  u16 TXFIFO_H2C_OVF:1; /* bit[0], set 0 to mask TXFIFO_H2C_OVF_INT */
}SPDIO_CPU_INT_MASK, *PSPDIO_CPU_INT_MASK;

// Register REG_SPDIO_CPU_INT_STAS @ 0xC2
typedef struct _SPDIO_CPU_INT_STAS
{
  u16 Reserved:7; /* bit[15:9], Reserved */
  u16 BD_FLAG_ERR_INT:1; /* bit[8], set 0 to mask BD_FLAG_ERR_INT */
  u16 SDIO_RST_CMD_INT:1; /* bit[7], set 0 to mask SDIO_RST_CMD_INT */
  u16 RPWM2_INT:1; /* bit[6], set 0 to mask RPWM2_INT */
  u16 RPWM_INT:1; /* bit[5], set 0 to mask RPWM_INT */
  u16 H2C_MSG_INT:1; /* bit[4], set 0 to mask H2C_MSG_INT_INT */
  u16 C2H_DMA_OK:1; /* bit[3], set 0 to mask C2H_DMA_OK_INT */
  u16 H2C_DMA_OK:1; /* bit[2], set 0 to mask H2C_DMA_OK_INT */
  u16 H2C_BUS_RES_FAIL:1; /* bit[1], set 0 to mask H2C_BUS_RES_FAIL_INT */
  u16 TXFIFO_H2C_OVF:1; /* bit[0], set 0 to mask TXFIFO_H2C_OVF_INT */
}SPDIO_CPU_INT_STAS, *PSPDIO_CPU_INT_STAS;

// Register REG_SPDIO_CCPWM @ 0xC4
typedef struct _SPDIO_CCPWM
{
  u8 TOGGLING:1; /* bit[7], issue interrupt when 0->1 or 1->0 */
  u8 Reserved:3; /* bit[6:4], Reserved */
  u8 WWLAN:1; /* bit[3], 0/1: "Wake on WLAN"/"Normal" state */
  u8 RPS_ST:1; /* bit[2], 0/1: AP Register Sleep/Active state */
  u8 WLAN_TRX:1; /* bit[1], 0: WLAN Off; 1: WLAN On */
  u8 :1; /* bit[0] */
}SPDIO_CCPWM, *PSPDIO_CCPWM;

// Register REG_SPDIO_CPU_IND @ 0xC5
typedef struct _SPDIO_CPU_IND
{
  u8 Reserved:7; /* bit[7:1], Reserved */
  u8 SYS_TRX_RDY:1; /* bit[0], To indicate the Host system that CPU is ready for TRX
   , to be sync to 0x87[0] */
}SPDIO_CPU_IND, *PSPDIO_CPU_IND;

// Register REG_SPDIO_CPU_H2C_MSG @ 0xC8
typedef struct _SPDIO_CPU_H2C_MSG
{
  u32 Reserved:1; /* bit[31], Reserved */
  u32 CPU_H2C_MSG:30; /* bit[30:0], Host CPU to FW message */
}SPDIO_CPU_H2C_MSG, *PSPDIO_CPU_H2C_MSG;

// Register REG_SPDIO_CPU_C2H_MSG @ 0xCC
typedef struct _SPDIO_CPU_C2H_MSG
{
  u32 Reserved:1; /* bit[31], Reserved */
  u32 CPU_C2H_MSG:30; /* bit[30:0], FW to Host CPU message, sync to REG_SDIO_C2H_MSG */
}SPDIO_CPU_C2H_MSG, *PSPDIO_CPU_C2H_MSG;

// Register REG_SPDIO_CRPWM @ 0xD0
typedef struct _SPDIO_CRPWM
{
  u8 TOGGLING:1; /* bit[7], issue interrupt when 0->1 or 1->0 */
  u8 Reserved:3; /* bit[6:4], Reserved */
  u8 WWLAN:1; /* bit[3], 0/1: "Wake on WLAN"/"Normal" state */
  u8 RPS_ST:1; /* bit[2], 0/1: AP Register Sleep/Active state */
  u8 WLAN_TRX:1; /* bit[1], 0: WLAN Off; 1: WLAN On */
  u8 :1; /* bit[0] */
}SPDIO_CRPWM, *PSPDIO_CRPWM;

// Register REG_SPDIO_AHB_DMA_CTRL @ 0xD4
typedef struct _SPDIO_AHB_DMA_CTRL
{
  u32 DISPATCH_TXAGG:1; /* bit[31], Enable to dispatch aggregated TX packet */
  u32 AHB_BURST_TYPE:3; /* bit[30:28], AHB burst type */
  u32 AHB_BUSY_WAIT_CNT:4; /* bit[27:24], timeout for AHB controller to wait busy */
  u32 AHB_DMA_TRANS:2; /* bit[23:22], AHB DMA Trans value, for debugging */
  u32 AHB_MASTER_RDY:1; /* bit[21], AHB Master Hready signal */
  u32 :1; /* bit[20] */
  u32 AHB_DMA_CS:4; /* bit[19:16], AHB DMA state */
  u32 :1; /* bit[15] */
  u32 RXFF_WLEVEL:7; /* bit[14:8], SPDIO RX FIFO water level */
  u32 :1; /* bit[7] */
  u32 TXFF_WLEVEL:7; /* bit[6:0], SPDIO TX FIFO water level */
}SPDIO_AHB_DMA_CTRL, *PSPDIO_AHB_DMA_CTRL;

#endif	/* end of '#if LITTLE_ENDIAN' */

//#define TX_FIFO_ADDR								0x0000
//#define TX_FIFO_SIZE								0x8000

//TX BD setting
#if SDIO_BOOT_DRIVER
// for build ROM library
#define SDIO_TX_BD_NUM								2	// Number of TX BD
#define SDIO_TX_BD_BUF_SIZE							(2048+32)    // the size of a TX BD pointed buffer, WLan header = 26 bytes
#define SDIO_TX_PKT_NUM								10	// Number of TX packet handler

//RX BD setting
#define RX_BD_FREE_TH								4   // trigger the interrupt when free RX BD over this threshold

#define MAX_RX_BD_BUF_SIZE			                16380	// the Maximum size for a RX_BD point to, make it 4-bytes aligned

#define SDIO_RX_PKT_NUM								3	// Number of RX packet handler
//#define SDIO_RX_BD_NUM								10	// Number of RX BD, to make 32K of bus aggregation, it needs 22 RX_BD at least
#define SDIO_RX_BD_NUM								(SDIO_RX_PKT_NUM*2)	// Number of RX BD, to make 32K of bus aggregation, it needs 22 RX_BD at least
#define SDIO_RX_BD_BUF_SIZE							(2048+24)    // the size of a RX BD pointed buffer, sizeof(RX Desc)  = 26 bytes
#define MIN_RX_BD_SEND_PKT							2	/* the minum needed RX_BD to send a Packet to Host, we need 2:
															one for RX_Desc, the other for payload */

// CCPWM2 bit map definition for Firmware download
#define SDIO_INIT_DONE                               (BIT0)
#define SDIO_MEM_WR_DONE                            (BIT1)
#define SDIO_MEM_RD_DONE                            (BIT2)
#define SDIO_MEM_ST_DONE                            (BIT3)

#define SDIO_CPWM2_TOGGLE                           (BIT15)

#else
#if CONFIG_INIC_EN
//TX BD setting
#define SDIO_TX_BD_NUM								20	// Number of TX BD
#define SDIO_TX_BD_BUF_SIZE							1540    //1514+24
//#define SDIO_TX_PKT_NUM								1	// not used

//RX BD setting
#define RX_BD_FREE_TH								5   // trigger the interrupt when free RX BD over this threshold
#define SDIO_RX_BD_BUF_SIZE							1540 //1514+24
#define MAX_RX_BD_BUF_SIZE			                16380	// the Maximum size for a RX_BD point to, make it 4-bytes aligned
#define SDIO_RX_BD_NUM								32	// Number of RX BD, to make 32K of bus aggregation, it needs 22 RX_BD at least
#define SDIO_RX_PKT_NUM								128	// Number of RX packet handler
#define MIN_RX_BD_SEND_PKT							2	/* the minum needed RX_BD to send a Packet to Host, we need 2:
											one for RX_Desc, the other for payload */

#else
#define SDIO_TX_BD_NUM								24	// Number of TX BD
#define SDIO_TX_BD_BUF_SIZE							(2048+32)    // the size of a TX BD pointed buffer, WLan header = 26 bytes
#define SDIO_TX_PKT_NUM								128	// Number of TX packet handler

//RX BD setting
#define RX_BD_FREE_TH								5   // trigger the interrupt when free RX BD over this threshold

#define SDIO_RX_BD_BUF_SIZE							2048
#define MAX_RX_BD_BUF_SIZE			                16380	// the Maximum size for a RX_BD point to, make it 4-bytes aligned

//#define SDIO_TX_FIFO_SIZE							(1024*64)	// 64K
#define SDIO_RX_BD_NUM								24	// Number of RX BD, to make 32K of bus aggregation, it needs 22 RX_BD at least
#define SDIO_RX_PKT_NUM								128	// Number of RX packet handler
#define MIN_RX_BD_SEND_PKT							2	/* the minum needed RX_BD to send a Packet to Host, we need 2:
															one for RX_Desc, the other for payload */
#endif
#endif

#define SDIO_IRQ_PRIORITY							10

/* SDIO Events */
#define SDIO_EVENT_IRQ								BIT(0)		// Interrupt triggered
#define SDIO_EVENT_RX_PKT_RDY						BIT(1)		// A new SDIO packet ready
#define SDIO_EVENT_C2H_DMA_DONE						BIT(2)		// Interrupt of C2H DMA done triggered
#define SDIO_EVENT_DUMP                             BIT(3)      // SDIO status dump periodically Enable
#define SDIO_EVENT_TXBD_REFILL                      BIT(4)      // To refill TX BD buffer
#define SDIO_EVENT_EXIT								BIT(28)		// Request to exit the SDIO task
#define SDIO_EVENT_MP_STOPPED						BIT(29)		// The SDIO task is stopped
#define SDIO_EVENT_TX_STOPPED						BIT(30)		// The SDIO task is stopped
#define SDIO_EVENT_RX_STOPPED						BIT(31)		// The SDIO task is stopped

#define SDIO_TASK_PRIORITY							1	// it can be 0(lowest) ~ configMAX_PRIORITIES-1(highest)
#define SDIO_MP_TASK_PRIORITY                       2	// it can be 0(lowest) ~ configMAX_PRIORITIES-1(highest)
//#if SDIO_TASK_PRIORITY > (configMAX_PRIORITIES - 1)
#if SDIO_TASK_PRIORITY > (4 - 1)
#error "SDIO Task Priority Should be 0~(configMAX_PRIORITIES-1)"
#endif

//#define TX_RX_PACKET_SIZE							0x144

typedef struct _SDIO_TX_BD_
{
  u32 Address; /* The TX buffer physical address, it must be 4-bytes aligned */
} SDIO_TX_BD, *PSDIO_TX_BD;

#define TX_BD_STRUCTURE_SIZE	(sizeof(SDIO_TX_BD))

/* The RX Buffer Descriptor format */

#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
typedef struct _SDIO_RX_BD_
{
  u32 BuffSize :14; /* bit[13:0], RX Buffer Size, Maximum 16384-1 */
  u32 LS :1; /* bit[14], is the Last Segment ? */
  u32 FS :1; /* bit[15], is the First Segment ? */
  u32 Seq :16; /* bit[31:16], The sequence number, it's no use for now */
  u32 PhyAddr; /* The RX buffer physical address, it must be 4-bytes aligned */
} SDIO_RX_BD, *PSDIO_RX_BD;
#else
typedef struct _SDIO_RX_BD_
{
  u32 Seq:16; /* bit[31:16], The sequence number, be used for ?? */
  u32 FS:1; /* bit[15], is the First Segment ? */
  u32 LS:1; /* bit[14], is the Last Segment ? */
  u32 BuffSize:14; /* bit[13:0], RX Buffer Size, Maximum 16384 */
  u32 PhyAddr; /* The RX buffer physical address, it must be 4-bytes aligned */
}SDIO_RX_BD, *PSDIO_RX_BD;
#endif
#define RX_BD_STRUCTURE_SIZE	(sizeof(SDIO_RX_BD))

// TODO: This data structer just for test, we should modify it for the normal driver
typedef struct _SDIO_TX_DESC
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;    		// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;		// bit[31:24], the bus aggregation number
#else
  u32 bus_agg_num:8;      // bit[31:24], the bus aggregation number
  u32 offset:8;// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 txpktsize:16;// bit[15:0]
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;             // bit[7:0], the packet type
  u32 rsvd0 :24;
#else
  u32 rsvd0:24;
  u32 type:8;             // bit[7:0], the packet type
#endif

  // u4Byte 2
  u32 rsvd1;

  // u4Byte 3
  u32 rsvd2;

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_TX_DESC, *PSDIO_TX_DESC;

// TX Desc for Memory Write command
typedef struct _SDIO_TX_DESC_MW
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;    		// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;		// bit[31:24], the bus aggregation number
#else
  u32 bus_agg_num:8;      // bit[31:24], the bus aggregation number
  u32 offset:8;// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 txpktsize:16;// bit[15:0]
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;             // bit[7:0], the packet type
  u32 reply :1;            // bit[8], request to send a reply message
  u32 rsvd0 :23;
#else
  u32 rsvd0:23;
  u32 reply:1;            // bit[8], request to send a reply message
  u32 type:8;// bit[7:0], the packet type
#endif

  // u4Byte 2
  u32 start_addr;         // memory write start address

  // u4Byte 3
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 write_len :16;       // bit[15:0], the length to write
  u32 rsvd2 :16;           // bit[31:16]
#else
  u32 rsvd2:16;           // bit[31:16]
  u32 write_len:16;// bit[15:0], the length to write
#endif

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_TX_DESC_MW, *PSDIO_TX_DESC_MW;

// TX Desc for Memory Read command
typedef struct _SDIO_TX_DESC_MR
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;    		// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;		// bit[31:24], the bus aggregation number
#else
  u32 bus_agg_num:8;      // bit[31:24], the bus aggregation number
  u32 offset:8;// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 txpktsize:16;// bit[15:0]
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;             // bit[7:0], the packet type
  u32 rsvd0 :24;
#else
  u32 rsvd0:24;
  u32 type:8;             // bit[7:0], the packet type
#endif

  // u4Byte 2
  u32 start_addr;         // memory write start address

  // u4Byte 3
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 read_len :16;        // bit[15:0], the length to read
  u32 rsvd2 :16;           // bit[31:16]
#else
  u32 rsvd2:16;           // bit[31:16]
  u32 read_len:16;// bit[15:0], the length to read
#endif

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_TX_DESC_MR, *PSDIO_TX_DESC_MR;

// TX Desc for Memory Set command
typedef struct _SDIO_TX_DESC_MS
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;    		// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;		// bit[31:24], the bus aggregation number
#else
  u32 bus_agg_num:8;      // bit[31:24], the bus aggregation number
  u32 offset:8;// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 txpktsize:16;// bit[15:0]
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;             // bit[7:0], the packet type
  u32 data :8;             // bit[8:15], the value to be written to the memory
  u32 reply :1;            // bit[16], request to send a reply message
  u32 rsvd0 :15;
#else
  u32 rsvd0:15;
  u32 reply:1;            // bit[16], request to send a reply message
  u32 data:8;// bit[8:15], the value to be written to the memory
  u32 type:8;// bit[7:0], the packet type
#endif

  // u4Byte 2
  u32 start_addr;         // memory write start address

  // u4Byte 3
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 write_len :16;       // bit[15:0], the length to write
  u32 rsvd2 :16;           // bit[31:16]
#else
  u32 rsvd2:16;           // bit[31:16]
  u32 write_len:16;// bit[15:0], the length to write
#endif

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_TX_DESC_MS, *PSDIO_TX_DESC_MS;

// TX Desc for Jump to Start command
typedef struct _SDIO_TX_DESC_JS
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;    		// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;		// bit[31:24], the bus aggregation number
#else
  u32 bus_agg_num:8;      // bit[31:24], the bus aggregation number
  u32 offset:8;// bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 txpktsize:16;// bit[15:0]
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;             // bit[7:0], the packet type
  u32 rsvd0 :24;
#else
  u32 rsvd0:24;
  u32 type:8;             // bit[7:0], the packet type
#endif

  // u4Byte 2
  u32 start_fun;         // the pointer of the startup function

  // u4Byte 3
  u32 rsvd2;

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_TX_DESC_JS, *PSDIO_TX_DESC_JS;

#define SIZE_TX_DESC	(sizeof(SDIO_TX_DESC))
// define the TX BD buffer size with unite of 64 byets
/* Be carefull!! the setting of hardware's TX BD buffer size may exceed the real size of
 the TX BD buffer size, and then it may cause the hardware DMA write the buffer overflow */
#define SDIO_TX_BUF_SZ_UNIT          64
#define SDIO_TX_BD_BUF_USIZE        ((((SDIO_TX_BD_BUF_SIZE+sizeof(SDIO_TX_DESC)-1)/SDIO_TX_BUF_SZ_UNIT)+1)&0xff)

typedef struct _SDIO_TX_BD_BUFFER_
{
  SDIO_TX_DESC TX_Desc;
  u8 TX_Buffer[ SDIO_TX_BD_BUF_SIZE ];
} SDIO_TX_BD_BUFFER, *PSDIO_TX_BD_BUFFER;

// TODO: This data structer just for test, we should modify it for the normal driver
typedef struct _SDIO_RX_DESC
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 pkt_len :16;     // bit[15:0], the packet size
  u32 offset :8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 rsvd0 :6;        // bit[29:24]
  u32 icv :1;          // bit[30], ICV error
  u32 crc :1;          // bit[31], CRC error
#else
  u32 crc:1;          // bit[31], CRC error
  u32 icv:1;// bit[30], ICV error
  u32 rsvd0:6;// bit[29:24]
  u32 offset:8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 pkt_len:16;// bit[15:0], the packet size
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;         // bit[7:0], the type of this packet
  u32 rsvd1 :24;       // bit[31:8]
#else
  u32 rsvd1:24;       // bit[31:8]
  u32 type:8;// bit[7:0], the type of this packet
#endif

  // u4Byte 2
  u32 rsvd2;

  // u4Byte 3
  u32 rsvd3;

  // u4Byte 4
  u32 rsvd4;

  // u4Byte 5
  u32 rsvd5;
} SDIO_RX_DESC, *PSDIO_RX_DESC;

// For memory read command
typedef struct _SDIO_RX_DESC_MR
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 pkt_len :16;     // bit[15:0], the packet size
  u32 offset :8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 rsvd0 :8;        // bit[31:24]
#else
  u32 rsvd0:8;        // bit[31:24]
  u32 offset:8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 pkt_len:16;// bit[15:0], the packet size
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;         // bit[7:0], the type of this packet
  u32 rsvd1 :24;       // bit[31:8]
#else
  u32 rsvd1:24;       // bit[31:8]
  u32 type:8;// bit[7:0], the type of this packet
#endif

  // u4Byte 2
  u32 start_addr;

  // u4Byte 3
  u32 rsvd2;

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_RX_DESC_MR, *PSDIO_RX_DESC_MR;

// For memory write reply command
typedef struct _SDIO_RX_DESC_MW
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 pkt_len :16;     // bit[15:0], the packet size
  u32 offset :8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 rsvd0 :8;        // bit[31:24]
#else
  u32 rsvd0:8;        // bit[31:24]
  u32 offset:8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 pkt_len:16;// bit[15:0], the packet size
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;         // bit[7:0], the type of this packet
  u32 rsvd1 :24;       // bit[31:8]
#else
  u32 rsvd1:24;       // bit[31:8]
  u32 type:8;// bit[7:0], the type of this packet
#endif

  // u4Byte 2
  u32 start_addr;

  // u4Byte 3
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 write_len :16;   // bit[15:0], the type of this packet
  u32 result :8;      // bit[23:16], the result of memory write command
  u32 rsvd2 :8;       // bit[31:24]
#else
  u32 rsvd2:8;       // bit[31:24]
  u32 result:8;// bit[23:16], the result of memory write command
  u32 write_len:16;// bit[15:0], the type of this packet
#endif

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_RX_DESC_MW, *PSDIO_RX_DESC_MW;

// For memory set reply command
typedef struct _SDIO_RX_DESC_MS
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 pkt_len :16;     // bit[15:0], the packet size
  u32 offset :8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 rsvd0 :8;        // bit[31:24]
#else
  u32 rsvd0:8;        // bit[31:24]
  u32 offset:8;// bit[23:16], the offset from the packet start to the buf start, also means the size of RX Desc
  u32 pkt_len:16;// bit[15:0], the packet size
#endif

  // u4Byte 1
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 type :8;         // bit[7:0], the type of this packet
  u32 rsvd1 :24;       // bit[31:8]
#else
  u32 rsvd1:24;       // bit[31:8]
  u32 type:8;// bit[7:0], the type of this packet
#endif

  // u4Byte 2
  u32 start_addr;

  // u4Byte 3
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 write_len :16;   // bit[15:0], the type of this packet
  u32 result :8;      // bit[23:16], the result of memory write command
  u32 rsvd2 :8;       // bit[31:24]
#else
  u32 rsvd2:8;       // bit[31:24]
  u32 result:8;// bit[23:16], the result of memory write command
  u32 write_len:16;// bit[15:0], the type of this packet
#endif

  // u4Byte 4
  u32 rsvd3;

  // u4Byte 5
  u32 rsvd4;
} SDIO_RX_DESC_MS, *PSDIO_RX_DESC_MS;

#define SIZE_RX_DESC	(sizeof(SDIO_RX_DESC))

typedef struct _SDIO_RX_BD_BUFFER_
{
  SDIO_RX_DESC RX_Desc;
  u8 RX_Buffer[ SDIO_RX_BD_BUF_SIZE ];
} SDIO_RX_BD_BUFFER, *PSDIO_RX_BD_BUFFER;

/* The data structer for a packet fordwarding to the WLan driver to transmit it */
// TODO: This data structer just for test, we may need modify it for the normal driver
typedef struct _SDIO_TX_PACKET_
{
  u8 *pHeader;		// Point to the 1st byte of the packets
  u16 PktSize;		// the size (bytes) of this packet
  _LIST list;			// the link list to chain packets
  u8 isDyna;          // is Dynamic allocated
} SDIO_TX_PACKET, *PSDIO_TX_PACKET;

/* the data structer to bind a TX_BD with a TX Packet */
typedef struct _SDIO_TX_BD_HANDLE_
{
  SDIO_TX_BD *pTXBD;		// Point to the TX_BD buffer
#if SDIO_API_DEFINED
  VOID *priv;
#else
#if CONFIG_INIC_EN
#if CONFIG_INIC_SKB_TX
  struct sk_buff *skb;
#endif
#endif
#endif
  SDIO_TX_PACKET *pPkt;	// point to the Tx Packet
  u8 isPktEnd;		// For a packet over 1 BD , this flag to indicate is this BD contains a packet end
  u8 isFree;		// is this TX BD free
} SDIO_TX_BD_HANDLE, *PSDIO_TX_BD_HANDLE;

/* The data structer for a packet which from the WLan driver to send to the Host */
// TODO: This data structer just for test, we may need modify it for the normal driver
#if SDIO_BOOT_DRIVER
typedef struct _SDIO_RX_PACKET_
{
//	SDIO_RX_DESC RxDesc;	// The RX Descriptor for this packet, to be send to Host ahead this packet
  u8 *pData;// point to the head of payload of this packet
  u16 Offset;// the offset from the pData to the payload buffer
  _LIST list;// the link list to chain packets
  u8 PktBuf[SDIO_RX_BD_BUF_SIZE];// the Rx_Desc + payload data buffer, the first 24 bytes is reserved for RX_DESC
}SDIO_RX_PACKET, *PSDIO_RX_PACKET;
#else
typedef struct _SDIO_RX_PACKET_
{
  SDIO_RX_DESC RxDesc;	// The RX Descriptor for this packet, to be send to Host ahead this packet
#if SDIO_API_DEFINED
  VOID *priv;
#else
#if CONFIG_INIC_EN
#if CONFIG_INIC_SKB_RX
  struct sk_buff *skb;
#endif
#endif
#endif
  u8 *pData;				// point to the head of payload of this packet
  u16 Offset;         // the offset from the pData to the payload buffer
  _LIST list;			// the link list to chain packets
  u8 isDyna;          // is Dynamic allocated
} SDIO_RX_PACKET, *PSDIO_RX_PACKET;
#endif

/* the data structer to bind a RX_BD with a RX Packet */
typedef struct _SDIO_RX_BD_HANDLE_
{
  SDIO_RX_BD *pRXBD;		// Point to the RX_BD buffer
  SDIO_RX_PACKET *pPkt;	// point to the Rx Packet
  u8 isPktEnd;		// For a packet over 1 BD , this flag to indicate is this BD contains a packet end
  u8 isFree;		// is this RX BD free (DMA done and its RX packet has been freed)
} SDIO_RX_BD_HANDLE, *PSDIO_RX_BD_HANDLE;

#if SDIO_MP_MODE
typedef struct _SDIO_MP_CMD_
{
  u8 cmd_name[16];
  u32 cmd_type;
}SDIO_MP_CMD, *PSDIO_MP_CMD;

typedef enum _SDIO_MP_CMD_TYPE_
{
  SDIO_MP_START=1,
  SDIO_MP_STOP=2,
  SDIO_MP_LOOPBACK=3,
  SDIO_MP_STATUS=4,
  SDIO_MP_READ_REG8=5,
  SDIO_MP_READ_REG16=6,
  SDIO_MP_READ_REG32=7,
  SDIO_MP_WRITE_REG8=8,
  SDIO_MP_WRITE_REG16=9,
  SDIO_MP_WRITE_REG32=10,
  SDIO_MP_WAKEUP=11,	// wakeup the SDIO task manually, for debugging
  SDIO_MP_DUMP=12,// start/stop to dump the SDIO status periodically
  SDIO_MP_CTX=13,// setup continue TX test
  SDIO_MP_CRX=14,// setup continue RX test
  SDIO_MP_CRX_DA=15,// setup continue RX with dynamic allocate RX Buf test
  SDIO_MP_CRX_STOP=16,// setup continue RX test
  SDIO_MP_DBG_MSG=17,// Debug message On/Off

}SDIO_MP_CMD_TYPE;

typedef enum _SDIO_CRX_MODE_
{
  SDIO_CRX_STATIC_BUF = 1,
  SDIO_CRX_DYNA_BUF = 2,
}SDIO_CRX_MODE;

typedef struct _SDIO_MP_RX_PACKET_
{
  _LIST list;         // this member MUST be the 1st one, the link list to chain packets
  u8 *pData;// point to the head of payload of this packet
  u16 Offset;// the offset from the pData to the payload
  u16 DataLen;// the data length of this packet
}SDIO_MP_RX_PACKET, *PSDIO_MP_RX_PACKET;

#endif	// end of '#if SDIO_MP_MODE'

#define SDIO_CMD_TX_ETH         0x83    // request to TX a 802.3 packet
#define SDIO_CMD_TX_WLN         0x81    // request to TX a 802.11 packet
#define SDIO_CMD_H2C            0x11    // H2C(host to device) command packet
#define SDIO_CMD_MEMRD          0x51    // request to read a block of memory data
#define SDIO_CMD_MEMWR          0x53    // request to write a block of memory
#define SDIO_CMD_MEMST          0x55    // request to set a block of memory with a value
#define SDIO_CMD_STARTUP        0x61    // request to jump to the start up function

#define SDIO_CMD_RX_ETH         0x82    // indicate a RX 802.3 packet
#define SDIO_CMD_RX_WLN         0x80    // indicate a RX 802.11 packet
#define SDIO_CMD_C2H            0x10    // C2H(device to host) command packet
#define SDIO_CMD_MEMRD_RSP      0x50    // response to memory block read command
#define SDIO_CMD_MEMWR_RSP      0x52    // response to memory write command
#define SDIO_CMD_MEMST_RSP      0x54    // response to memory set command
#define SDIO_CMD_STARTED        0x60    // indicate the program has jumped to the given function

enum SDIO_RPWM2_BITS
{
  RPWM2_ACT_BIT = BIT0,     // Active
  RPWM2_SLEEP_BIT = 0,        // Sleep
  RPWM2_DSTANDBY_BIT = BIT1,     // Deep Standby
  RPWM2_PG_BIT = 0,        // Power Gated
  RPWM2_FBOOT_BIT = BIT2,     // fast reboot
  RPWM2_NBOOT_BIT = 0,        // normal reboot
  RPWM2_WKPIN_A5_BIT = BIT3,     // enable GPIO A5 wakeup
  RPWM2_WKPIN_C7_BIT = BIT4,     // enable GPIO C7 wakeup
  RPWM2_WKPIN_D5_BIT = BIT5,     // enable GPIO D5 wakeup
  RPWM2_WKPIN_E3_BIT = BIT6,     // enable GPIO E3 wakeup
  RPWM2_PIN_A5_LV_BIT = BIT7,     // GPIO A5 wakeup level
  RPWM2_PIN_C7_LV_BIT = BIT8,     // GPIO C7 wakeup level
  RPWM2_PIN_D5_LV_BIT = BIT9,     // GPIO D5 wakeup level
  RPWM2_PIN_E3_LV_BIT = BIT10,    // GPIO E3 wakeup level
  RPWM2_CG_BIT = BIT11,    // Clock Gated
  RPWM2_ACK_BIT = BIT14,    // Acknowledge
  RPWM2_TOGGLE_BIT = BIT15,    // Toggle bit
};

enum SDIO_CPWM2_BITS
{
  CPWM2_ACT_BIT = BIT0,     // Active
  CPWM2_DSTANDBY_BIT = BIT1,     // Deep Standby
  CPWM2_FBOOT_BIT = BIT2,     // fast reboot
  CPWM2_INIC_FW_RDY_BIT = BIT3,     // is the iNIC FW(1) or Boot FW(0)

  CPWM2_TOGGLE_BIT = BIT15,    // Toggle bit
};

#ifdef CONFIG_SDIO_DEVICE_VERIFY

#define TX_BD_STRUCTURE_NUM							10
#define RX_BD_STRUCTURE_NUM							10
#define TX_BD_BUFFER_SIZE							0x1000//0x2000//0x800
#define RX_BD_BUFFER_SIZE							0x400//0x800

#define SDIO_RAM_ADDR_BASE							0x20080000
#define SDIO_BUFFER_HEAD(addr)						SDIO_RAM_ADDR_BASE + addr
#define HAL_SDIO_BUFFER_READ8(addr)					HAL_READ8(SDIO_RAM_ADDR_BASE, addr)
#define HAL_SDIO_BUFFER_READ32(addr)				HAL_READ32(SDIO_RAM_ADDR_BASE, addr)
#define HAL_SDIO_BUFFER_WRITE32(addr, value)		HAL_WRITE32(SDIO_RAM_ADDR_BASE, addr, value)

//#define RX_BD_ADDR									0x8000
//#define RX_BUFFER_ADDR								0x8050

typedef enum _SDIO_TEST_FUNC_
{
  SDIO_TEST_INIT,			// 0
  SDIO_TEST_INT_ON,// 1
  SDIO_TEST_INT_OFF,// 2
  SDIO_HCI_RX_REQ,// 3
  SDIO_RESET_TXFIFIO,// 4
  SDIO_CPU_RST_DMA,// 5
  SDIO_CPU_CLR_INT_REG,// 6
  SDIO_TIMER_TEST,// 7
  SDIO_TEST_DEBUG,// 8
  SDIO_TEST,// 9
  SDIO_HELP = 0xff
}SDIO_TEST_FUNC, *PSDIO_TEST_FUNC;

typedef struct _SDIO_TEST_ADAPTER_
{
  u32 TXWritePtr;
  u32 TXReadPtr;
  u16 RXWritePtr;
  u16 RXReadPtr;
  u16 IntMask;
  u16 IntStatus;
}SDIO_TEST_ADAPTER, *PSDIO_TEST_ADAPTER;

VOID
MovePKTToRX(
    IN u32 Source, IN u32 Destination, IN u32 PKTSize
);

BOOL
PacketProcess(
    IN SDIO_TEST_ADAPTER *pDevStatus
);

VOID
SdioDeviceIrqHandleFunc(
    IN VOID *DATA
);

VOID
SdioDeviceTestApp(
    IN u32 Data
);

VOID
InitRXBD(VOID);

VOID
InitTXFIFO(VOID);

VOID
IrqRegister(VOID);

#endif	// end of "#ifdef CONFIG_SDIO_DEVICE_VERIFY"

#if SDIO_API_DEFINED
#include "spdio_api.h"
#endif

#if !SDIO_BOOT_DRIVER
#include "mailbox.h"
#endif
#define PURE_SDIO_INIC           0  // is a pure SDIO iNIC device or a SDIO iNIC + peripheral device

#if SDIO_BOOT_DRIVER
typedef struct _HAL_SDIO_ADAPTER_
{
  u8 *pTXBDAddr; /* The TX_BD start address */
  PSDIO_TX_BD pTXBDAddrAligned; /* The TX_BD start address, it must be 4-bytes aligned */
  PSDIO_TX_BD_HANDLE pTXBDHdl; /* point to the allocated memory for TX_BD Handle array */
  u16 TXBDWPtr; /* The SDIO TX(Host->Device) BD local write index, different with HW maintained write Index. */
  u16 TXBDRPtr; /* The SDIO TX(Host->Device) BD read index */
  u16 TXBDRPtrReg; /* The SDIO TX(Host->Device) BD read index has been write to HW register */
  u16 reserve1;

  u8 *pRXBDAddr; /* The RX_BD start address */
  PSDIO_RX_BD pRXBDAddrAligned; /* The RX_BD start address, it must be 8-bytes aligned */
  PSDIO_RX_BD_HANDLE pRXBDHdl; /* point to the allocated memory for RX_BD Handle array */
  u16 RXBDWPtr; /* The SDIO RX(Device->Host) BD write index */
  u16 RXBDRPtr; /* The SDIO RX(Device->Host) BD local read index, different with HW maintained Read Index. */
  u16 IntMask; /* The Interrupt Mask */
  u16 IntStatus; /* The Interrupt Status */
  u32 Events; /* The Event to the SDIO Task */

  u32 EventSema; /* Semaphore for SDIO events, use to wakeup the SDIO task */
  u8 CCPWM; /* the value write to register CCPWM, which will sync to Host HCPWM */
  u8 reserve2;
  u16 CCPWM2; /* the value write to register CCPWM2, which will sync to Host HCPWM2 */

  s8 (*Tx_Callback)(VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize); /* to hook the WLan driver TX callback function to handle a Packet TX */
  VOID *pTxCb_Adapter; /* a pointer will be used to call the TX Callback function,
   which is from the TX CallBack function register */
  s8 (*pTxCallback_Backup)(VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize);// Use to back up the registered TX Callback function, for MP/Normal mode switch
  VOID *pTxCb_Adapter_Backup;// Backup the pTxCb_Adapter, for MP/Normal mode switch
  _LIST FreeTxPktList; /* The list to queue free Tx packets handler */
  _LIST RxPktList; /* The list to queue RX packets */
  _LIST FreeRxPktList; /* The list to queue free Rx packets handler */
  SDIO_TX_PACKET *pTxPktHandler; /* to store allocated TX Packet handler memory address */
  SDIO_RX_PACKET *pRxPktHandler; /* to store allocated RX Packet handler memory address */
  u32 RxInQCnt; /* The packet count for Rx In Queue */
  u32 MemAllocCnt;		// Memory allocated count, for debug only
  u32 MAllocFailedCnt;// MemAlloc Failed count, for debugging

//	VOID			*pHalOp;			/* point to HAL operation function table */
}HAL_SDIO_ADAPTER, *PHAL_SDIO_ADAPTER;

extern BOOL SDIO_Device_Init_Rom(
    IN PHAL_SDIO_ADAPTER pSDIODev
);
extern VOID SDIO_Device_DeInit_Rom(
    IN PHAL_SDIO_ADAPTER pSDIODev
);
extern VOID SDIO_Send_C2H_IOMsg_Rom(
    IN PHAL_SDIO_ADAPTER pSDIODev,
    IN u32 *C2HMsg
);
extern u8 SDIO_Send_C2H_PktMsg_Rom(
    IN PHAL_SDIO_ADAPTER pSDIODev,
    IN u8 *C2HMsg,
    IN u16 MsgLen
);
extern VOID SDIO_Register_Tx_Callback_Rom(
    IN PHAL_SDIO_ADAPTER pSDIODev,
    IN s8 (*Tx_Callback)(VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize),
    IN VOID *pAdapter
);
extern s8 SDIO_Rx_Callback_Rom(
    IN PHAL_SDIO_ADAPTER pSDIODev,
    IN VOID *pData,
    IN u16 Offset,
    IN u16 Length,
    IN u8 CmdType
);

#else   // else of "#if SDIO_BOOT_DRIVER"
typedef struct _HAL_SDIO_ADAPTER_
{
//	u8				*pTxBuff;			/* point to the SDIO TX Buffer */
//	u8				*pTxBuffAligned;	/* point to the SDIO TX Buffer with 4-bytes aligned */
//	u32				TXFifoRPtr;		    /* The SDIO TX(Host->Device) FIFO buffer read pointer */
#if SDIO_API_DEFINED
  VOID *spdio_priv; /*Data from User*/
#endif
  u8 *pTXBDAddr; /* The TX_BD start address */
  PSDIO_TX_BD pTXBDAddrAligned; /* The TX_BD start address, it must be 4-bytes aligned */
  PSDIO_TX_BD_HANDLE pTXBDHdl; /* point to the allocated memory for TX_BD Handle array */
  u16 TXBDWPtr; /* The SDIO TX(Host->Device) BD local write index, different with HW maintained write Index. */
  u16 TXBDRPtr; /* The SDIO TX(Host->Device) BD read index */
  u16 TXBDRPtrReg; /* The SDIO TX(Host->Device) BD read index has been write to HW register */

  u8 *pRXBDAddr; /* The RX_BD start address */
  PSDIO_RX_BD pRXBDAddrAligned; /* The RX_BD start address, it must be 8-bytes aligned */
  PSDIO_RX_BD_HANDLE pRXBDHdl; /* point to the allocated memory for RX_BD Handle array */
  u16 RXBDWPtr; /* The SDIO RX(Device->Host) BD write index */
  u16 RXBDRPtr; /* The SDIO RX(Device->Host) BD local read index, different with HW maintained Read Index. */
  u16 IntMask; /* The Interrupt Mask */
  u16 IntStatus; /* The Interrupt Status */
  u32 Events; /* The Event to the SDIO Task */

  u8 CCPWM; /* the value write to register CCPWM, which will sync to Host HCPWM */
  u8 reserve1;
  u16 CCPWM2; /* the value write to register CCPWM2, which will sync to Host HCPWM2 */
  u8 CRPWM; /* sync from Host HRPWM */
  u8 reserve2;
  u16 CRPWM2; /* sync from Host HRPWM2 */

#if !TASK_SCHEDULER_DISABLED
  _Sema TxSema; /* Semaphore for SDIO TX, use to wakeup the SDIO TX task */
  _Sema RxSema; /* Semaphore for SDIO RX, use to wakeup the SDIO RX task */
#else
  u32 EventSema; /* Semaphore for SDIO events, use to wakeup the SDIO task */
#endif
  s8 (*Tx_Callback)( VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize, u8 type ); /* to hook the WLan driver TX callback function to handle a Packet TX */
  VOID *pTxCb_Adapter; /* a pointer will be used to call the TX Callback function,
   which is from the TX CallBack function register */
#if SDIO_API_DEFINED
  s8 (*Rx_Done_Callback)( VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize, u8 type ); /* to hook RX done callback function to release packet */
  VOID *pRxDoneCb_Adapter; /* a pointer will be used to call the RX Done Callback function,
   which is from the TX CallBack function register */
#endif
  s8 (*pTxCallback_Backup)( VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize, u8 type );// Use to back up the registered TX Callback function, for MP/Normal mode switch
  VOID *pTxCb_Adapter_Backup;	// Backup the pTxCb_Adapter, for MP/Normal mode switch
#if SDIO_DEBUG
  _LIST FreeTxPktList; /* The list to queue free Tx packets handler */
  SDIO_TX_PACKET *pTxPktHandler; /* to store allocated TX Packet handler memory address */
#endif
  _LIST RxPktList; /* The list to queue RX packets */
  _LIST FreeRxPktList; /* The list to queue free Rx packets handler */
//	_LIST			RecyclePktList;		/* The list to queue packets handler to be recycled */
  SDIO_RX_PACKET *pRxPktHandler; /* to store allocated RX Packet handler memory address */
  _Mutex RxMutex; /* The Mutex to protect RxPktList */
  u32 RxInQCnt; /* The packet count for Rx In Queue */
#if SDIO_DEBUG
  _Mutex StatisticMutex; /* The Mutex to protect Statistic data */
  u32 MemAllocCnt;		// Memory allocated count, for debug only
  u32 MAllocFailedCnt;// MemAlloc Failed count, for debugging
#endif
  VOID *pHalOp; /* point to HAL operation function table */
  RTL_MAILBOX *pMBox; /* the Mail box for other driver module can send message to SDIO driver */

#ifdef PLATFORM_FREERTOS
  xTaskHandle xSDIOTxTaskHandle; /* The handle of the SDIO Task for TX, can be used to delte the task */
  xTaskHandle xSDIORxTaskHandle; /* The handle of the SDIO Task speical for RX, can be used to delte the task */
#endif
  u8 RxFifoBusy; /* is the RX BD fetch hardware busy */

#if SDIO_MP_MODE
#if !TASK_SCHEDULER_DISABLED
u32 MP_Events; /* The Event to the SDIO Task */
_Sema MP_EventSema; /* Semaphore for SDIO events, use to wakeup the SDIO task */
RTL_MAILBOX *pMP_MBox; /* the Mail box for communication with other driver module */
#ifdef PLATFORM_FREERTOS
xTaskHandle MP_TaskHandle; /* The handle of the MP loopback Task, can be used to delte the task */
#endif  // end of "#ifdef PLATFORM_FREERTOS"
#endif  // end of "#if !TASK_SCHEDULER_DISABLED"
// for MP mode
RTL_TIMER *pPeriodTimer; /* a timer to calculate throughput periodically */
u8 MP_ModeEn; /* is in MP mode */
u8 MP_LoopBackEn; /* is loop-back enabled */
u8 MP_ContinueTx; /* is continue TX test enabled */
u8 MP_ContinueRx; /* is continue RX test enabled */
u8 MP_ContinueRxMode; /* continue RX test mode: static RX Buf, Dyna-Allocate RX Buf, Pre-Allocate RX Buf */
u8 MP_CRxInfinite; /* is non-stop SDIO RX, no packet count limit */
u16 MP_CRxSize; /* SDIO RX test packet size */
u8 *pMP_CRxBuf;        // the buffer for continye RX test
u32 MP_CRxPktCnt; /* SDIO RX test packet count */
u32 MP_CRxPktPendingCnt; /* SDIO RX test packet pening count */
u32 MP_TxPktCnt; /* SDIO TX packet count */
u32 MP_RxPktCnt; /* SDIO RX packet count */
u32 MP_TxByteCnt; /* SDIO TX Byte count */
u32 MP_RxByteCnt; /* SDIO RX Byte count */
u32 MP_TxDropCnt; /* SDIO TX Drop packet count */
u32 MP_RxDropCnt; /* SDIO RX Drop packet count */

u32 MP_TxPktCntInPeriod; /* SDIO TX packet count in a period */
u32 MP_RxPktCntInPeriod; /* SDIO RX packet count in a period */
u32 MP_TxByteCntInPeriod; /* SDIO TX Byte count in a period */
u32 MP_RxByteCntInPeriod; /* SDIO RX Byte count in a period */

u32 MP_TxAvgTPWin[SDIO_AVG_TP_WIN_SIZE]; /* a window of SDIO TX byte count history, for average throughput calculation */
u32 MP_RxAvgTPWin[SDIO_AVG_TP_WIN_SIZE]; /* a window of SDIO RX byte count history, for average throughput calculation */
u32 MP_TxAvgTPWinSum; /* The sum of all byte-count in the window */
u32 MP_RxAvgTPWinSum; /* The sum of all byte-count in the window */
u8 OldestTxAvgWinIdx; /* the index of the oldest TX byte count log */
u8 TxAvgWinCnt; /* the number of log in the Window */
u8 OldestRxAvgWinIdx; /* the index of the oldest RX byte count log */
u8 RxAvgWinCnt; /* the number of log in the Window */

_LIST MP_RxPktList; /* The list to queue RX packets, for MP loopback test */
#endif	// end of '#if SDIO_MP_MODE'
} HAL_SDIO_ADAPTER, *PHAL_SDIO_ADAPTER;
#endif  // end of "#else of "#if SDIO_BOOT_DRIVER""

typedef struct _HAL_SDIO_OP_
{
BOOL (*HalSdioDevInit)( PHAL_SDIO_ADAPTER pSDIODev );
VOID (*HalSdioDevDeInit)( PHAL_SDIO_ADAPTER pSDIODev );
VOID (*HalSdioSendC2HIOMsg)( PHAL_SDIO_ADAPTER pSDIODev, u32 *C2HMsg );
u8 (*HalSdioSendC2HPktMsg)( PHAL_SDIO_ADAPTER pSDIODev, u8 *C2HMsg, u16 MsgLen );
VOID (*HalSdioRegTxCallback)( PHAL_SDIO_ADAPTER pSDIODev,
  s8 (*CallbackFun)( VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize, u8 Type ), VOID *pAdapter );
s8 (*HalSdioRxCallback)( PHAL_SDIO_ADAPTER pSDIODev, VOID *pData, u16 Offset, u16 PktSize,
  u8 CmdType );
#if SDIO_API_DEFINED
VOID (*HalSdioRegRxDoneCallback)( PHAL_SDIO_ADAPTER pSDIODev,
  s8 (*CallbackFun)( VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize, u8 Type ), VOID *pAdapter );
#endif
#if SDIO_MP_MODE
VOID (*HalSdioDevMPApp)(PHAL_SDIO_ADAPTER pSDIODev, u16 argc, u8 *argv[]);
#endif
} HAL_SDIO_OP, *PHAL_SDIO_OP;

extern BOOL SDIO_Device_Init(
IN PHAL_SDIO_ADAPTER pSDIODev
);
extern VOID SDIO_Device_DeInit(
IN PHAL_SDIO_ADAPTER pSDIODev
);
extern VOID SDIO_Send_C2H_IOMsg(
IN PHAL_SDIO_ADAPTER pSDIODev,
IN u32 *C2HMsg
);
extern u8 SDIO_Send_C2H_PktMsg(
IN PHAL_SDIO_ADAPTER pSDIODev,
IN u8 *C2HMsg,
IN u16 MsgLen
);
extern VOID SDIO_Register_Tx_Callback(
IN PHAL_SDIO_ADAPTER pSDIODev,
IN s8 (*Tx_Callback)(VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize, u8 Type),
IN VOID *pAdapter
);
#if SDIO_API_DEFINED
extern VOID SDIO_Register_Rx_Done_Callback(
IN PHAL_SDIO_ADAPTER pSDIODev,
IN s8 (*Rx_Done_Callback)(VOID *pAdapter, u8 *pPkt, u16 Offset, u16 PktSize, u8 Type),
IN VOID *pAdapter
);
#endif
extern s8 SDIO_Rx_Callback(
IN PHAL_SDIO_ADAPTER pSDIODev,
IN VOID *pData,
IN u16 Offset,
IN u16 Length,
IN u8 CmdType
);
#if SDIO_MP_MODE
extern VOID SDIO_DeviceMPApp(
IN PHAL_SDIO_ADAPTER pSDIODev,
IN u16 argc,
IN u8 *argv[]
);
#endif

extern PHAL_SDIO_ADAPTER pgSDIODev;
extern VOID HalSdioInit( VOID );
extern VOID HalSdioDeInit( VOID );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_SDIO_DEVICE_H__ */
