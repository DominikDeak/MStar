//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#ifndef _MSBOARD_H_
#define _MSBOARD_H_

#define BOARD_NAME                              "BD_MST082B_10AJQ_MONET_HTV"
#define CUS_IR_HEAD_FILE                        "IR_HERAN.h"

//=============================================================================
#define PIN_SPI_CZ1                             BALL_V18
#define PIN_SPI_CZ2                             0
#define PIN_SPI_CZ3                             0
#define PIN_FLASH_WP0                           0
#define PIN_FLASH_WP1                           0

//=============================================================================
#define CONFIG_PADMUX_MODE0                     0x00
#define CONFIG_PADMUX_MODE1                     0x01
#define CONFIG_PADMUX_MODE2                     0x02
#define CONFIG_PADMUX_MODE3                     0x03
#define CONFIG_PADMUX_MODE4                     0x04
#define CONFIG_PADMUX_MODE5                     0x05
#define CONFIG_PADMUX_MODE6                     0x06
#define CONFIG_PADMUX_MODE7                     0x07
#define CONFIG_PADMUX_MODE8                     0x08
#define CONFIG_PADMUX_MODE9                     0x09
#define CONFIG_PADMUX_UNKNOWN                   0xFF

//=============================================================================
#if defined(CONFIG_NAND_FLASH)
#define PADS_NAND_MODE                          CONFIG_PADMUX_MODE1     //Option: CONFIG_PADMUX_MODE1 / DISABLE
#define PADS_NAND_PE                            ENABLE                  //Option: ENABLE / DISABLE
#define PADS_NAND_CS1_EN                        DISABLE                 //Option: ENABLE / DISABLE
#define PADS_EMMC_MODE                          DISABLE                 //Option: CONFIG_PADMUX_MODE1 / DISABLE
#define PADS_EMMC_PE                            DISABLE                 //Option: ENABLE / DISABLE
#define PADS_EMMC_RSTN_EN                       DISABLE                 //Option: ENABLE / DISABLE
#elif defined(CONFIG_MMC)
#define PADS_NAND_MODE                          DISABLE                 //Option: CONFIG_PADMUX_MODE1 / DISABLE
#define PADS_NAND_PE                            DISABLE                 //Option: ENABLE / DISABLE
#define PADS_NAND_CS1_EN                        DISABLE                 //Option: ENABLE / DISABLE
#define PADS_EMMC_MODE                          CONFIG_PADMUX_MODE1     //Option: CONFIG_PADMUX_MODE1 / DISABLE
#define PADS_EMMC_PE                            ENABLE                  //Option: ENABLE / DISABLE
#define PADS_EMMC_RSTN_EN                       ENABLE                  //Option: ENABLE / DISABLE
#else
#define PADS_NAND_MODE                          DISABLE                 //Option: CONFIG_PADMUX_MODE1 / DISABLE
#define PADS_EMMC_MODE                          DISABLE                 //Option: CONFIG_PADMUX_MODE1 / DISABLE
#endif

#define PADS_JTAG_MODE                          DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / DISABLE
#define PADS_VSYNC_VIF_OUT_EN                   DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TS0_CONFIG                         CONFIG_PADMUX_MODE2     //Option: CONFIG_PADMUX_MODE1: PARALLEL_IN
                                                                        //        CONFIG_PADMUX_MODE2: SERIAL_IN
                                                                        //        CONFIG_PADMUX_MODE3: M-CARD SPI
                                                                        //        CONFIG_PADMUX_MODE4: SERIAL_IN (3-WIRD)
                                                                        //        CONFIG_PADMUX_UNKNOWN

#define PADS_TS0_PE                             DISABLE                 //Option: ENABLE / DISABLE

#define PADS_SPDIF_OUT                          ENABLE                  //Option: ENABLE / DISABLE
#define PADS_SPDIF_IN                           DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / DISABLE
#define PADS_I2S_MUTE                           DISABLE                 //Option: ENABLE / DISABLE
#define PADS_I2S_OUT                            DISABLE//ENABLE                  //Option: ENABLE / DISABLE
#define PADS_I2S_OUT_DATA                       DISABLE//ENABLE                  //Option: ENABLE / DISABLE

#define PADS_ET_MODE                            DISABLE                 //Option: ENABLE / DISABLE
#define PADS_LED_MODE                           DISABLE                 //Option: ENABLE (PAD_I2S_OUT Mode) / DISABLE (PAD_LED Mode)
#define PADS_VSYNC_LIKE_MODE                    DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE

#define PADS_LD_SPI1                            DISABLE                 //Option: ENABLE / DISABLE
#define PADS_LD_SPI2                            DISABLE                 //Option: ENABLE / DISABLE
#define PADS_LD_SPI3                            DISABLE                 //Option: ENABLE / DISABLE
#define PADS_DIM_MODE                           DISABLE                 //Option: ENABLE / DISABLE

#define PADS_UART2_MODE                         DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_UART3_MODE                         DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_UART4_MODE                         DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_FAST_UART_MODE                     DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE

#define PADS_OD_UART2_MODE                      DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_OD_UART3_MODE                      DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_OD_UART4_MODE                      DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_OD_FAST_UART_MODE                  DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE

#define PADS_UART0_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_UART1_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_UART2_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_UART3_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_UART4_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_FAST_UART_INV_MODE                 DISABLE                 //Option: ENABLE / DISABLE

#define PADS_UART0_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_UART1_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_UART2_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_UART3_INV_MODE                     DISABLE                 //Option: ENABLE / DISABLE
#define PADS_FAST_UART_INV_MODE                 DISABLE                 //Option: ENABLE / DISABLE

