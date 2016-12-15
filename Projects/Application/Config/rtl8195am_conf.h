#ifndef __RTL8195AM_CONF_H__
#define __RTL8195AM_CONF_H__

#define CONFIG_ADC_EN       ( 1 )
#define CONFIG_DAC_EN       ( 1 )
#define CONFIG_GDMA_EN      ( 1 )
#define CONFIG_GPIO_EN      ( 1 )
#define CONFIG_I2C_EN       ( 1 )
#define CONFIG_I2S_EN       ( 1 )
#define CONFIG_MII_EN       ( 1 )
#define CONFIG_NFC_EN       ( 1 )
#define CONFIG_PWM_EN       ( 1 )
#define CONFIG_SSI_EN       ( 1 )
#define CONFIG_UART_EN      ( 1 )
#define CONFIG_USB_EN       ( 1 )
#define CONFIG_WDT_EN       ( 1 )

#define CONFIG_CRYPTO_EN    ( 1 )
#define CONFIG_EFUSE_EN     ( 1 )
#define CONFIG_SDR_EN       ( 1 )
#define CONFIG_SPIC_EN      ( 1 )
#define CONFIG_TIMER_EN     ( 1 )
#define CONFIG_WIFI_EN      ( 1 )

/* Includes ------------------------------------------------------------------*/

#include "rtl8195am_adc.h"
#include "rtl8195am_dac.h"
#include "rtl8195am_gdma.h"
#include "rtl8195am_gpio.h"
#include "rtl8195am_gspi.h"
#include "rtl8195am_i2c.h"
#include "rtl8195am_i2s.h"
#include "rtl8195am_irq.h"
#include "rtl8195am_mii.h"
#include "rtl8195am_misc.h"
#include "rtl8195am_nfc.h"
#include "rtl8195am_pcm.h"
#include "rtl8195am_peri_on.h"
#include "rtl8195am_pinmux.h"
#include "rtl8195am_pwm.h"
#include "rtl8195am_ssi.h"
#include "rtl8195am_util.h"
#include "rtl8195am_sdio.h"
#include "rtl8195am_sdio_host.h"
#include "rtl8195am_sdr.h"
#include "rtl8195am_sdr_controller.h"
#include "rtl8195am_spi_flash.h"
#include "rtl8195am_ssi.h"
#include "rtl8195am_sys_on.h"
#include "rtl8195am_timer.h"
#include "rtl8195am_uart.h"
#include "rtl8195am_log_uart.h"
#include "rtl8195am_usb.h"
#include "rtl8195am_wdt.h"

#include "rtl8195am_crypto.h"
#include "rtl8195am_efuse.h"
#include "rtl8195am_sdr.h"
#include "rtl8195am_spic.h"
#include "rtl8195am_timerc.h"
#include "rtl8195am_wifi.h"

#endif

