#ifndef __RTL8195AM_USB_H__
#define __RTL8195AM_USB_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

#define OTG_FAST_INIT   1

#define HAL_OTG_READ32(addr)            HAL_READ32(USB_OTG_REG_BASE, (u32)addr)
#define HAL_OTG_WRITE32(addr, value)    HAL_WRITE32(USB_OTG_REG_BASE, (u32)addr, value)

#define HAL_OTG_MODIFY32(addr, clrmsk, setmsk)     HAL_WRITE32(USB_OTG_REG_BASE,(u32)addr,\
                                                   ((HAL_READ32(USB_OTG_REG_BASE, (u32)addr) & (~clrmsk)) | setmsk))

#define DWC_READ_REG32(_reg_)   HAL_OTG_READ32((u32)_reg_)
#define DWC_WRITE_REG32(_reg_, _val_)   HAL_OTG_WRITE32((u32)_reg_,_val_)
#define DWC_MODIFY_REG32(_reg_,_cmsk_,_smsk_)   HAL_OTG_MODIFY32((u32)_reg_,_cmsk_,_smsk_)

//This part is added for RTK power sequence

//3 SYS_ON reg

//#define REG_SYS_FUNC_EN                     0x08
#define BIT_SHIFT_SOC_SYSPEON_EN   4
#define BIT_MASK_SOC_SYSPEON_EN    0x1
#define BIT_SOC_SYSPEON_EN_OTG(x)(((x) & BIT_MASK_SOC_SYSPEON_EN) << BIT_SHIFT_SOC_SYSPEON_EN)
#define BIT_INVC_SOC_SYSPEON_EN (~(BIT_MASK_SOC_SYSPEON_EN << BIT_SHIFT_SOC_SYSPEON_EN))

//3 Peri_ON reg
#define REG_OTG_PWCSEQ_OFFSET_OTG               0x40000000
#define REG_OTG_PWCSEQ_PWC_OTG                  0x200
#define REG_OTG_PWCSEQ_ISO_OTG                  0x204
#define REG_SOC_HCI_COM_FUNC_EN_OTG             0x214
#define REG_PESOC_HCI_CLK_CTRL0_OTG             0x240

//#define REG_PON_ISO_CTRL                        0x204

#define REG_OTG_PWCSEQ_IP_OFF               0x30004     //This is in OTG IP
#define REG_OTG_PS_INTR_STS                 0x30008     //This is in OTG IP
#define REG_OTG_PS_INTR_MSK                 0x3000C     //This is in OTG IP

//4 REG_OTG_PWCSEQ_PWC
#define BIT_SHIFT_PWC_USBD_EN   0
#define BIT_MASK_PWC_USBD_EN    0x1
#define BIT_PWC_USBD_EN(x)(((x) & BIT_MASK_PWC_USBD_EN) << BIT_SHIFT_PWC_USBD_EN)
#define BIT_INVC_PWC_USBD_EN (~(BIT_MASK_PWC_USBD_EN << BIT_SHIFT_PWC_USBD_EN))

#define BIT_SHIFT_PWC_UPLV_EN   1
#define BIT_MASK_PWC_UPLV_EN    0x1
#define BIT_PWC_UPLV_EN(x)(((x) & BIT_MASK_PWC_UPLV_EN) << BIT_SHIFT_PWC_UPLV_EN)
#define BIT_INVC_PWC_UPLV_EN (~(BIT_MASK_PWC_UPLV_EN << BIT_SHIFT_PWC_UPLV_EN))

#define BIT_SHIFT_PWC_UPHV_EN   2
#define BIT_MASK_PWC_UPHV_EN    0x1
#define BIT_PWC_UPHV_EN(x)(((x) & BIT_MASK_PWC_UPHV_EN) << BIT_SHIFT_PWC_UPHV_EN)
#define BIT_INVC_PWC_UPHV_EN (~(BIT_MASK_PWC_UPHV_EN << BIT_SHIFT_PWC_UPHV_EN))

//4 REG_OTG_PWCSEQ_ISO
#define BIT_SHIFT_ISO_USBD_EN   0
#define BIT_MASK_ISO_USBD_EN    0x1
#define BIT_ISO_USBD_EN(x)(((x) & BIT_MASK_ISO_USBD_EN) << BIT_SHIFT_ISO_USBD_EN)
#define BIT_INVC_ISO_USBD_EN (~(BIT_MASK_ISO_USBD_EN << BIT_SHIFT_ISO_USBD_EN))