#define PADS_PWM0_MODE                          ENABLE                  //Option: ENABLE / DISABLE
#define PADS_PWM1_MODE                          DISABLE                 //Option: ENABLE / DISABLE
#define PADS_PWM2_MODE                          DISABLE//ENABLE                  //Option: ENABLE / DISABLE
#define PADS_PWM3_MODE                          DISABLE                 //Option: ENABLE / DISABLE
#define PADS_PWM4_MODE                          DISABLE                 //Option: ENABLE / DISABLE

#define PADS_IRE_MODE                           DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_DDCR_MODE                          DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / DISABLE

#define PADS_MIIC_MODE0                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_MIIC_MODE1                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_MIIC_MODE2                         DISABLE                 //Option: ENABLE / DISABLE

#define PADS_TCON0_MODE                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TCON1_MODE                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TCON2_MODE                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TCON3_MODE                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TCON4_MODE                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TCON5_MODE                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TCON6_MODE                         DISABLE                 //Option: ENABLE / DISABLE
#define PADS_TCON7_MODE                         DISABLE                 //Option: ENABLE / DISABLE

#define ENABLE_EXT_GPIO_INT0                    DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_EXT_GPIO_INT1                    DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_EXT_GPIO_INT2                    DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_EXT_GPIO_INT3                    DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_EXT_GPIO_INT4                    DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_EXT_GPIO_INT5                    DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_EXT_GPIO_INT6                    DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_EXT_GPIO_INT7                    DISABLE                 //Option: ENABLE / DISABLE

#define ENABLE_PM51_PORT1_GPIO0                 DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_PM51_PORT1_GPIO1                 DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_PM51_PORT1_GPIO2                 DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_PM51_PORT1_GPIO3                 DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_PM51_PORT1_GPIO4                 DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_PM51_PORT1_GPIO5                 DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_PM51_PORT1_GPIO6                 DISABLE                 //Option: ENABLE / DISABLE
#define ENABLE_PM51_PORT1_GPIO7                 DISABLE                 //Option: ENABLE / DISABLE

#define PADS_SD_MODE                            DISABLE                 //Option: CONFIG_SDIO_MODE0 / CONFIG_SDIO_MODE1 / DISABLE
#define PADS_SDIO_MODE                          DISABLE                 //Option: CONFIG_SDIO_MODE0 / CONFIG_SDIO_MODE1 / DISABLE
#define PADS_SDIO30_MODE                        DISABLE                 //Option: CONFIG_SDIO_MODE0 / CONFIG_SDIO_MODE1 / DISABLE

#define PADS_3D_FLAG_CONFIG                     DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE
#define PADS_OSD3D_FLAG_CONFIG                  DISABLE                 //Option: CONFIG_PADMUX_MODE1 / CONFIG_PADMUX_MODE2 / CONFIG_PADMUX_MODE3 / DISABLE

#define ENABLE_MSPI_MODE                        DISABLE                 //Option: ENABLE / DISABLE

//=============================================================================
#define BALL_V3_IS_GPIO                         GPIO_OUT_HIGH           //POWER_SW (Low: Off / High: On)

#define BALL_G4_IS_GPIO                         GPIO_OUT_LOW            //Panel (Low: Off / High: On)
#define BALL_H5_IS_GPIO                         GPIO_OUT_LOW            //Backlight (Low: Off / High: On)

#define BALL_W5_IS_GPIO                         GPIO_OUT_HIGH           //Mute (Low: Normal / High: Mute)

#define BALL_V5_IS_GPIO                         GPIO_IN                 //SD_CDZ

#define BALL_D4_IS_GPIO                         GPIO_OUT_LOW            //MHL-CB-DET

#define BALL_B3_IS_GPIO                         GPIO_IN                 //IRIN
#define BALL_D8_IS_GPIO                         GPIO_OUT_HIGH           //DDCR_CK: EEPROM I2C_SCL
#define BALL_E8_IS_GPIO                         GPIO_IN                 //DDCR_DA: EEPROM I2C_SDA

#define BALL_Y4_IS_GPIO                         GPIO_OUT_LOW            //3D_EN_CTL

#define BALL_E22_IS_GPIO                        GPIO_OUT_HIGH	        //PWM0: Bright adjusts within panel (Software control)
// EosTek Patch Begin
#define BALL_D23_IS_GPIO                        GPIO_OUT_HIGH	        // PAD_PWM2: TUNER_SWITCH
#define BALL_C23_IS_GPIO                         GPIO_OUT_LOW    // EarPhone Pop (Low: Off / High: On)

#define BALL_C6_IS_GPIO                       GPIO_OUT_LOW   //LED G
#define BALL_H4_IS_GPIO                     GPIO_OUT_HIGH   //LED R
// EosTek Patch End
//=============================================================================
//====================================
// EosTek Patch Begin
#define BALL_B22_IS_GPIO              GPIO_OUT_LOW// PAD_I2S_OUT_MCK  kok_gpio5 TX--Data
#define BALL_C22_IS_GPIO              GPIO_OUT_LOW // PAD_I2S_OUT_SD   kok_gpio6 RX --Clk
// EosTek Patch End
//====================================
#ifdef CONFIG_MSTAR_VID_ENABLE
#define CONFIG_CHIP_PACKAGE                     0                       //Chip Package: 0: BGA / 1: QFP / Otherwise: Reserved

#define PAD_GPIO_PM3_IS_GPIO                    GPIO_OUT_HIGH           //VID0
//#define PAD_GPIO_PM8_IS_GPIO                  GPIO_OUT_HIGH           //VID1

#define CONFIG_SIDD_THRESHOLD_CPU_L0            108                     //0x0000FFFF: Unused
#define CONFIG_SIDD_THRESHOLD_CPU_L1            0xFFFF                  //0x0000FFFF: Unused
#define CONFIG_SIDD_THRESHOLD_CPU_L2            0xFFFF                  //0x0000FFFF: Unused

