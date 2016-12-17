#ifndef __RTL8195AM_ADC_H__
#define __RTL8195AM_ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "rtl8195am.h"
#include "rtl8195am_conf.h"
#include "rtl8195am_types.h"
#include "rtl8195am_macro.h"
#include "rtl8195am_compiler.h"

//================ Register Bit Field ==========================
//2 REG_ADC_FIFO_READ

#define BIT_SHIFT_ADC_FIFO_RO 0
#define BIT_MASK_ADC_FIFO_RO 0xffffffffL
#define BIT_ADC_FIFO_RO(x)                    	(((x) & BIT_MASK_ADC_FIFO_RO) << BIT_SHIFT_ADC_FIFO_RO)
#define BIT_CTRL_ADC_FIFO_RO(x)               	(((x) & BIT_MASK_ADC_FIFO_RO) << BIT_SHIFT_ADC_FIFO_RO)
#define BIT_GET_ADC_FIFO_RO(x)                	(((x) >> BIT_SHIFT_ADC_FIFO_RO) & BIT_MASK_ADC_FIFO_RO)

//2 REG_ADC_CONTROL

#define BIT_SHIFT_ADC_DBG_SEL 24
#define BIT_MASK_ADC_DBG_SEL 0x7
#define BIT_ADC_DBG_SEL(x)                    	(((x) & BIT_MASK_ADC_DBG_SEL) << BIT_SHIFT_ADC_DBG_SEL)
#define BIT_CTRL_ADC_DBG_SEL(x)               	(((x) & BIT_MASK_ADC_DBG_SEL) << BIT_SHIFT_ADC_DBG_SEL)
#define BIT_GET_ADC_DBG_SEL(x)                	(((x) >> BIT_SHIFT_ADC_DBG_SEL) & BIT_MASK_ADC_DBG_SEL)

#define BIT_SHIFT_ADC_THRESHOLD 16
#define BIT_MASK_ADC_THRESHOLD 0x3f
#define BIT_ADC_THRESHOLD(x)                  	(((x) & BIT_MASK_ADC_THRESHOLD) << BIT_SHIFT_ADC_THRESHOLD)
#define BIT_CTRL_ADC_THRESHOLD(x)             	(((x) & BIT_MASK_ADC_THRESHOLD) << BIT_SHIFT_ADC_THRESHOLD)
#define BIT_GET_ADC_THRESHOLD(x)              	(((x) >> BIT_SHIFT_ADC_THRESHOLD) & BIT_MASK_ADC_THRESHOLD)

#define BIT_SHIFT_ADC_BURST_SIZE 8
#define BIT_MASK_ADC_BURST_SIZE 0x1f
#define BIT_ADC_BURST_SIZE(x)                 	(((x) & BIT_MASK_ADC_BURST_SIZE) << BIT_SHIFT_ADC_BURST_SIZE)
#define BIT_CTRL_ADC_BURST_SIZE(x)            	(((x) & BIT_MASK_ADC_BURST_SIZE) << BIT_SHIFT_ADC_BURST_SIZE)
#define BIT_GET_ADC_BURST_SIZE(x)             	(((x) >> BIT_SHIFT_ADC_BURST_SIZE) & BIT_MASK_ADC_BURST_SIZE)

#define BIT_ADC_ENDIAN                        	BIT(3)
#define BIT_SHIFT_ADC_ENDIAN                  	3
#define BIT_MASK_ADC_ENDIAN                   	0x1
#define BIT_CTRL_ADC_ENDIAN(x)                	(((x) & BIT_MASK_ADC_ENDIAN) << BIT_SHIFT_ADC_ENDIAN)

#define BIT_ADC_OVERWRITE                     	BIT(2)
#define BIT_SHIFT_ADC_OVERWRITE               	2
#define BIT_MASK_ADC_OVERWRITE                	0x1
#define BIT_CTRL_ADC_OVERWRITE(x)             	(((x) & BIT_MASK_ADC_OVERWRITE) << BIT_SHIFT_ADC_OVERWRITE)

#define BIT_ADC_ONESHOT                       	BIT(1)
#define BIT_SHIFT_ADC_ONESHOT                 	1
#define BIT_MASK_ADC_ONESHOT                  	0x1
#define BIT_CTRL_ADC_ONESHOT(x)               	(((x) & BIT_MASK_ADC_ONESHOT) << BIT_SHIFT_ADC_ONESHOT)

#define BIT_ADC_COMP_ONLY                     	BIT(0)
#define BIT_SHIFT_ADC_COMP_ONLY               	0
#define BIT_MASK_ADC_COMP_ONLY                	0x1
#define BIT_CTRL_ADC_COMP_ONLY(x)             	(((x) & BIT_MASK_ADC_COMP_ONLY) << BIT_SHIFT_ADC_COMP_ONLY)

//2 REG_ADC_INTR_EN
#define BIT_ADC_AWAKE_CPU_EN                  	BIT(7)
#define BIT_SHIFT_ADC_AWAKE_CPU_EN            	7
#define BIT_MASK_ADC_AWAKE_CPU_EN             	0x1
#define BIT_CTRL_ADC_AWAKE_CPU_EN(x)          	(((x) & BIT_MASK_ADC_AWAKE_CPU_EN) << BIT_SHIFT_ADC_AWAKE_CPU_EN)