#define BIT_SHIFT_ISO_USBA_EN   1
#define BIT_MASK_ISO_USBA_EN    0x1
#define BIT_ISO_USBA_EN(x)(((x) & BIT_MASK_ISO_USBA_EN) << BIT_SHIFT_ISO_USBA_EN)
#define BIT_INVC_ISO_USBA_EN (~(BIT_MASK_ISO_USBA_EN << BIT_SHIFT_ISO_USBA_EN))

//4 REG_SOC_HCI_COM_FUNC_EN
#define BIT_SHIFT_SOC_HCI_OTG_EN   4
#define BIT_MASK_SOC_HCI_OTG_EN    0x1
#define BIT_SOC_HCI_OTG_EN_OTG(x)(((x) & BIT_MASK_SOC_HCI_OTG_EN) << BIT_SHIFT_SOC_HCI_OTG_EN)
#define BIT_INVC_SOC_HCI_OTG_EN (~(BIT_MASK_SOC_HCI_OTG_EN << BIT_SHIFT_SOC_HCI_OTG_EN))

//4 REG_PESOC_HCI_CLK_CTRL0
#define BIT_SHIFT_SOC_ACTCK_OTG_EN   4
#define BIT_MASK_SOC_ACTCK_OTG_EN    0x1
#define BIT_SOC_ACTCK_OTG_EN_OTG(x)(((x) & BIT_MASK_SOC_ACTCK_OTG_EN) << BIT_SHIFT_SOC_ACTCK_OTG_EN)
#define BIT_INVC_SOC_ACTCK_OTG_EN (~(BIT_MASK_SOC_ACTCK_OTG_EN << BIT_SHIFT_SOC_ACTCK_OTG_EN))

//4 REG_OTG_PWCSEQ_OTG
#define BIT_SHIFT_USBOTG_PS_EN   0
#define BIT_MASK_USBOTG_PS_EN    0x1
#define BIT_USBOTG_PS_EN(x)(((x) & BIT_MASK_USBOTG_PS_EN) << BIT_SHIFT_USBOTG_PS_EN)
#define BIT_INVC_USBOTG_PS_EN (~(BIT_MASK_USBOTG_PS_EN << BIT_SHIFT_USBOTG_PS_EN))

#define BIT_SHIFT_USBOTG_DIS_SUSB   1
#define BIT_MASK_USBOTG_DIS_SUSB    0x1
#define BIT_USBOTG_DIS_SUSB(x)(((x) & BIT_MASK_USBOTG_DIS_SUSB) << BIT_SHIFT_USBOTG_DIS_SUSB)
#define BIT_INVC_USBOTG_DIS_SUSB (~(BIT_MASK_USBOTG_DIS_SUSB << BIT_SHIFT_USBOTG_DIS_SUSB))

#define BIT_SHIFT_USBOTG_SUSBM   4
#define BIT_MASK_USBOTG_SUSBM    0x1
#define BIT_USBOTG_SUSBM(x)(((x) & BIT_MASK_USBOTG_SUSBM) << BIT_SHIFT_USBOTG_SUSBM)
#define BIT_INVC_USBOTG_SUSBM (~(BIT_MASK_USBOTG_SUSBM << BIT_SHIFT_USBOTG_SUSBM))

#define BIT_SHIFT_UPLL_CKRDY   5
#define BIT_MASK_UPLL_CKRDY    0x1
#define BIT_UPLL_CKRDY(x)(((x) & BIT_MASK_UPLL_CKRDY) << BIT_SHIFT_UPLL_CKRDY)
#define BIT_INVC_UPLL_CKRDY (~(BIT_MASK_UPLL_CKRDY << BIT_SHIFT_UPLL_CKRDY))

#define BIT_SHIFT_USB_LS        6
#define BIT_MASK_USB_LS    0x3
#define BIT_USB_LS(x)(((x) & BIT_MASK_USB_LS) << BIT_SHIFT_USB_LS)
#define BIT_INVC_USB_LS (~(BIT_MASK_USB_LS << BIT_SHIFT_USB_LS))

#define BIT_SHIFT_USBOTG_EN   8
#define BIT_MASK_USBOTG_EN    0x1
#define BIT_USBOTG_EN(x)(((x) & BIT_MASK_USBOTG_EN) << BIT_SHIFT_USBOTG_EN)
#define BIT_INVC_USBOTG_EN (~(BIT_MASK_USBOTG_EN << BIT_SHIFT_USBOTG_EN))

#define BIT_SHIFT_USBPHY_EN   9
#define BIT_MASK_USBPHY_EN    0x1
#define BIT_USBPHY_EN(x)(((x) & BIT_MASK_USBPHY_EN) << BIT_SHIFT_USBPHY_EN)
#define BIT_INVC_USBPHY_EN (~(BIT_MASK_USBPHY_EN << BIT_SHIFT_USBPHY_EN))