#define CONFIG_OSC_THRESHOLD_CPU_L0             320                     //0x0000FFFF: Unused
#define CONFIG_OSC_THRESHOLD_CPU_L1             0xFFFF                  //0x0000FFFF: Unused
#define CONFIG_OSC_THRESHOLD_CPU_L2             0xFFFF                  //0x0000FFFF: Unused

#define CONFIG_SIDD_THRESHOLD_CORE_L0           108                     //0x0000FFFF: Unused
#define CONFIG_SIDD_THRESHOLD_CORE_L1           0xFFFF                  //0x0000FFFF: Unused
#define CONFIG_SIDD_THRESHOLD_CORE_L2           0xFFFF                  //0x0000FFFF: Unused

#define CONFIG_OSC_THRESHOLD_CORE_L0            320                     //0x0000FFFF: Unused
#define CONFIG_OSC_THRESHOLD_CORE_L1            0xFFFF                  //0x0000FFFF: Unused
#define CONFIG_OSC_THRESHOLD_CORE_L2            0xFFFF                  //0x0000FFFF: Unused
#endif

//=============================================================================
#include "chip/MSD93J2P.h"

#define USE_SW_I2C                              1
#define USE_SW_I2C_HIGHSPEED                    0

#define I2C_DEV_DATABASE                        ((E_I2C_BUS_SYS << 8) | 0xA4)
#define I2C_DEV_HDCPKEY                         ((E_I2C_BUS_SYS << 8) | 0xA8)
#define I2C_DEV_EDID_A0                         ((E_I2C_BUS_DDCA0 << 8) | 0xA0)
#define I2C_DEV_EDID_D0                         ((E_I2C_BUS_DDCD0 << 8) | 0xA0)
#define I2C_DEV_EDID_D1                         ((E_I2C_BUS_DDCD1 << 8) | 0xA0)
#define I2C_DEV_EDID_D2                         ((E_I2C_BUS_DDCD2 << 8) | 0xA0)

//=============================================================================
#define TUNER_IIC_BUS                           E_I2C_BUS_DDCD0
#define DEMOD_IIC_BUS                           E_I2C_BUS_DDCD0
#define RM_DEVICE_ADR                           I2C_DEV_DATABASE
#define RM_HDCP_ADR                             I2C_DEV_HDCPKEY

//=============================================================================
#define PANEL_TYPE_SEL                          g_PNL_TypeSel   //PNL_AU37_T370HW01_HD //PNL_AU20_T200XW02_WXGA//PNL_LG32_WXGA //PNL_AU19PW01_WXGA//PNL_AU20_T200XW02_WXGA //PNL_LG19_SXGA  //PNL_CMO22_WSXGA  //PNL_AU20_T200XW02_WXGA  // PNL_CMO22_WSXGA  // PNL_AU20_T200XW02_WXGA // PNL_AU17_EN05_SXGA
#define SATURN_FLASH_TYPE                       FLASH_TYPE_SERIAL
#define SATURN_FLASH_IC                         FLASH_IC_MX25L6405D

#define ENABLE_DDC_RAM                          DISABLE
#define RM_EEPROM_TYPE                          RM_TYPE_24C512         // RM_TYPE_24C64

#define DIGITAL_I2S_SELECT                      AUDIO_I2S_NONE

#define INPUT_AV_VIDEO_COUNT                    1
#define INPUT_SV_VIDEO_COUNT                    0
#define INPUT_YPBPR_VIDEO_COUNT                 1

#ifdef ATSC_SYSTEM
#define INPUT_SCART_VIDEO_COUNT                 0
#else
#define INPUT_SCART_VIDEO_COUNT                 0
#endif

#define INPUT_HDMI_VIDEO_COUNT                  3

#ifdef ATSC_SYSTEM
#define ENABLE_SCART_VIDEO                      0
#else
#define ENABLE_SCART_VIDEO                      0
#endif

//=============================================================================
#define INPUT_VGA_MUX                           INPUT_PORT_ANALOG0
#define INPUT_VGA_SYNC_MUX                      INPUT_PORT_ANALOG0_SYNC //SYNC port of VGA. There is a case which data and sync use different port.
#define INPUT_YPBPR_MUX                         INPUT_PORT_ANALOG1
#define INPUT_YPBPR2_MUX                        INPUT_PORT_NONE_PORT
#define INPUT_TV_YMUX                           INPUT_PORT_YMUX_CVBS0
#define INPUT_AV_YMUX                           INPUT_PORT_YMUX_CVBS0
#define INPUT_AV2_YMUX                          INPUT_PORT_NONE_PORT
#define INPUT_AV3_YMUX                          INPUT_PORT_NONE_PORT
#define INPUT_SV_YMUX                           INPUT_PORT_NONE_PORT
#define INPUT_SV_CMUX                           INPUT_PORT_NONE_PORT
#define INPUT_SV2_YMUX                          INPUT_PORT_NONE_PORT
#define INPUT_SV2_CMUX                          INPUT_PORT_NONE_PORT
#define INPUT_SCART_YMUX                        INPUT_PORT_NONE_PORT
#define INPUT_SCART_RGBMUX                      INPUT_PORT_NONE_PORT
#define INPUT_SCART_FB_MUX                      INPUT_PORT_NONE_PORT
#define INPUT_SCART_CMUX                        INPUT_PORT_NONE_PORT
#define INPUT_SCART2_YMUX                       INPUT_PORT_NONE_PORT
#define INPUT_SCART2_RGBMUX                     INPUT_PORT_NONE_PORT
#define INPUT_SCART2_FB_MUX                     INPUT_PORT_NONE_PORT