#define BIT_ADC_FIFO_RD_ERROR_EN              	BIT(6)
#define BIT_SHIFT_ADC_FIFO_RD_ERROR_EN        	6
#define BIT_MASK_ADC_FIFO_RD_ERROR_EN         	0x1
#define BIT_CTRL_ADC_FIFO_RD_ERROR_EN(x)      	(((x) & BIT_MASK_ADC_FIFO_RD_ERROR_EN) << BIT_SHIFT_ADC_FIFO_RD_ERROR_EN)

#define BIT_ADC_FIFO_RD_REQ_EN                	BIT(5)
#define BIT_SHIFT_ADC_FIFO_RD_REQ_EN          	5
#define BIT_MASK_ADC_FIFO_RD_REQ_EN           	0x1
#define BIT_CTRL_ADC_FIFO_RD_REQ_EN(x)        	(((x) & BIT_MASK_ADC_FIFO_RD_REQ_EN) << BIT_SHIFT_ADC_FIFO_RD_REQ_EN)

#define BIT_ADC_FIFO_FULL_EN                  	BIT(4)
#define BIT_SHIFT_ADC_FIFO_FULL_EN            	4
#define BIT_MASK_ADC_FIFO_FULL_EN             	0x1
#define BIT_CTRL_ADC_FIFO_FULL_EN(x)          	(((x) & BIT_MASK_ADC_FIFO_FULL_EN) << BIT_SHIFT_ADC_FIFO_FULL_EN)

#define BIT_ADC_COMP_3_EN                     	BIT(3)
#define BIT_SHIFT_ADC_COMP_3_EN               	3
#define BIT_MASK_ADC_COMP_3_EN                	0x1
#define BIT_CTRL_ADC_COMP_3_EN(x)             	(((x) & BIT_MASK_ADC_COMP_3_EN) << BIT_SHIFT_ADC_COMP_3_EN)

#define BIT_ADC_COMP_2_EN                     	BIT(2)
#define BIT_SHIFT_ADC_COMP_2_EN               	2
#define BIT_MASK_ADC_COMP_2_EN                	0x1
#define BIT_CTRL_ADC_COMP_2_EN(x)             	(((x) & BIT_MASK_ADC_COMP_2_EN) << BIT_SHIFT_ADC_COMP_2_EN)

#define BIT_ADC_COMP_1_EN                     	BIT(1)
#define BIT_SHIFT_ADC_COMP_1_EN               	1
#define BIT_MASK_ADC_COMP_1_EN                	0x1
#define BIT_CTRL_ADC_COMP_1_EN(x)             	(((x) & BIT_MASK_ADC_COMP_1_EN) << BIT_SHIFT_ADC_COMP_1_EN)

#define BIT_ADC_COMP_0_EN                     	BIT(0)
#define BIT_SHIFT_ADC_COMP_0_EN               	0
#define BIT_MASK_ADC_COMP_0_EN                	0x1
#define BIT_CTRL_ADC_COMP_0_EN(x)             	(((x) & BIT_MASK_ADC_COMP_0_EN) << BIT_SHIFT_ADC_COMP_0_EN)

//2 REG_ADC_INTR_STS
#define BIT_ADC_FIFO_THRESHOLD                	BIT(7)
#define BIT_SHIFT_ADC_FIFO_THRESHOLD          	7
#define BIT_MASK_ADC_FIFO_THRESHOLD           	0x1
#define BIT_CTRL_ADC_FIFO_THRESHOLD(x)        	(((x) & BIT_MASK_ADC_FIFO_THRESHOLD) << BIT_SHIFT_ADC_FIFO_THRESHOLD)

#define BIT_ADC_FIFO_RD_ERROR_ST              	BIT(6)
#define BIT_SHIFT_ADC_FIFO_RD_ERROR_ST        	6
#define BIT_MASK_ADC_FIFO_RD_ERROR_ST         	0x1
#define BIT_CTRL_ADC_FIFO_RD_ERROR_ST(x)      	(((x) & BIT_MASK_ADC_FIFO_RD_ERROR_ST) << BIT_SHIFT_ADC_FIFO_RD_ERROR_ST)

#define BIT_ADC_FIFO_RD_REQ_ST                	BIT(5)
#define BIT_SHIFT_ADC_FIFO_RD_REQ_ST          	5
#define BIT_MASK_ADC_FIFO_RD_REQ_ST           	0x1
#define BIT_CTRL_ADC_FIFO_RD_REQ_ST(x)        	(((x) & BIT_MASK_ADC_FIFO_RD_REQ_ST) << BIT_SHIFT_ADC_FIFO_RD_REQ_ST)

#define BIT_ADC_FIFO_FULL_ST                  	BIT(4)
#define BIT_SHIFT_ADC_FIFO_FULL_ST            	4
#define BIT_MASK_ADC_FIFO_FULL_ST             	0x1
#define BIT_CTRL_ADC_FIFO_FULL_ST(x)          	(((x) & BIT_MASK_ADC_FIFO_FULL_ST) << BIT_SHIFT_ADC_FIFO_FULL_ST)

#define BIT_ADC_COMP_3_ST                     	BIT(3)
#define BIT_SHIFT_ADC_COMP_3_ST               	3
#define BIT_MASK_ADC_COMP_3_ST                	0x1
#define BIT_CTRL_ADC_COMP_3_ST(x)             	(((x) & BIT_MASK_ADC_COMP_3_ST) << BIT_SHIFT_ADC_COMP_3_ST)