#define BIT_SHIFT_USB_GT_LS_EN   10
#define BIT_MASK_USB_GT_LS_EN    0x1
#define BIT_USB_GT_LS_EN(x)(((x) & BIT_MASK_USB_GT_LS_EN) << BIT_SHIFT_USB_GT_LS_EN)
#define BIT_INVC_USB_GT_LS_EN (~(BIT_MASK_USB_GT_LS_EN << BIT_SHIFT_USB_GT_LS_EN))

struct zero_dev
{
  //ModifiedByJD    spinlock_t    lock;
  struct usb_gadget *gadget;
  struct usb_request *req; /* for control responses */

  /* when configured, we have one of two configs:
   * - source data (in to host) and sink it (out from host)
   * - or loop it back (out from host back in to host)
   */
  u8 config;
  struct usb_ep *in_ep, *out_ep, *status_ep;//ModifiedByJD

  const struct usb_endpoint_descriptor *in, *out, *status;                 //ModifiedByJD
/* autoresume timer */
//ModifiedByJD    struct timer_list resume;
};

// common command for USB
#define USB_CMD_TX_ETH         0x83    // request to TX a 802.3 packet
#define USB_CMD_TX_WLN         0x81    // request to TX a 802.11 packet
#define USB_CMD_H2C            0x11    // H2C(host to device) command packet
#define USB_CMD_MEMRD          0x51    // request to read a block of memory data
#define USB_CMD_MEMWR          0x53    // request to write a block of memory
#define USB_CMD_MEMST          0x55    // request to set a block of memory with a value
#define USB_CMD_STARTUP        0x61    // request to jump to the start up function

#define USB_CMD_RX_ETH         0x82    // indicate a RX 802.3 packet
#define USB_CMD_RX_WLN         0x80    // indicate a RX 802.11 packet
#define USB_CMD_C2H            0x10    // C2H(device to host) command packet
#define USB_CMD_MEMRD_RSP      0x50    // response to memory block read command
#define USB_CMD_MEMWR_RSP      0x52    // response to memory write command
#define USB_CMD_MEMST_RSP      0x54    // response to memory set command
#define USB_CMD_STARTED        0x60    // indicate the program has jumped to the given function

// TODO: This data structer just for test, we should modify it for the normal driver
typedef struct _USB_TX_DESC
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;       // bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;    // bit[31:24], the bus aggregation number
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
} USB_TX_DESC, *PUSB_TX_DESC;

#define SIZE_USB_TX_DESC  sizeof(USB_TX_DESC)

// TX Desc for Memory Write command
typedef struct _USB_TX_DESC_MW
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;       // bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;    // bit[31:24], the bus aggregation number
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
} USB_TX_DESC_MW, *PUSB_TX_DESC_MW;

// TX Desc for Memory Read command
typedef struct _USB_TX_DESC_MR
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;       // bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;    // bit[31:24], the bus aggregation number
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
} USB_TX_DESC_MR, *PUSB_TX_DESC_MR;

// TX Desc for Memory Set command
typedef struct _USB_TX_DESC_MS
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;       // bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;    // bit[31:24], the bus aggregation number
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
} USB_TX_DESC_MS, *PUSB_TX_DESC_MS;

// TX Desc for Jump to Start command
typedef struct _USB_TX_DESC_JS
{
  // u4Byte 0
#if (SYSTEM_ENDIAN==PLATFORM_LITTLE_ENDIAN)
  u32 txpktsize :16;       // bit[15:0]
  u32 offset :8;       // bit[23:16], store the sizeof(SDIO_TX_DESC)
  u32 bus_agg_num :8;    // bit[31:24], the bus aggregation number
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
} USB_TX_DESC_JS, *PUSB_TX_DESC_JS;

typedef struct _USB_RX_DESC
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
} USB_RX_DESC, *PUSB_RX_DESC;

// For memory read command
typedef struct _USB_RX_DESC_MR
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
} USB_RX_DESC_MR, *PUSB_RX_DESC_MR;

// For memory write reply command
typedef struct _USB_RX_DESC_MW
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
} USB_RX_DESC_MW, *PUSB_RX_DESC_MW;

// For memory set reply command
typedef struct _USB_RX_DESC_MS
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
} USB_RX_DESC_MS, *PUSB_RX_DESC_MS;

// For firmware ready reply command
typedef struct _USB_RX_DESC_FS
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
  u32 rsvd2;

  // u4Byte 3
  u32 rsvd3;

  // u4Byte 4
  u32 rsvd4;

  // u4Byte 5
  u32 rsvd5;
} USB_RX_DESC_FS, *PUSB_RX_DESC_FS;

#define SIZE_USB_RX_DESC  sizeof(USB_RX_DESC)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_USB_H__ */