#define SCART_ID_SEL                            0x02   // HSYNC1
#define SCART2_ID_SEL                           0x04   // HSYNC2

#define INPUT_HDMI1_MUX                         INPUT_PORT_DVI0
#define INPUT_HDMI2_MUX                         INPUT_PORT_DVI1
#define INPUT_HDMI3_MUX                         INPUT_PORT_DVI2
#define PWS_INPUT_HDMI1_PATH                    _HDMI1_
#define PWS_INPUT_HDMI2_PATH                    _HDMI2_
#define PWS_INPUT_HDMI3_PATH                    _HDMI3_

//=============================================================================
#define ENABLE_MHL                              ENABLE
#define MHL_TYPE                                MHL_TYPE_INTERNAL
#define HDMI_PORT_FOR_MHL                       UI_INPUT_SOURCE_HDMI3

//For Support MHL chip
#if (ENABLE_MHL == ENABLE)
#define INPUT_SUPPORT_MHL_PATH                  E_INPUT_SUPPORT_MHL_PORT_DVI2
#else
#define INPUT_SUPPORT_MHL_PATH                  E_INPUT_NOT_SUPPORT_MHL
#endif

//=============================================================================
#define AUDIO_SOURCE_DTV                        AUDIO_DSP1_DVB_INPUT
#define AUDIO_SOURCE_DTV2                       AUDIO_DSP3_DVB_INPUT
#define AUDIO_SOURCE_ATV                        AUDIO_DSP4_SIF_INPUT
#define AUDIO_SOURCE_PC                         AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_YPBPR                      AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_YPBPR2                     AUDIO_NULL_INPUT
#define AUDIO_SOURCE_AV                         AUDIO_AUIN0_INPUT
#define AUDIO_SOURCE_AV2                        AUDIO_NULL_INPUT
#define AUDIO_SOURCE_AV3                        AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SV                         AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SV2                        AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SCART                      AUDIO_NULL_INPUT
#define AUDIO_SOURCE_SCART2                     AUDIO_NULL_INPUT
#define AUDIO_SOURCE_HDMI                       AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI2                      AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI3                      AUDIO_HDMI_INPUT
#define AUDIO_SOURCE_HDMI4                      AUDIO_NULL_INPUT
#define AUDIO_SOURCE_DVI                        AUDIO_SOURCE_PC
#define AUDIO_SOURCE_DVI2                       AUDIO_SOURCE_PC
#define AUDIO_SOURCE_DVI3                       AUDIO_SOURCE_PC
#define AUDIO_SOURCE_DVI4                       AUDIO_NULL_INPUT

#define AUDIO_PATH_MAIN_SPEAKER                 AUDIO_T3_PATH_I2S
#define AUDIO_PATH_HP                           AUDIO_T3_PATH_AUOUT1
#define AUDIO_PATH_LINEOUT                      AUDIO_T3_PATH_AUOUT0
#define AUDIO_PATH_SIFOUT                       AUDIO_T3_PATH_AUOUT2
#define AUDIO_PATH_SCART1                       AUDIO_PATH_SIFOUT
#define AUDIO_PATH_SCART2                       AUDIO_PATH_LINEOUT
#define AUDIO_PATH_SPDIF                        AUDIO_T3_PATH_SPDIF

#define AUDIO_OUTPUT_MAIN_SPEAKER               AUDIO_I2S_OUTPUT
#define AUDIO_OUTPUT_HP                         AUDIO_HP_OUTPUT
#define AUDIO_OUTPUT_LINEOUT                    AUDIO_AUOUT0_OUTPUT
#define AUDIO_OUTPUT_SIFOUT                     AUDIO_AUOUT2_OUTPUT
#define AUDIO_OUTPUT_SCART1                     AUDIO_OUTPUT_SIFOUT
#define AUDIO_OUTPUT_SCART2                     AUDIO_OUTPUT_LINEOUT

//=============================================================================
#define Switch_PC()                             _FUNC_NOT_USED()
#define Switch_YPBPR()                          _FUNC_NOT_USED()
#define Switch_YPBPR2()                         _FUNC_NOT_USED()
#define Switch_AV()                             _FUNC_NOT_USED()
#define Switch_AV2()                            _FUNC_NOT_USED()
#define Switch_AV3()                            _FUNC_NOT_USED()
#define Switch_SV()                             _FUNC_NOT_USED()
#define Switch_SV2()                            _FUNC_NOT_USED()
#define Switch_SCART()                          _FUNC_NOT_USED()
#define Switch_SCART2()                         _FUNC_NOT_USED()
#define Switch_DVI()                            MApi_XC_DVI_SwitchSrc(INPUT_PORT_DVI0)
#define Switch_DVI2()                           MApi_XC_DVI_SwitchSrc(INPUT_PORT_DVI1)
#define Switch_DVI3()                           MApi_XC_DVI_SwitchSrc(INPUT_PORT_DVI2)
#define Switch_DVI4()                           _FUNC_NOT_USED()
#define Switch_DEFAULT()                        _FUNC_NOT_USED()

// HDMI switch Setting
#define HDMI_SWITCH_SELECT                      HDMI_SWITCH_NONE

//===============================================================
#ifdef ATSC_SYSTEM

#define TS_CLK_INV                              0
#define TS_PARALLEL_OUTPUT                      1
#define USE_UTOPIA                              1
#define FRONTEND_DEMOD_TYPE                     EMBEDDED_ATSC_DEMOD //EMBEDDED_ATSC_DEMOD//TOSHIBA_TC90512XBG_DEMOD
#define FRONTEND_TUNER_TYPE                     NXP_TDA18273_TUNER  //SAMSUNG_S205_TUNER////SHARP_VA1G5BF2009_TUNERPHILIPS_TDA1316_TUNER //PHILIPS_FQD1216_TUNER