#define BIT_ADC_COMP_2_ST                     	BIT(2)
#define BIT_SHIFT_ADC_COMP_2_ST               	2
#define BIT_MASK_ADC_COMP_2_ST                	0x1
#define BIT_CTRL_ADC_COMP_2_ST(x)             	(((x) & BIT_MASK_ADC_COMP_2_ST) << BIT_SHIFT_ADC_COMP_2_ST)

#define BIT_ADC_COMP_1_ST                     	BIT(1)
#define BIT_SHIFT_ADC_COMP_1_ST               	1
#define BIT_MASK_ADC_COMP_1_ST                	0x1
#define BIT_CTRL_ADC_COMP_1_ST(x)             	(((x) & BIT_MASK_ADC_COMP_1_ST) << BIT_SHIFT_ADC_COMP_1_ST)

#define BIT_ADC_COMP_0_ST                     	BIT(0)
#define BIT_SHIFT_ADC_COMP_0_ST               	0
#define BIT_MASK_ADC_COMP_0_ST                	0x1
#define BIT_CTRL_ADC_COMP_0_ST(x)             	(((x) & BIT_MASK_ADC_COMP_0_ST) << BIT_SHIFT_ADC_COMP_0_ST)

//2 REG_ADC_COMP_VALUE_L

#define BIT_SHIFT_ADC_COMP_TH_1 16
#define BIT_MASK_ADC_COMP_TH_1 0xffff
#define BIT_ADC_COMP_TH_1(x)                  	(((x) & BIT_MASK_ADC_COMP_TH_1) << BIT_SHIFT_ADC_COMP_TH_1)
#define BIT_CTRL_ADC_COMP_TH_1(x)             	(((x) & BIT_MASK_ADC_COMP_TH_1) << BIT_SHIFT_ADC_COMP_TH_1)
#define BIT_GET_ADC_COMP_TH_1(x)              	(((x) >> BIT_SHIFT_ADC_COMP_TH_1) & BIT_MASK_ADC_COMP_TH_1)

#define BIT_SHIFT_ADC_COMP_TH_0 0
#define BIT_MASK_ADC_COMP_TH_0 0xffff
#define BIT_ADC_COMP_TH_0(x)                  	(((x) & BIT_MASK_ADC_COMP_TH_0) << BIT_SHIFT_ADC_COMP_TH_0)
#define BIT_CTRL_ADC_COMP_TH_0(x)             	(((x) & BIT_MASK_ADC_COMP_TH_0) << BIT_SHIFT_ADC_COMP_TH_0)
#define BIT_GET_ADC_COMP_TH_0(x)              	(((x) >> BIT_SHIFT_ADC_COMP_TH_0) & BIT_MASK_ADC_COMP_TH_0)

//2 REG_ADC_COMP_VALUE_H

#define BIT_SHIFT_ADC_COMP_TH_3 16
#define BIT_MASK_ADC_COMP_TH_3 0xffff
#define BIT_ADC_COMP_TH_3(x)                  	(((x) & BIT_MASK_ADC_COMP_TH_3) << BIT_SHIFT_ADC_COMP_TH_3)
#define BIT_CTRL_ADC_COMP_TH_3(x)             	(((x) & BIT_MASK_ADC_COMP_TH_3) << BIT_SHIFT_ADC_COMP_TH_3)
#define BIT_GET_ADC_COMP_TH_3(x)              	(((x) >> BIT_SHIFT_ADC_COMP_TH_3) & BIT_MASK_ADC_COMP_TH_3)

#define BIT_SHIFT_ADC_COMP_TH_2 0
#define BIT_MASK_ADC_COMP_TH_2 0xffff
#define BIT_ADC_COMP_TH_2(x)                  	(((x) & BIT_MASK_ADC_COMP_TH_2) << BIT_SHIFT_ADC_COMP_TH_2)
#define BIT_CTRL_ADC_COMP_TH_2(x)             	(((x) & BIT_MASK_ADC_COMP_TH_2) << BIT_SHIFT_ADC_COMP_TH_2)
#define BIT_GET_ADC_COMP_TH_2(x)              	(((x) >> BIT_SHIFT_ADC_COMP_TH_2) & BIT_MASK_ADC_COMP_TH_2)

//2 REG_ADC_COMP_SET

#define BIT_SHIFT_ADC_GREATER_THAN 0
#define BIT_MASK_ADC_GREATER_THAN 0xf
#define BIT_ADC_GREATER_THAN(x)               	(((x) & BIT_MASK_ADC_GREATER_THAN) << BIT_SHIFT_ADC_GREATER_THAN)
#define BIT_CTRL_ADC_GREATER_THAN(x)          	(((x) & BIT_MASK_ADC_GREATER_THAN) << BIT_SHIFT_ADC_GREATER_THAN)
#define BIT_GET_ADC_GREATER_THAN(x)           	(((x) >> BIT_SHIFT_ADC_GREATER_THAN) & BIT_MASK_ADC_GREATER_THAN)

//2 REG_ADC_POWER

#define BIT_SHIFT_ADC_PWR_CUT_CNTR 16
#define BIT_MASK_ADC_PWR_CUT_CNTR 0xff
#define BIT_ADC_PWR_CUT_CNTR(x)               	(((x) & BIT_MASK_ADC_PWR_CUT_CNTR) << BIT_SHIFT_ADC_PWR_CUT_CNTR)
#define BIT_CTRL_ADC_PWR_CUT_CNTR(x)          	(((x) & BIT_MASK_ADC_PWR_CUT_CNTR) << BIT_SHIFT_ADC_PWR_CUT_CNTR)
#define BIT_GET_ADC_PWR_CUT_CNTR(x)           	(((x) >> BIT_SHIFT_ADC_PWR_CUT_CNTR) & BIT_MASK_ADC_PWR_CUT_CNTR)

#define BIT_ADC_FIFO_ON_ST                    	BIT(11)
#define BIT_SHIFT_ADC_FIFO_ON_ST              	11
#define BIT_MASK_ADC_FIFO_ON_ST               	0x1
#define BIT_CTRL_ADC_FIFO_ON_ST(x)            	(((x) & BIT_MASK_ADC_FIFO_ON_ST) << BIT_SHIFT_ADC_FIFO_ON_ST)

#define BIT_ADC_ISO_ON_ST                     	BIT(10)
#define BIT_SHIFT_ADC_ISO_ON_ST               	10
#define BIT_MASK_ADC_ISO_ON_ST                	0x1
#define BIT_CTRL_ADC_ISO_ON_ST(x)             	(((x) & BIT_MASK_ADC_ISO_ON_ST) << BIT_SHIFT_ADC_ISO_ON_ST)

#define BIT_ADC_PWR33_ON_ST                   	BIT(9)
#define BIT_SHIFT_ADC_PWR33_ON_ST             	9
#define BIT_MASK_ADC_PWR33_ON_ST              	0x1
#define BIT_CTRL_ADC_PWR33_ON_ST(x)           	(((x) & BIT_MASK_ADC_PWR33_ON_ST) << BIT_SHIFT_ADC_PWR33_ON_ST)

#define BIT_ADC_PWR12_ON_ST                   	BIT(8)
#define BIT_SHIFT_ADC_PWR12_ON_ST             	8
#define BIT_MASK_ADC_PWR12_ON_ST              	0x1
#define BIT_CTRL_ADC_PWR12_ON_ST(x)           	(((x) & BIT_MASK_ADC_PWR12_ON_ST) << BIT_SHIFT_ADC_PWR12_ON_ST)

#define BIT_ADC_ISO_MANUAL                    	BIT(3)
#define BIT_SHIFT_ADC_ISO_MANUAL              	3
#define BIT_MASK_ADC_ISO_MANUAL               	0x1
#define BIT_CTRL_ADC_ISO_MANUAL(x)            	(((x) & BIT_MASK_ADC_ISO_MANUAL) << BIT_SHIFT_ADC_ISO_MANUAL)

#define BIT_ADC_PWR33_MANUAL                  	BIT(2)
#define BIT_SHIFT_ADC_PWR33_MANUAL            	2
#define BIT_MASK_ADC_PWR33_MANUAL             	0x1
#define BIT_CTRL_ADC_PWR33_MANUAL(x)          	(((x) & BIT_MASK_ADC_PWR33_MANUAL) << BIT_SHIFT_ADC_PWR33_MANUAL)

#define BIT_ADC_PWR12_MANUAL                  	BIT(1)
#define BIT_SHIFT_ADC_PWR12_MANUAL            	1
#define BIT_MASK_ADC_PWR12_MANUAL             	0x1
#define BIT_CTRL_ADC_PWR12_MANUAL(x)          	(((x) & BIT_MASK_ADC_PWR12_MANUAL) << BIT_SHIFT_ADC_PWR12_MANUAL)

#define BIT_ADC_PWR_AUTO                      	BIT(0)
#define BIT_SHIFT_ADC_PWR_AUTO                	0
#define BIT_MASK_ADC_PWR_AUTO                 	0x1
#define BIT_CTRL_ADC_PWR_AUTO(x)              	(((x) & BIT_MASK_ADC_PWR_AUTO) << BIT_SHIFT_ADC_PWR_AUTO)

//2 REG_ADC_ANAPAR_AD0

#define BIT_SHIFT_ADC_ANAPAR_AD0 2
#define BIT_MASK_ADC_ANAPAR_AD0 0x3fffffff
#define BIT_ADC_ANAPAR_AD0(x)                 	(((x) & BIT_MASK_ADC_ANAPAR_AD0) << BIT_SHIFT_ADC_ANAPAR_AD0)
#define BIT_CTRL_ADC_ANAPAR_AD0(x)            	(((x) & BIT_MASK_ADC_ANAPAR_AD0) << BIT_SHIFT_ADC_ANAPAR_AD0)
#define BIT_GET_ADC_ANAPAR_AD0(x)             	(((x) >> BIT_SHIFT_ADC_ANAPAR_AD0) & BIT_MASK_ADC_ANAPAR_AD0)

#define BIT_ADC_AUDIO_EN                      	BIT(1)
#define BIT_SHIFT_ADC_AUDIO_EN                	1
#define BIT_MASK_ADC_AUDIO_EN                 	0x1
#define BIT_CTRL_ADC_AUDIO_EN(x)              	(((x) & BIT_MASK_ADC_AUDIO_EN) << BIT_SHIFT_ADC_AUDIO_EN)