#define DEMOD_IF_KHz                            5000
#define DEMOD_IQSWAP                            1
#define USE_ATSC_UTOPIA_INTERFACE

#define FRONTEND_IF_MIXER_TYPE                  XUGUANG_T126CWADC   //PHILIPS_FQD1216_TUNER
#define FRONTEND_IF_DEMODE_TYPE                 MSTAR_INTERN_VIF    //MSTAR_INTERN_VIF  //PHILIPS_TDA9886 //MSTAR_VIF_MSB1210   //MSTAR_VIF //PHILIPS_TDA9886

#define VIF_TUNER_TYPE                          1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_SAW_ARCH                            2                   // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF)
#define ATSC_DEMOD_VIF_IN                       1

#else

#define TS_CLK_INV                              0
#define TS_PARALLEL_OUTPUT                      1
#define TS_SERIAL_OUTPUT_IF_CI_REMOVED          0
//#define USE_UTOPIA                              1
#define FRONTEND_DEMOD_TYPE                     EMBEDDED_DVBT_DEMOD //EMBEDDED_DVBT_DEMOD //ZARLINK_ZL10353_DEMODE
#define FRONTEND_TUNER_TYPE                     NUTUNE_FK1602_TUNER //LG_TDTC_G311D_TUNER//PHILIPS_TDA1316_TUNER //PHILIPS_FQD1216_TUNER

#define FRONTEND_IF_MIXER_TYPE                  XUGUANG_T126CWADC   //PHILIPS_FQD1216_TUNER
#define FRONTEND_IF_DEMODE_TYPE                 MSTAR_INTERN_VIF    //MSTAR_INTERN_VIF  //PHILIPS_TDA9886 //MSTAR_VIF_MSB1210   //MSTAR_VIF //PHILIPS_TDA9886

#define VIF_TUNER_TYPE                          1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_SAW_ARCH                            2                   // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF); 6: save_pin_package

#endif

#define FRONTEND_SECOND_DEMOD_TYPE              MSTAR_NONE_DEMOD

//=============================================================================
#define MSB1210_TS_SERIAL_INVERSION                     0
#define MSB1210_TS_PARALLEL_INVERSION                   0
#define MSB1210_DTV_DRIVING_LEVEL                       1 //0 or 1
#define MSB1210_WEAK_SIGNAL_PICTURE_FREEZE_ENABLE       1

#define INTERN_DVBT_TS_SERIAL_INVERSION                 0
#define INTERN_DVBT_TS_PARALLEL_INVERSION               0
#define INTERN_DVBT_DTV_DRIVING_LEVEL                   1
#define INTERN_DVBT_WEAK_SIGNAL_PICTURE_FREEZE_ENABLE   1

#define SECAM_L_PRIME_ON()                      _FUNC_NOT_USED() //GPIO60_SET(1)//_FUNC_NOT_USED()
#define SECAM_L_PRIME_OFF()                     _FUNC_NOT_USED() //GPIO60_SET(0)//_FUNC_NOT_USED()
#define EXT_RF_AGC_ON()                         _FUNC_NOT_USED()// ATV mode: external RF AGC
#define EXT_RF_AGC_OFF()                        _FUNC_NOT_USED()  // DTV mode: internal RF AGC

//=============================================================================
#define IR_TYPE_SEL                             IR_TYPE_MSTAR_DTV   // IR_TYPE_MSTAR_DTV // IR_TYPE_CUS03_DTV // IR_TYPE_NEW
#define KEYPAD_TYPE_SEL                         KEYPAD_TYPE_ORIG    // KEYPAD_TYPE_DEMO
#define POWER_KEY_SEL                           POWER_KEY_PAD_INT

//=============================================================================
#define ENABLE_POWER_SAVING                     0
#define POWER_DOWN_SEQ                          1
#define POWER_SAVING_T                          0
#define SCREENSAVER_ENABLE                      1
#define NO_SIGNAL_AUTO_SHUTDOWN                 1
#define STANDBY_MODE                            POWERMODE_S3
#define POWERUP_MODE                            PUMODE_WORK
#define ENABLE_POWER_GOOD_DETECT                1
#define ENABLE_POWER_SAVING_SIF                 1
#define ENABLE_POWER_SAVING_VDMVD               0
#define ENABLE_POWER_SAVING_DPMS                0

#define ENABLE_PWS                              0   //Analog IP PWS
#define ENABLE_DIP_PWS                          0   //Digital IP PWS, for U3 only now
#define ENABLE_DIP_MONITOR                      0   //For U3 oly now

//=============================================================================
#define BOOTUP_MIU_BIST                         1
#ifndef MEMORY_MAP
#define MEMORY_MAP                              MMAP_256_256MB//MMAP_64MB
#endif
#define MIU_INTERFACE                           DDR3_INTERFACE_BGA   //DDR3_INTERFACE_BGA / DDR2_INTERFACE_BGA
#define MIU_DRAM_FREQ                           1666 //800 / 1066 / 1333 / 1666

#define MIU1_INTERFACE                          DDR3_INTERFACE_BGA   //DDR3_INTERFACE_BGA / DDR2_INTERFACE_BGA
#define MIU1_DRAM_FREQ                          1666 //800 / 1066 / 1333 / 1666

//=============================================================================
#define MOD_LVDS_GPIO                           0x820
#define SHARE_GND                               ENABLE

#define LVDS_PN_SWAP_L                          0x00
#define LVDS_PN_SWAP_H                          0x00

#define ENABLE_SSC                              DISABLE
#define ENABLE_LVDSTORGB_CONVERTER              DISABLE