#define BIT_ADC_EN_MANUAL                     	BIT(0)
#define BIT_SHIFT_ADC_EN_MANUAL               	0
#define BIT_MASK_ADC_EN_MANUAL                	0x1
#define BIT_CTRL_ADC_EN_MANUAL(x)             	(((x) & BIT_MASK_ADC_EN_MANUAL) << BIT_SHIFT_ADC_EN_MANUAL)

//2 REG_ADC_ANAPAR_AD1

#define BIT_SHIFT_ADC_ANAPAR_AD1 0
#define BIT_MASK_ADC_ANAPAR_AD1 0xffffffffL
#define BIT_ADC_ANAPAR_AD1(x)                 	(((x) & BIT_MASK_ADC_ANAPAR_AD1) << BIT_SHIFT_ADC_ANAPAR_AD1)
#define BIT_CTRL_ADC_ANAPAR_AD1(x)            	(((x) & BIT_MASK_ADC_ANAPAR_AD1) << BIT_SHIFT_ADC_ANAPAR_AD1)
#define BIT_GET_ADC_ANAPAR_AD1(x)             	(((x) >> BIT_SHIFT_ADC_ANAPAR_AD1) & BIT_MASK_ADC_ANAPAR_AD1)

//2 REG_ADC_ANAPAR_AD2

#define BIT_SHIFT_ADC_ANAPAR_AD2 0
#define BIT_MASK_ADC_ANAPAR_AD2 0xffffffffL
#define BIT_ADC_ANAPAR_AD2(x)                 	(((x) & BIT_MASK_ADC_ANAPAR_AD2) << BIT_SHIFT_ADC_ANAPAR_AD2)
#define BIT_CTRL_ADC_ANAPAR_AD2(x)            	(((x) & BIT_MASK_ADC_ANAPAR_AD2) << BIT_SHIFT_ADC_ANAPAR_AD2)
#define BIT_GET_ADC_ANAPAR_AD2(x)             	(((x) >> BIT_SHIFT_ADC_ANAPAR_AD2) & BIT_MASK_ADC_ANAPAR_AD2)

//2 REG_ADC_ANAPAR_AD3

#define BIT_SHIFT_ADC_ANAPAR_AD3 0
#define BIT_MASK_ADC_ANAPAR_AD3 0xffffffffL
#define BIT_ADC_ANAPAR_AD3(x)                 	(((x) & BIT_MASK_ADC_ANAPAR_AD3) << BIT_SHIFT_ADC_ANAPAR_AD3)
#define BIT_CTRL_ADC_ANAPAR_AD3(x)            	(((x) & BIT_MASK_ADC_ANAPAR_AD3) << BIT_SHIFT_ADC_ANAPAR_AD3)
#define BIT_GET_ADC_ANAPAR_AD3(x)             	(((x) >> BIT_SHIFT_ADC_ANAPAR_AD3) & BIT_MASK_ADC_ANAPAR_AD3)

//2 REG_ADC_ANAPAR_AD4

#define BIT_SHIFT_ADC_ANAPAR_AD4 0
#define BIT_MASK_ADC_ANAPAR_AD4 0xffffffffL
#define BIT_ADC_ANAPAR_AD4(x)                 	(((x) & BIT_MASK_ADC_ANAPAR_AD4) << BIT_SHIFT_ADC_ANAPAR_AD4)
#define BIT_CTRL_ADC_ANAPAR_AD4(x)            	(((x) & BIT_MASK_ADC_ANAPAR_AD4) << BIT_SHIFT_ADC_ANAPAR_AD4)
#define BIT_GET_ADC_ANAPAR_AD4(x)             	(((x) >> BIT_SHIFT_ADC_ANAPAR_AD4) & BIT_MASK_ADC_ANAPAR_AD4)

//2 REG_ADC_ANAPAR_AD5

#define BIT_SHIFT_ADC_ANAPAR_AD5 0
#define BIT_MASK_ADC_ANAPAR_AD5 0xffffffffL
#define BIT_ADC_ANAPAR_AD5(x)                 	(((x) & BIT_MASK_ADC_ANAPAR_AD5) << BIT_SHIFT_ADC_ANAPAR_AD5)
#define BIT_CTRL_ADC_ANAPAR_AD5(x)            	(((x) & BIT_MASK_ADC_ANAPAR_AD5) << BIT_SHIFT_ADC_ANAPAR_AD5)
#define BIT_GET_ADC_ANAPAR_AD5(x)             	(((x) >> BIT_SHIFT_ADC_ANAPAR_AD5) & BIT_MASK_ADC_ANAPAR_AD5)

//2 REG_ADC_CALI_DATA

#define BIT_SHIFT_ADC_CALI_DATA_6 16
#define BIT_MASK_ADC_CALI_DATA_6 0xffff
#define BIT_ADC_CALI_DATA_6(x)                	(((x) & BIT_MASK_ADC_CALI_DATA_6) << BIT_SHIFT_ADC_CALI_DATA_6)
#define BIT_CTRL_ADC_CALI_DATA_6(x)           	(((x) & BIT_MASK_ADC_CALI_DATA_6) << BIT_SHIFT_ADC_CALI_DATA_6)
#define BIT_GET_ADC_CALI_DATA_6(x)            	(((x) >> BIT_SHIFT_ADC_CALI_DATA_6) & BIT_MASK_ADC_CALI_DATA_6)

#define BIT_SHIFT_ADC_CALI_DATA_0 0
#define BIT_MASK_ADC_CALI_DATA_0 0xffff
#define BIT_ADC_CALI_DATA_0(x)                	(((x) & BIT_MASK_ADC_CALI_DATA_0) << BIT_SHIFT_ADC_CALI_DATA_0)
#define BIT_CTRL_ADC_CALI_DATA_0(x)           	(((x) & BIT_MASK_ADC_CALI_DATA_0) << BIT_SHIFT_ADC_CALI_DATA_0)
#define BIT_GET_ADC_CALI_DATA_0(x)            	(((x) >> BIT_SHIFT_ADC_CALI_DATA_0) & BIT_MASK_ADC_CALI_DATA_0)

//================ Register Reg Field  =========================


//================ ADC HAL related enumeration ==================

//================ ADC Function Prototypes  =====================
#define HAL_ADC_WRITE32(addr, value)    HAL_WRITE32(ADC_REG_BASE,addr,value)
#define HAL_ADC_READ32(addr)            HAL_READ32(ADC_REG_BASE,addr)

RTK_STATUS HalADCInit8195a(IN VOID *Data);
RTK_STATUS HalADCDeInit8195a(IN VOID *Data);
RTK_STATUS HalADCEnableRtl8195a(IN VOID *Data);
RTK_STATUS HalADCIntrCtrl8195a(IN VOID *Data);
u32 HalADCReceiveRtl8195a(IN VOID *Data);
u32 HalADCReadRegRtl8195a(IN VOID *Data,IN u8 I2CReg);

//================ ADC Configuration  =========================
#define ADC_INTR_OP_TYPE    1
#define ADC_DMA_OP_TYPE     1

// ADC SAL management macros
#define SAL_ADC_USER_CB_NUM     (sizeof(SAL_ADC_USER_CB) / sizeof(PSAL_ADC_USERCB_ADPT))

// ADC used module.
// Please set the ADC module flag to 1 to enable the related
#define ADC0_USED                   1
#define ADC1_USED                   1
#define ADC2_USED                   1
#define ADC3_USED                   1

//================ Debug MSG Definition =======================
#define ADC_PREFIX      "RTL8195A[adc]: "
#define ADC_PREFIX_LVL  "    [ADC_DBG]: "

typedef enum _ADC_DBG_LVL_
{
  HAL_ADC_LVL = 0x01,
  SAL_ADC_LVL = 0x02,
  VERI_ADC_LVL = 0x04,
} ADC_DBG_LVL, *PADC_DBG_LVL;

#ifdef CONFIG_DEBUG_LOG
#ifdef CONFIG_DEBUG_LOG_ADC_HAL

#define DBG_8195A_ADC(...)  do{ \
        _DbgDump("\r"ADC_PREFIX __VA_ARGS__);\
    }while(0)

#define ADCDBGLVL   0xFF
#define DBG_8195A_ADC_LVL(LVL,...)  do{\
            if (LVL&ADCDBGLVL){\
                _DbgDump("\r"ADC_PREFIX_LVL __VA_ARGS__);\
            }\
    }while(0)
#else
#define DBG_ADC_LOG_PERD    100
#define DBG_8195A_ADC(...)
#define DBG_8195A_ADC_LVL(...)
#endif
#endif

//================ ADC HAL Related Enumeration ==================
// ADC Module Selection
typedef enum _ADC_MODULE_SEL_
{
  ADC0_SEL = 0x0,
  ADC1_SEL = 0x1,
  ADC2_SEL = 0x2,
  ADC3_SEL = 0x3,
} ADC_MODULE_SEL, *PADC_MODULE_SEL;

// ADC module status
typedef enum _ADC_MODULE_STATUS_
{
  ADC_DISABLE = 0x0,
  ADC_ENABLE = 0x1,
} ADC_MODULE_STATUS, *PADC_MODULE_STATUS;

// ADC Data Endian
typedef enum _ADC_DATA_ENDIAN_
{
  ADC_DATA_ENDIAN_LITTLE = 0x0,
  ADC_DATA_ENDIAN_BIG = 0x1,
} ADC_DATA_ENDIAN, *PADC_DATA_ENDIAN;

// ADC Debug Select
typedef enum _ADC_DEBUG_SEL_
{
  ADC_DBG_SEL_DISABLE = 0x0,
  ADC_DBG_SEL_ENABLE = 0x1,
} ADC_DEBUG_SEL, *PADC_DEBUG_SEL;

typedef enum _ADC_COMPARE_SET_
{
  ADC_COMP_SMALLER_THAN = 0x0,
  ADC_COMP_GREATER_THAN = 0x1,
} ADC_COMPARE_SET, *PADC_COMPARE_SET;

// ADC feature status
typedef enum _ADC_FEATURE_STATUS_
{
  ADC_FEATURE_DISABLED = 0,
  ADC_FEATURE_ENABLED = 1,
} ADC_FEATURE_STATUS, *PADC_FEATURE_STATUS;

// ADC operation type
typedef enum _ADC_OP_TYPE_
{
  ADC_RDREG_TYPE = 0x0,
  ADC_DMA_TYPE = 0x1,
  ADC_INTR_TYPE = 0x2,
} ADC_OP_TYPE, *PADC_OP_TYPE;