#if ENABLE_SSC
#define MIU_SSC_SPAN_DEFAULT                    350
#define MIU_SSC_STEP_DEFAULT                    200
#define MIU_SSC_SPAN_MAX                        500
#define MIU_SSC_STEP_MAX                        300
#define LVDS_SSC_SPAN_DEFAULT                   350
#define LVDS_SSC_STEP_DEFAULT                   200
#define LVDS_SSC_SPAN_MAX                       500
#define LVDS_SSC_STEP_MAX                       300
#endif

//=============================================================================
#define DRAM_TYPE                               DDR_II
#define DRAM_BUS                                DRAM_BUS_16
#define DDRPLL_FREQ                             DDRLLL_FREQ_400
#define DDRII_ODT

#define MIU_0_02                                0x0C45
#define MIU_0_1A                                0x5151
#define MIU_0_36                                0x0244
#define MIU_0_38                                0x0070

//=============================================================================
#define MCU_CLOCK_SEL                           MCUCLK_144MHZ

#define MST_XTAL_CLOCK_HZ                       FREQ_12MHZ
#define MST_XTAL_CLOCK_KHZ                      (MST_XTAL_CLOCK_HZ / 1000UL)
#define MST_XTAL_CLOCK_MHZ                      (MST_XTAL_CLOCK_KHZ / 1000UL)

//=============================================================================-
#define ENABLE_HKMCU_ICACHE_BYPASS              0
#define ENABLE_HKMCU_CODE_ECC                   0

//=============================================================================
#define POWER_DOWN_INFORM_EXTERNALMCU           0

#if POWER_DOWN_INFORM_EXTERNALMCU
#define EXMCU_SLAVE_ADDR                        0xA8
#define EXMCU_SUBADDRESS                        0x04
#define EXMCU_SLEEP_MODE                        0x00
#endif

// ??? This board support HW IIC (TBC)
#define IIC_BY_HW                               0
#define IIC_BY_SW                               1
#define _EEPROM_ACCESS                          IIC_BY_SW   //IIC_BY_HW
#define EEPROM_CLK_SEL                          EEPROM_CLK_100KHZ

//=============================================================================
#define ENABLE_DPWM_FUNCTION                    0

#define SCART_OUT_ON()                          _FUNC_NOT_USED()
#define SCART_OUT_OFF()                         _FUNC_NOT_USED())

// Video switch Setting
#define Switch_YPbPr1()                         _FUNC_NOT_USED()
#define Switch_YPbPr2()                         _FUNC_NOT_USED()

#define SwitchRGBToSCART()                      _FUNC_NOT_USED()
#define SwitchRGBToDSUB()                       _FUNC_NOT_USED()

#define MDrv_Sys_GetUsbOcdN()                   _FUNC_NOT_USED
#define MDrv_Sys_GetRgbSw()

// Audio Amplifier
#define Audio_Amplifier_ON()                    mdrv_gpio_set_low(BALL_W5)
#define Audio_Amplifier_OFF()                   mdrv_gpio_set_high(BALL_W5)

#define Adj_Volume_Off()                        mdrv_gpio_set_high(BALL_W5)
#define Adj_Volume_On()                         mdrv_gpio_set_low(BALL_W5)

//------ PANEL RELATED ---------------------------------------------------------
#define Panel_VCC_ON()                          mdrv_gpio_set_high(BALL_G4)
#define Panel_VCC_OFF()                         mdrv_gpio_set_low(BALL_G4)
#define Panel_Backlight_VCC_ON()                mdrv_gpio_set_high(BALL_H5)
#define Panel_Backlight_VCC_OFF()               mdrv_gpio_set_low(BALL_H5)

#define Panel_Backlight_PWM_ADJ(x)              MDrv_PWM_DutyCycle(E_PWM_CH0, x)
#define Panel_Backlight_Max_Current(x)          MDrv_PWM_DutyCycle(E_PWM_CH0, x)

#define Panel_VG_HL_CTL_ON()                    _FUNC_NOT_USED()
#define Panel_VG_HL_CTL_OFF()                   _FUNC_NOT_USED()
#define PANEL_CONNECTOR_SWAP_LVDS_CH            0
#define PANEL_CONNECTOR_SWAP_LVDS_POL           1

#define PANEL_PDP_10BIT                         1
#define PANEL_CONNECTOR_SWAP_PORT               1
#define PANEL_SWAP_LVDS_POL                     0

// PCMCIA power control
#define PCMCIA_VCC_ON()                         _FUNC_NOT_USED()
#define PCMCIA_VCC_OFF()                        _FUNC_NOT_USED()

// Power Saving
#define Power_On()                              _FUNC_NOT_USED()
#define Power_Off()                             _FUNC_NOT_USED()
#define MDrv_Sys_GetSvideoSw()                  _FUNC_NOT_USED()

#define Peripheral_Device_Reset_ON()            _FUNC_NOT_USED()
#define Peripheral_Device_Reset_OFF()           _FUNC_NOT_USED()
#define Tuner_ON()                              _FUNC_NOT_USED()
#define Tuner_OFF()                             _FUNC_NOT_USED()
#define Demodulator_ON()                        _FUNC_NOT_USED()
#define Demodulator_OFF()                       _FUNC_NOT_USED()
#define LAN_ON()                                _FUNC_NOT_USED()
#define LAN_OFF()                               _FUNC_NOT_USED()

#define TunerOffPCMCIA()                        PCMCIA_VCC_OFF()
#define TunerOnPCMCIA()                         PCMCIA_VCC_ON()

// LED Control
#define LED_RED_ON()                            mdrv_gpio_set_high(BALL_H4)
#define LED_RED_OFF()                           mdrv_gpio_set_low(BALL_H4)
#define LED_GREEN_ON()                          mdrv_gpio_set_high(BALL_C6)
#define LED_GREEN_OFF()                         mdrv_gpio_set_low(BALL_C6)