// ADC device status
typedef enum _ADC_DEVICE_STATUS_
{
  ADC_STS_UNINITIAL = 0x00,
  ADC_STS_INITIALIZED = 0x01,
  ADC_STS_IDLE = 0x02,

  ADC_STS_TX_READY = 0x03,
  ADC_STS_TX_ING = 0x04,

  ADC_STS_RX_READY = 0x05,
  ADC_STS_RX_ING = 0x06,

  ADC_STS_ERROR = 0x07,
  ADC_STS_FULL = 0x08,
} ADC_DEVICE_STATUS, *PADC_DEVICE_STATUS;

// ADC error type
typedef enum _ADC_ERR_TYPE_
{
  ADC_ERR_FIFO_RD_ERROR = 0x40,       //ADC FIFO read error
} ADC_ERR_TYPE, *PADC_ERR_TYPE;

// ADC initial status
typedef enum _ADC_INITAIL_STATUS_
{
  ADC0_INITED = 0x1,
  ADC1_INITED = 0x2,
  ADC2_INITED = 0x4,
  ADC3_INITED = 0x8,
} ADC_INITAIL_STATUS, *PADC_INITAIL_STATUS;

//================ ADC HAL Data Structure ======================
// ADC HAL initial data structure
typedef struct _HAL_ADC_INIT_DAT_
{
  u8 ADCIdx;         //ADC index used
  u8 ADCEn;          //ADC module enable
  u8 ADCEndian;      //ADC endian selection,
                     //but actually it's for 32-bit ADC data swap control
                     //1'b0: no swap,
                     //1'b1: swap the upper 16-bit and the lower 16-bit
  u8 ADCBurstSz;     //ADC DMA operation threshold

  u8 ADCCompOnly;    //ADC compare mode only enable (without FIFO enable)
  u8 ADCOneShotEn;   //ADC one-shot mode enable
  u8 ADCOverWREn;    //ADC overwrite mode enable
  u8 ADCOneShotTD;   //ADC one shot mode threshold

  u16 ADCCompCtrl;    //ADC compare mode control,
                      //1'b0:less than the compare threshold
                      //1'b1:greater than the compare threshod
  u16 ADCCompTD;      //ADC compare mode threshold

  u8 ADCDataRate;    //ADC down sample data rate,
  u8 ADCAudioEn;     //ADC audio mode enable
  u8 ADCEnManul;     //ADC enable manually
  u8 ADCDbgSel;

  u32 RSVD0;

  u32 *ADCData;       //ADC data pointer
  u32 ADCPWCtrl;      //ADC0 power control
  u32 ADCIntrMSK;     //ADC Interrupt Mask
  u32 ADCAnaParAd3;   //ADC analog parameter 3
  u32 ADCInInput;     //ADC Input is internal?
} HAL_ADC_INIT_DAT, *PHAL_ADC_INIT_DAT;

// ADC HAL Operations
typedef struct _HAL_ADC_OP_
{
  RTK_STATUS (*HalADCInit)( VOID *Data );   //HAL ADC initialization
  RTK_STATUS (*HalADCDeInit)( VOID *Data );   //HAL ADC de-initialization
  RTK_STATUS (*HalADCEnable)( VOID *Data );   //HAL ADC de-initialization
  u32 (*HalADCReceive)( VOID *Data );   //HAL ADC receive
  RTK_STATUS (*HalADCIntrCtrl)( VOID *Data );   //HAL ADC interrupt control
  u32 (*HalADCReadReg)( VOID *Data, u8 ADCReg );   //HAL ADC read register
} HAL_ADC_OP, *PHAL_ADC_OP;

// ADC user callback adapter
typedef struct _SAL_ADC_USERCB_ADPT_
{
  VOID (*USERCB)( VOID *Data );
  u32 USERData;
} SAL_ADC_USERCB_ADPT, *PSAL_ADC_USERCB_ADPT;

// ADC user callback structure
typedef struct _SAL_ADC_USER_CB_
{
  PSAL_ADC_USERCB_ADPT pTXCB;          //ADC Transmit Callback
  PSAL_ADC_USERCB_ADPT pTXCCB;         //ADC Transmit Complete Callback
  PSAL_ADC_USERCB_ADPT pRXCB;          //ADC Receive Callback
  PSAL_ADC_USERCB_ADPT pRXCCB;         //ADC Receive Complete Callback
  PSAL_ADC_USERCB_ADPT pRDREQCB;       //ADC Read Request Callback
  PSAL_ADC_USERCB_ADPT pERRCB;         //ADC Error Callback
  PSAL_ADC_USERCB_ADPT pDMATXCB;       //ADC DMA Transmit Callback
  PSAL_ADC_USERCB_ADPT pDMATXCCB;      //ADC DMA Transmit Complete Callback
  PSAL_ADC_USERCB_ADPT pDMARXCB;       //ADC DMA Receive Callback
  PSAL_ADC_USERCB_ADPT pDMARXCCB;      //ADC DMA Receive Complete Callback
} SAL_ADC_USER_CB, *PSAL_ADC_USER_CB;

// ADC Transmit Buffer
typedef struct _SAL_ADC_TRANSFER_BUF_
{
  u32 DataLen;                        //ADC Transmfer Length
  u32 *pDataBuf;                      //ADC Transfer Buffer Pointer
  u32 RSVD;                           //
} SAL_ADC_TRANSFER_BUF, *PSAL_ADC_TRANSFER_BUF;