#define ST_DET_Read()                           0
#define ANT_5V_MNT_Read()                       0
#define TU_ERROR_N_Read()                       0
#define HDMI_5V_Read()                          0
#define COMP_SW_Read()                          1
#define PANEL_CTL_Off()                         Panel_VCC_OFF()
#define PANEL_CTL_On()                          Panel_VCC_ON()
#define INV_CTL_Off()                           Panel_Backlight_VCC_OFF()
#define INV_CTL_On()                            Panel_Backlight_VCC_ON()
#define POWER_ON_OFF1_On()                      Power_On()
#define POWER_ON_OFF1_Off()                     Power_Off()
#define MUTE_On()                               Adj_Volume_Off()    //(XBYTE[0x1e63] |= BIT7)
#define MUTE_Off()                              Adj_Volume_On()     //(XBYTE[0x1e63] &= ~BIT7)
#define EEPROM_WP_On()                          _FUNC_NOT_USED()
#define EEPROM_WP_Off()                         _FUNC_NOT_USED()
#define LED_GRN_Off()                           LED_GREEN_OFF()
#define LED_GRN_On()                            LED_GREEN_ON()
#define LED_RED_Off()                           LED_GRN_On()
#define LED_RED_On()                            LED_GRN_Off()
#define ANT_5V_CTL_Off()                        _FUNC_NOT_USED()
#define ANT_5V_CTL_On()                         _FUNC_NOT_USED()
#define BOOSTER_Off()                           _FUNC_NOT_USED()
#define BOOSTER_On()                            _FUNC_NOT_USED()
#define RGB_SW_On()                             _FUNC_NOT_USED()
#define RGB_SW_Off()                            _FUNC_NOT_USED()
#define SC_RE1_On()                             _FUNC_NOT_USED()
#define SC_RE1_Off()                            _FUNC_NOT_USED()
#define SC_RE2_On()                             _FUNC_NOT_USED()
#define SC_RE2_Off()                            _FUNC_NOT_USED()
#define TU_RESET_N_On()                         _FUNC_NOT_USED()    //mdrv_gpio_set_high(BALL_P4)
#define TU_RESET_N_Off()                        _FUNC_NOT_USED()    //mdrv_gpio_set_low(BALL_P4)
#define DeactivateScartRecord1()                _FUNC_NOT_USED()    //SetGPIOHigh(SC_RE1)
#define ActivateScartRecord1()                  _FUNC_NOT_USED()    //SetGPIOLow(SC_RE1)
#define DeactivateScartRecord2()                _FUNC_NOT_USED()    //SetGPIOHigh(SC_RE2)
#define ActivateScartRecord2()                  _FUNC_NOT_USED()    //SetGPIOLow(SC_RE2)

//------MST Keypad definition---------------------------------------------------
#define KEYPAD_CHANNEL_SUPPORT                  4 //Maximun supported keypad channels
#define ADC_KEY_CHANNEL_NUM                     2 //Real supported keypad channels
#define ADC_KEY_LAST_CHANNEL                    ADC_KEY_CHANNEL_NUM - 1

//config which keypad channel enabled
#define ENABLE_KPDCHAN_1                        ENABLE
#define ENABLE_KPDCHAN_2                        DISABLE
#define ENABLE_KPDCHAN_3                        DISABLE
#define ENABLE_KPDCHAN_4                        DISABLE

#define KEYPAD_KEY_VALIDATION                   3
#define KEYPAD_REPEAT_KEY_CHECK                 KEYPAD_KEY_VALIDATION + 2
#define KEYPAD_REPEAT_KEY_CHECK_1               KEYPAD_KEY_VALIDATION + 3
#define KEYPAD_STABLE_NUM                       10
#define KEYPAD_STABLE_NUM_MIN                   9
#define KEYPAD_REPEAT_PERIOD                    2 // 6
#define KEYPAD_REPEAT_PERIOD_1                  KEYPAD_REPEAT_PERIOD/2

//------------------------------------------------------------------------------
// SAR boundary define
//------------------------------------------------------------------------------
#define KEYPAD_CH1_UB                           0xFF
#define KEYPAD_CH1_LB                           0xD0
#define KEYPAD_CH2_UB                           0xFF
#define KEYPAD_CH2_LB                           0xD0
#define KEYPAD_CH3_UB                           0xFF
#define KEYPAD_CH3_LB                           0xD0
#define KEYPAD_CH4_UB                           0xFF
#define KEYPAD_CH4_LB                           0xD0

#define ADC_KEY_LEVEL                           4
#define ADC_KEY_L0                              0x12
#define ADC_KEY_L1                              0x36
#define ADC_KEY_L2                              0x56
#define ADC_KEY_L3                              0x7B
#define ADC_KEY_L4                              0x92
#define ADC_KEY_L5                              0xAB
#define ADC_KEY_L6                              0xC3
#define ADC_KEY_L7                              0xE7
#define ADC_KEY_LEVEL_MAX                       ADC_KEY_L7

//### Currently Only Support 2 keypad Channels
//### Support un-balanced levels for each channel by spec. requirement
#define ADC_CH1_LEVELS                          4       //### must be <= ADC_KEY_LEVEL
#define ADC_CH2_LEVELS                          4       //### must be <= ADC_KEY_LEVEL
#define ADC_CH3_LEVELS                          4       //### must be <= ADC_KEY_LEVEL
#define ADC_CH4_LEVELS                          4       //### must be <= ADC_KEY_LEVEL