typedef struct _SAL_ADC_DMA_USER_DEF_
{

  u8 TxDatSrcWdth;
  u8 TxDatDstWdth;
  u8 TxDatSrcBstSz;
  u8 TxDatDstBstSz;

  u8 TxChNo;
  u8 LlpCtrl;
  u16 RSVD0;

  u32 MaxMultiBlk;
  u32 pLlix;
  u32 pBlockSizeList;
} SAL_ADC_DMA_USER_DEF, *PSAL_ADC_DMA_USER_DEF;

// Software API Level ADC Handler
typedef struct _SAL_ADC_HND_
{
  u8 DevNum;             //ADC device number
  u8 PinMux;             //ADC pin mux seletion
  u8 OpType;             //ADC operation type selection
  volatile u8 DevSts;             //ADC device status

  u32 ADCExd;             //ADC extended options:
                          //bit 0: example
                          //bit 31~bit 1: Reserved
  u32 ErrType;            //
  u32 TimeOut;            //ADC IO Timeout count

  PHAL_ADC_INIT_DAT pInitDat;           //Pointer to ADC initial data struct
  PSAL_ADC_TRANSFER_BUF pRXBuf;             //Pointer to ADC TX buffer
  PSAL_ADC_USER_CB pUserCB;            //Pointer to ADC User Callback
} SAL_ADC_HND, *PSAL_ADC_HND;

// ADC SAL handle private
typedef struct _SAL_ADC_HND_PRIV_
{
  VOID **ppSalADCHnd;              //Pointer to SAL_ADC_HND pointer
  SAL_ADC_HND SalADCHndPriv;              //Private SAL_ADC_HND
} SAL_ADC_HND_PRIV, *PSAL_ADC_HND_PRIV;

//ADC SAL management adapter
typedef struct _SAL_ADC_MNGT_ADPT_
{
  PSAL_ADC_HND_PRIV pSalHndPriv;        //Pointer to SAL_ADC_HND
  PHAL_ADC_INIT_DAT pHalInitDat;        //Pointer to HAL ADC initial data( HAL_ADC_INIT_DAT )
  PHAL_ADC_OP pHalOp;             //Pointer to HAL ADC operation( HAL_ADC_OP )
  VOID (*pHalOpInit)( VOID* );             //Pointer to HAL ADC initialize function

  PIRQ_HANDLE pIrqHnd;            //Pointer to IRQ handler in SAL layer( IRQ_HANDLE )
  VOID (*pSalIrqFunc)( VOID* );      //Used for SAL ADC interrupt function

  PSAL_ADC_DMA_USER_DEF pDMAConf;                   //Pointer to DAC User Define DMA config
  PHAL_GDMA_ADAPTER pHalGdmaAdp;
  PHAL_GDMA_OP pHalGdmaOp;
  PIRQ_HANDLE pIrqGdmaHnd;
  VOID (*pHalGdmaOpInit)( VOID* );   //Pointer to HAL DAC initialize function
  PSAL_ADC_USER_CB pUserCB;                    //Pointer to SAL user callbacks (SAL_ADC_USER_CB )
  VOID (*pSalDMAIrqFunc)( VOID* );   //Used for SAL DAC interrupt function
} SAL_ADC_MNGT_ADPT, *PSAL_ADC_MNGT_ADPT;

//================ ADC HAL Function Prototype ===================
// ADC HAL inline function
// For checking I2C input index valid or not
static inline RTK_STATUS
RtkADCIdxChk(
    IN u8 ADCIdx
)
{
#if !ADC0_USED
  if (ADCIdx == ADC0_SEL)
  return _EXIT_FAILURE;
#endif

#if !ADC1_USED
  if (ADCIdx == ADC1_SEL)
  return _EXIT_FAILURE;
#endif

#if !ADC2_USED
  if (ADCIdx == ADC2_SEL)
  return _EXIT_FAILURE;
#endif

#if !ADC3_USED
  if (ADCIdx == ADC3_SEL)
  return _EXIT_FAILURE;
#endif
  ADCIdx++; //for compile warning.
  return _EXIT_SUCCESS;
}

VOID HalADCOpInit(IN VOID *Data);
PSAL_ADC_HND RtkADCGetSalHnd(IN u8 DACIdx);
RTK_STATUS RtkADCFreeSalHnd(IN PSAL_ADC_HND pSalADCHND);
RTK_STATUS RtkADCLoadDefault(IN VOID *Data);
RTK_STATUS RtkADCInit(IN VOID *Data);
RTK_STATUS RtkADCDeInit(IN VOID *Data);
//RTK_STATUS RtkADCReceive(IN  VOID *Data);
u32 RtkADCReceive(IN VOID *Data);
u32 RtkADCReceiveBuf(IN VOID *Data,IN u32 *pBuf);
u32 RtkADCRxManualRotate(IN VOID *Data,IN u32 *pBuf);

PSAL_ADC_MNGT_ADPT RtkADCGetMngtAdpt(IN u8 ADCIdx);
RTK_STATUS RtkADCFreeMngtAdpt(IN PSAL_ADC_MNGT_ADPT pSalADCMngtAdpt);
VOID ADCISRHandle(IN VOID *Data);
VOID ADCGDMAISRHandle(IN VOID *Data);
HAL_STATUS RtkADCDisablePS(IN VOID *Data);
HAL_STATUS RtkADCEnablePS(IN VOID *Data);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RTL8195AM_ADC_H__ */