#define ADC_KEY_1_L0                            0x10//0x22    //0x27
#define ADC_KEY_1_L1                            0x2F//0x5A    //0x47
#define ADC_KEY_1_L2                            0x4D//0x81    //0x63
#define ADC_KEY_1_L3                            0x71//0xC9    //0x7B
#define ADC_KEY_1_L4                            0x92//0x00    //RFU
#define ADC_KEY_1_L5                            0xAB//0x00    //RFU
#define ADC_KEY_1_L6                            0xC3//0x00    //RFU
#define ADC_KEY_1_L7                            0xE7//0x00    //RFU

#define ADC_KEY_2_L0                            0x22//0x30    //0x27
#define ADC_KEY_2_L1                            0x5A//0x60    //0x47
#define ADC_KEY_2_L2                            0x81//0x90    //0x63
#define ADC_KEY_2_L3                            0xC9//0xBF    //0x7B
#define ADC_KEY_2_L4                            0x00    //RFU
#define ADC_KEY_2_L5                            0x00    //RFU
#define ADC_KEY_2_L6                            0x00    //RFU
#define ADC_KEY_2_L7                            0x00    //RFU

#if (KEYPAD_TYPE_SEL == KEYPAD_TYPE_ORIG) // MStar normal keypad
#define ADC_KEY_1_L0_FLAG                       IRKEY_POWER  //IRKEY_UP
#define ADC_KEY_1_L1_FLAG                       IRKEY_CHANNEL_PLUS
#define ADC_KEY_1_L2_FLAG                       IRKEY_CHANNEL_MINUS
#define ADC_KEY_1_L3_FLAG                       IRKEY_VOLUME_PLUS
#define ADC_KEY_1_L4_FLAG                       IRKEY_VOLUME_MINUS  //RFU
#define ADC_KEY_1_L5_FLAG                       IRKEY_SELECT  //RFU
#define ADC_KEY_1_L6_FLAG                       IRKEY_INPUT_SOURCE  //RFU
#define ADC_KEY_1_L7_FLAG                       IRKEY_MENU  //RFU

#define ADC_KEY_2_L0_FLAG                       IRKEY_POWER
#define ADC_KEY_2_L1_FLAG                       IRKEY_INPUT_SOURCE
#define ADC_KEY_2_L2_FLAG                       IRKEY_RIGHT
#define ADC_KEY_2_L3_FLAG                       IRKEY_DOWN
#define ADC_KEY_2_L4_FLAG                       IRKEY_DUMY  //RFU
#define ADC_KEY_2_L5_FLAG                       IRKEY_DUMY  //RFU
#define ADC_KEY_2_L6_FLAG                       IRKEY_DUMY  //RFU
#define ADC_KEY_2_L7_FLAG                       IRKEY_DUMY  //RFU
#endif

//------------------------------------------------------------------------------
// SAR boundary define
//------------------------------------------------------------------------------
#define LK_KEYPAD_CH1_UB                        0x3F
#define LK_KEYPAD_CH1_LB                        0x1A
#define LK_KEYPAD_CH2_UB                        0x3F
#define LK_KEYPAD_CH2_LB                        0x1A
#define LK_KEYPAD_CH3_UB                        0x3F
#define LK_KEYPAD_CH3_LB                        0x00
#define LK_KEYPAD_CH4_UB                        0x3F
#define LK_KEYPAD_CH4_LB                        0x00

#define LK_CH_MINUS_UB                          0x11
#define LK_CH_MINUS_LB                          0x0D
#define LK_CH_PLUS_UB                           0x11
#define LK_CH_PLUS_LB                           0x0D
#define LK_INPUT_UB                             0x09
#define LK_INPUT_LB                             0x05
#define LK_MENU_UB                              0x09
#define LK_MENU_LB                              0x05
#define LK_OK_UB                                0x18
#define LK_OK_LB                                0x14
#define LK_POWER_UB                             0x03
#define LK_POWER_LB                             0x00
#define LK_VOL_MINUS_UB                         0x18
#define LK_VOL_MINUS_LB                         0x14
#define LK_VOL_PLUS_UB                          0x03
#define LK_VOL_PLUS_LB                          0x00

//-----PIN_OUT_SELECT------------------------------------------------------------------------

#define PWM0_PERIOD                             0xff
//#define PWM1_PERIOD                           0xff
//#define PWM2_PERIOD                           0xff    //PWM2 Period=( PWM2_PERIOD+1 ) *( 1/ Xtal)
//#define PWM3_PERIOD                           0xff

#define INIT_PWM0_DUTY                          0x7e
//#define INIT_PWM1_DUTY                        0x7e
//#define INIT_PWM2_DUTY                        0x7e    //PWM2_duty= (Init_Pwm2_DUTY +1 ) * (1/XTAL)
//#define INIT_PWM3_DUTY                        0x7e

#define BACKLITE_INIT_SETTING                   ENABLE
#define PWM2_MUX_SEL                            0x00

//------8051 Serial Port Setting------------------------------------------------
#define ENABLE_UART0                            ENABLE
#define ENABLE_UART0_INTERRUPT                  ENABLE
#define ENABLE_UART1                            DISABLE
#define ENABLE_UART1_INTERRUPT                  DISABLE
//------STDIO device setting----------------------------------------------------
#define STDIN_DEVICE                            IO_DEV_UART0
#define STDOUT_DEVICE                           IO_DEV_UART0
#define ENABLE_PIU_UART0                        DISABLE
#define ENABLE_PIU_UART0_INTERRUPT              DISABLE

//------ HDMI RELATED ---------------------------------------------------------
#define HDCP_HPD_INVERSE                        ENABLE

#define CHECK_IF_MBOOT_DEFAULT_ENV
#define FORCE_ENV_RELOAD
#define CONFIG_MBOOT_VERSION
#define USB_MBOOT_VERSION                 "MUSB-02.05"
#define USB_MBOOT_CURRENT_VERSION         "CL565126""(" __DATE__" - "__TIME__ ")"

#endif // _MSBOARD_H_
