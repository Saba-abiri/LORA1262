/*
 * SX1262.c
 *
 *  Created on: Feb 8, 2025
 *      Author: Saba_Abiri
 */

#ifndef INC_SX1262_DEFINITIONS_H_
#define INC_SX1262_DEFINITIONS_H_

#include "main.h"

#define SX126X_PACKET_LEN                              255


// SX126X physical layer properties
#define SX126X_FREQUENCY_STEP_SIZE                     0.9536743164 // 32Mhz / 2^25
#define SX126X_MAX_PACKET_LENGTH                       255
#define SX126X_CRYSTAL_FREQ                            32.0
#define SX126X_DIV_EXPONENT                            25

// SX126X SPI commands
// operational modes commands
#define SX126X_CMD_NOP                                 0x00
#define SX126X_CMD_SET_SLEEP                           0x84
#define SX126X_CMD_SET_STANDBY                         0x80
#define SX126X_CMD_SET_FS                              0xC1
#define SX126X_CMD_SET_TX                              0x83
#define SX126X_CMD_SET_RX                              0x82
#define SX126X_CMD_STOP_TIMER_ON_PREAMBLE              0x9F
#define SX126X_CMD_SET_RX_DUTY_CYCLE                   0x94
#define SX126X_CMD_SET_CAD                             0xC5
#define SX126X_CMD_SET_TX_CONTINUOUS_WAVE              0xD1
#define SX126X_CMD_SET_TX_INFINITE_PREAMBLE            0xD2
#define SX126X_CMD_SET_REGULATOR_MODE                  0x96
#define SX126X_CMD_CALIBRATE                           0x89
#define SX126X_CMD_CALIBRATE_IMAGE                     0x98
#define SX126X_CMD_SET_PA_CONFIG                       0x95
#define SX126X_CMD_SET_RX_TX_FALLBACK_MODE             0x93

// register and buffer access commands
#define SX126X_CMD_WRITE_REGISTER                      0x0D
#define SX126X_CMD_READ_REGISTER                       0x1D
#define SX126X_CMD_WRITE_BUFFER                        0x0E
#define SX126X_CMD_READ_BUFFER                         0x1E

// DIO and IRQ control
#define SX126X_CMD_SET_DIO_IRQ_PARAMS                  0x08
#define SX126X_CMD_GET_IRQ_STATUS                      0x12
#define SX126X_CMD_CLEAR_IRQ_STATUS                    0x02
#define SX126X_CMD_SET_DIO2_AS_RF_SWITCH_CTRL          0x9D
#define SX126X_CMD_SET_DIO3_AS_TCXO_CTRL               0x97

// RF, modulation and packet commands
#define SX126X_CMD_SET_RF_FREQUENCY                    0x86
#define SX126X_CMD_SET_PACKET_TYPE                     0x8A
#define SX126X_CMD_GET_PACKET_TYPE                     0x11
#define SX126X_CMD_SET_TX_PARAMS                       0x8E
#define SX126X_CMD_SET_MODULATION_PARAMS               0x8B
#define SX126X_CMD_SET_PACKET_PARAMS                   0x8C
#define SX126X_CMD_SET_CAD_PARAMS                      0x88
#define SX126X_CMD_SET_BUFFER_BASE_ADDRESS             0x8F
#define SX126X_CMD_SET_LORA_SYMB_NUM_TIMEOUT           0xA0

// status commands
#define SX126X_CMD_GET_STATUS                          0xC0
#define SX126X_CMD_GET_RSSI_INST                       0x15
#define SX126X_CMD_GET_RX_BUFFER_STATUS                0x13
#define SX126X_CMD_GET_PACKET_STATUS                   0x14
#define SX126X_CMD_GET_DEVICE_ERRORS                   0x17
#define SX126X_CMD_CLEAR_DEVICE_ERRORS                 0x07
#define SX126X_CMD_GET_STATS                           0x10
#define SX126X_CMD_RESET_STATS                         0x00

#define SX126X_CMD_PRAM_UPDATE                         0xD9
#define SX126X_CMD_SET_LBT_SCAN_PARAMS                 0x9A
#define SX126X_CMD_SET_SPECTR_SCAN_PARAMS              0x9B

// SX126X register map
#define SX126X_REG_RX_GAIN_RETENTION_0                 0x029F // SX1268 datasheet v1.1, section 9.6
#define SX126X_REG_RX_GAIN_RETENTION_1                 0x02A0 // SX1268 datasheet v1.1, section 9.6
#define SX126X_REG_RX_GAIN_RETENTION_2                 0x02A1 // SX1268 datasheet v1.1, section 9.6
#define SX126X_REG_VERSION_STRING                      0x0320
#define SX126X_REG_HOPPING_ENABLE                      0x0385
#define SX126X_REG_LR_FHSS_PACKET_LENGTH               0x0386
#define SX126X_REG_LR_FHSS_NUM_HOPPING_BLOCKS          0x0387
#define SX126X_REG_LR_FHSS_NUM_SYMBOLS_FREQX_MSB(X)    (0x0388 + (X)*6)
#define SX126X_REG_LR_FHSS_NUM_SYMBOLS_FREQX_LSB(X)    (0x0389 + (X)*6)
#define SX126X_REG_LR_FHSS_FREQX_0(X)                  (0x038A + (X)*6)
#define SX126X_REG_LR_FHSS_FREQX_1(X)                  (0x038B + (X)*6)
#define SX126X_REG_LR_FHSS_FREQX_2(X)                  (0x038C + (X)*6)
#define SX126X_REG_LR_FHSS_FREQX_3(X)                  (0x038D + (X)*6)
#define SX126X_REG_SPECTRAL_SCAN_RESULT                0x0401
#define SX126X_REG_DIOX_OUT_ENABLE                     0x0580
#define SX126X_REG_DIOX_DRIVE_STRENGTH                 0x0582
#define SX126X_REG_DIOX_IN_ENABLE                      0x0583
#define SX126X_REG_DIOX_PULL_UP_CTRL                   0x0584
#define SX126X_REG_DIOX_PULL_DOWN_CTRL                 0x0585
#define SX126X_REG_TX_BITBANG_ENABLE_0                 0x0587
#define SX126X_REG_PATCH_UPDATE_ENABLE                 0x0610
#define SX126X_REG_TX_BITBANG_ENABLE_1                 0x0680
#define SX126X_REG_WHITENING_INITIAL_MSB               0x06B8
#define SX126X_REG_WHITENING_INITIAL_LSB               0x06B9
#define SX126X_REG_RX_TX_PLD_LEN                       0x06BB
#define SX126X_REG_CRC_INITIAL_MSB                     0x06BC
#define SX126X_REG_CRC_INITIAL_LSB                     0x06BD
#define SX126X_REG_CRC_POLYNOMIAL_MSB                  0x06BE
#define SX126X_REG_CRC_POLYNOMIAL_LSB                  0x06BF
#define SX126X_REG_SYNC_WORD_0                         0x06C0
#define SX126X_REG_SYNC_WORD_1                         0x06C1
#define SX126X_REG_SYNC_WORD_2                         0x06C2
#define SX126X_REG_SYNC_WORD_3                         0x06C3
#define SX126X_REG_SYNC_WORD_4                         0x06C4
#define SX126X_REG_SYNC_WORD_5                         0x06C5
#define SX126X_REG_SYNC_WORD_6                         0x06C6
#define SX126X_REG_SYNC_WORD_7                         0x06C7
#define SX126X_REG_NODE_ADDRESS                        0x06CD
#define SX126X_REG_BROADCAST_ADDRESS                   0x06CE
#define SX126X_REG_PAYLOAD_LENGTH                      0x0702
#define SX126X_REG_PACKET_PARAMS                       0x0704
#define SX126X_REG_LORA_SYNC_TIMEOUT                   0x0706
#define SX126X_REG_IQ_CONFIG                           0x0736
#define SX126X_REG_LORA_SYNC_WORD_MSB                  0x0740
#define SX126X_REG_LORA_SYNC_WORD_LSB                  0x0741
#define SX126X_REG_FREQ_ERROR                          0x076B
#define SX126X_REG_SPECTRAL_SCAN_STATUS                0x07CD
#define SX126X_REG_RX_ADDR_PTR                         0x0803
#define SX126X_REG_RANDOM_NUMBER_0                     0x0819
#define SX126X_REG_RANDOM_NUMBER_1                     0x081A
#define SX126X_REG_RANDOM_NUMBER_2                     0x081B
#define SX126X_REG_RANDOM_NUMBER_3                     0x081C
#define SX126X_REG_SENSITIVITY_CONFIG                  0x0889 // SX1268 datasheet v1.1, section 15.1
#define SX126X_REG_RF_FREQUENCY_0                      0x088B
#define SX126X_REG_RF_FREQUENCY_1                      0x088C
#define SX126X_REG_RF_FREQUENCY_2                      0x088D
#define SX126X_REG_RF_FREQUENCY_3                      0x088E
#define SX126X_REG_RSSI_AVG_WINDOW                     0x089B
#define SX126X_REG_RX_GAIN                             0x08AC
#define SX126X_REG_TX_CLAMP_CONFIG                     0x08D8
#define SX126X_REG_ANA_LNA                             0x08E2
#define SX126X_REG_LNA_CAP_TUNE_N                      0x08E3
#define SX126X_REG_LNA_CAP_TUNE_P                      0x08E4
#define SX126X_REG_ANA_MIXER                           0x08E5
#define SX126X_REG_OCP_CONFIGURATION                   0x08E7
#define SX126X_REG_RTC_CTRL                            0x0902
#define SX126X_REG_XTA_TRIM                            0x0911
#define SX126X_REG_XTB_TRIM                            0x0912
#define SX126X_REG_DIO3_OUT_VOLTAGE_CTRL               0x0920
#define SX126X_REG_EVENT_MASK                          0x0944
#define SX126X_REG_PATCH_MEMORY_BASE                   0x8000

// SX126X SPI command variables
//SX126X_CMD_SET_SLEEP                                               MSB   LSB   DESCRIPTION
#define SX126X_SLEEP_START_COLD                        0b00000000  //  2     2   sleep mode: cold start, configuration is lost (default)
#define SX126X_SLEEP_START_WARM                        0b00000100  //  2     2               warm start, configuration is retained
#define SX126X_SLEEP_RTC_OFF                           0b00000000  //  0     0   wake on RTC timeout: disabled
#define SX126X_SLEEP_RTC_ON                            0b00000001  //  0     0                        enabled

//SX126X_CMD_SET_STANDBY
#define SX126X_STANDBY_RC                              0x00        //  7     0   standby mode: 13 MHz RC oscillator
#define SX126X_STANDBY_XOSC                            0x01        //  7     0                 32 MHz crystal oscillator

//SX126X_CMD_SET_RX
#define SX126X_RX_TIMEOUT_NONE                         0x000000    //  23    0   Rx timeout duration: no timeout (Rx single mode)
#define SX126X_RX_TIMEOUT_INF                          0xFFFFFF    //  23    0                        infinite (Rx continuous mode)

//SX126X_CMD_SET_TX
#define SX126X_TX_TIMEOUT_NONE                         0x000000    //  23    0   Tx timeout duration: no timeout (Tx single mode)

//SX126X_CMD_STOP_TIMER_ON_PREAMBLE
#define SX126X_STOP_ON_PREAMBLE_OFF                    0x00        //  7     0   stop timer on: sync word or header (default)
#define SX126X_STOP_ON_PREAMBLE_ON                     0x01        //  7     0                  preamble detection

//SX126X_CMD_SET_REGULATOR_MODE
#define SX126X_REGULATOR_LDO                           0x00        //  7     0   set regulator mode: LDO (default)
#define SX126X_REGULATOR_DC_DC                         0x01        //  7     0                       DC-DC

//SX126X_CMD_CALIBRATE
#define SX126X_CALIBRATE_IMAGE_OFF                     0b00000000  //  6     6   image calibration: disabled
#define SX126X_CALIBRATE_IMAGE_ON                      0b01000000  //  6     6                      enabled
#define SX126X_CALIBRATE_ADC_BULK_P_OFF                0b00000000  //  5     5   ADC bulk P calibration: disabled
#define SX126X_CALIBRATE_ADC_BULK_P_ON                 0b00100000  //  5     5                           enabled
#define SX126X_CALIBRATE_ADC_BULK_N_OFF                0b00000000  //  4     4   ADC bulk N calibration: disabled
#define SX126X_CALIBRATE_ADC_BULK_N_ON                 0b00010000  //  4     4                           enabled
#define SX126X_CALIBRATE_ADC_PULSE_OFF                 0b00000000  //  3     3   ADC pulse calibration: disabled
#define SX126X_CALIBRATE_ADC_PULSE_ON                  0b00001000  //  3     3                          enabled
#define SX126X_CALIBRATE_PLL_OFF                       0b00000000  //  2     2   PLL calibration: disabled
#define SX126X_CALIBRATE_PLL_ON                        0b00000100  //  2     2                    enabled
#define SX126X_CALIBRATE_RC13M_OFF                     0b00000000  //  1     1   13 MHz RC osc. calibration: disabled
#define SX126X_CALIBRATE_RC13M_ON                      0b00000010  //  1     1                               enabled
#define SX126X_CALIBRATE_RC64K_OFF                     0b00000000  //  0     0   64 kHz RC osc. calibration: disabled
#define SX126X_CALIBRATE_RC64K_ON                      0b00000001  //  0     0                               enabled
#define SX126X_CALIBRATE_ALL                           0b01111111  //  6     0   calibrate all blocks

//SX126X_CMD_SET_PA_CONFIG
#define SX126X_PA_CONFIG_HP_MAX                        0x07
#define SX126X_PA_CONFIG_DUTY_CYCLE                    0x04

//SX126X_CMD_SET_RX_TX_FALLBACK_MODE
#define SX126X_RX_TX_FALLBACK_MODE_FS                  0x40        //  7     0   after Rx/Tx go to: FS mode
#define SX126X_RX_TX_FALLBACK_MODE_STDBY_XOSC          0x30        //  7     0                      standby with crystal oscillator
#define SX126X_RX_TX_FALLBACK_MODE_STDBY_RC            0x20        //  7     0                      standby with RC oscillator (default)

//SX126X_CMD_SET_DIO_IRQ_PARAMS
#define SX126X_IRQ_LR_FHSS_HOP                         0b0100000000000000  //  14    14  PA ramped up during LR-FHSS hop
#define SX126X_IRQ_TIMEOUT                             0b0000001000000000  //  9     9   Rx or Tx timeout
#define SX126X_IRQ_CAD_DETECTED                        0b0000000100000000  //  8     8   channel activity detected
#define SX126X_IRQ_CAD_DONE                            0b0000000010000000  //  7     7   channel activity detection finished
#define SX126X_IRQ_CRC_ERR                             0b0000000001000000  //  6     6   wrong CRC received
#define SX126X_IRQ_HEADER_ERR                          0b0000000000100000  //  5     5   LoRa header CRC error
#define SX126X_IRQ_HEADER_VALID                        0b0000000000010000  //  4     4   valid LoRa header received
#define SX126X_IRQ_SYNC_WORD_VALID                     0b0000000000001000  //  3     3   valid sync word detected
#define SX126X_IRQ_PREAMBLE_DETECTED                   0b0000000000000100  //  2     2   preamble detected
#define SX126X_IRQ_RX_DONE                             0b0000000000000010  //  1     1   packet received
#define SX126X_IRQ_TX_DONE                             0b0000000000000001  //  0     0   packet transmission completed
#define SX126X_IRQ_RX_DEFAULT                          0b0000001001100010  //  14    0   default for Rx (RX_DONE, TIMEOUT, CRC_ERR and HEADER_ERR)
#define SX126X_IRQ_ALL                                 0b0100001111111111  //  14    0   all interrupts
#define SX126X_IRQ_NONE                                0b0000000000000000  //  14    0   no interrupts

//SX126X_CMD_SET_DIO2_AS_RF_SWITCH_CTRL
#define SX126X_DIO2_AS_IRQ                             0x00        //  7     0   DIO2 configuration: IRQ
#define SX126X_DIO2_AS_RF_SWITCH                       0x01        //  7     0                       RF switch control

//SX126X_CMD_SET_DIO3_AS_TCXO_CTRL
#define SX126X_DIO3_OUTPUT_1_6                         0x00        //  7     0   DIO3 voltage output for TCXO: 1.6 V
#define SX126X_DIO3_OUTPUT_1_7                         0x01        //  7     0                                 1.7 V
#define SX126X_DIO3_OUTPUT_1_8                         0x02        //  7     0                                 1.8 V
#define SX126X_DIO3_OUTPUT_2_2                         0x03        //  7     0                                 2.2 V
#define SX126X_DIO3_OUTPUT_2_4                         0x04        //  7     0                                 2.4 V
#define SX126X_DIO3_OUTPUT_2_7                         0x05        //  7     0                                 2.7 V
#define SX126X_DIO3_OUTPUT_3_0                         0x06        //  7     0                                 3.0 V
#define SX126X_DIO3_OUTPUT_3_3                         0x07        //  7     0                                 3.3 V

//SX126X_CMD_SET_PACKET_TYPE
#define SX126X_PACKET_TYPE_GFSK                        0x00        //  7     0   packet type: GFSK
#define SX126X_PACKET_TYPE_LORA                        0x01        //  7     0                LoRa
#define SX126X_PACKET_TYPE_LR_FHSS                     0x03        //  7     0                LR-FHSS

//SX126X_CMD_SET_TX_PARAMS
#define SX126X_PA_RAMP_10U                             0x00        //  7     0   ramp time: 10 us
#define SX126X_PA_RAMP_20U                             0x01        //  7     0              20 us
#define SX126X_PA_RAMP_40U                             0x02        //  7     0              40 us
#define SX126X_PA_RAMP_80U                             0x03        //  7     0              80 us
#define SX126X_PA_RAMP_200U                            0x04        //  7     0              200 us
#define SX126X_PA_RAMP_800U                            0x05        //  7     0              800 us
#define SX126X_PA_RAMP_1700U                           0x06        //  7     0              1700 us
#define SX126X_PA_RAMP_3400U                           0x07        //  7     0              3400 us

//SX126X_CMD_SET_MODULATION_PARAMS
#define SX126X_GFSK_FILTER_NONE                        0x00        //  7     0   GFSK filter: none
#define SX126X_GFSK_FILTER_GAUSS_0_3                   0x08        //  7     0                Gaussian, BT = 0.3
#define SX126X_GFSK_FILTER_GAUSS_0_5                   0x09        //  7     0                Gaussian, BT = 0.5
#define SX126X_GFSK_FILTER_GAUSS_0_7                   0x0A        //  7     0                Gaussian, BT = 0.7
#define SX126X_GFSK_FILTER_GAUSS_1                     0x0B        //  7     0                Gaussian, BT = 1
#define SX126X_GFSK_RX_BW_4_8                          0x1F        //  7     0   GFSK Rx bandwidth: 4.8 kHz
#define SX126X_GFSK_RX_BW_5_8                          0x17        //  7     0                      5.8 kHz
#define SX126X_GFSK_RX_BW_7_3                          0x0F        //  7     0                      7.3 kHz
#define SX126X_GFSK_RX_BW_9_7                          0x1E        //  7     0                      9.7 kHz
#define SX126X_GFSK_RX_BW_11_7                         0x16        //  7     0                      11.7 kHz
#define SX126X_GFSK_RX_BW_14_6                         0x0E        //  7     0                      14.6 kHz
#define SX126X_GFSK_RX_BW_19_5                         0x1D        //  7     0                      19.5 kHz
#define SX126X_GFSK_RX_BW_23_4                         0x15        //  7     0                      23.4 kHz
#define SX126X_GFSK_RX_BW_29_3                         0x0D        //  7     0                      29.3 kHz
#define SX126X_GFSK_RX_BW_39_0                         0x1C        //  7     0                      39.0 kHz
#define SX126X_GFSK_RX_BW_46_9                         0x14        //  7     0                      46.9 kHz
#define SX126X_GFSK_RX_BW_58_6                         0x0C        //  7     0                      58.6 kHz
#define SX126X_GFSK_RX_BW_78_2                         0x1B        //  7     0                      78.2 kHz
#define SX126X_GFSK_RX_BW_93_8                         0x13        //  7     0                      93.8 kHz
#define SX126X_GFSK_RX_BW_117_3                        0x0B        //  7     0                      117.3 kHz
#define SX126X_GFSK_RX_BW_156_2                        0x1A        //  7     0                      156.2 kHz
#define SX126X_GFSK_RX_BW_187_2                        0x12        //  7     0                      187.2 kHz
#define SX126X_GFSK_RX_BW_234_3                        0x0A        //  7     0                      234.3 kHz
#define SX126X_GFSK_RX_BW_312_0                        0x19        //  7     0                      312.0 kHz
#define SX126X_GFSK_RX_BW_373_6                        0x11        //  7     0                      373.6 kHz
#define SX126X_GFSK_RX_BW_467_0                        0x09        //  7     0                      467.0 kHz
#define SX126X_LORA_BW_7_8                             0x00        //  7     0   LoRa bandwidth: 7.8 kHz
#define SX126X_LORA_BW_10_4                            0x08        //  7     0                   10.4 kHz
#define SX126X_LORA_BW_15_6                            0x01        //  7     0                   15.6 kHz
#define SX126X_LORA_BW_20_8                            0x09        //  7     0                   20.8 kHz
#define SX126X_LORA_BW_31_25                           0x02        //  7     0                   31.25 kHz
#define SX126X_LORA_BW_41_7                            0x0A        //  7     0                   41.7 kHz
#define SX126X_LORA_BW_62_5                            0x03        //  7     0                   62.5 kHz
#define SX126X_LORA_BW_125_0                           0x04        //  7     0                   125.0 kHz
#define SX126X_LORA_BW_250_0                           0x05        //  7     0                   250.0 kHz
#define SX126X_LORA_BW_500_0                           0x06        //  7     0                   500.0 kHz
#define SX126X_LORA_CR_4_5                             0x01        //  7     0   LoRa coding rate: 4/5
#define SX126X_LORA_CR_4_6                             0x02        //  7     0                     4/6
#define SX126X_LORA_CR_4_7                             0x03        //  7     0                     4/7
#define SX126X_LORA_CR_4_8                             0x04        //  7     0                     4/8
#define SX126X_LORA_LOW_DATA_RATE_OPTIMIZE_OFF         0x00        //  7     0   LoRa low data rate optimization: disabled
#define SX126X_LORA_LOW_DATA_RATE_OPTIMIZE_ON          0x01        //  7     0                                    enabled

//SX126X_CMD_SET_PACKET_PARAMS
#define SX126X_GFSK_PREAMBLE_DETECT_OFF                0x00        //  7     0   GFSK minimum preamble length before reception starts: detector disabled
#define SX126X_GFSK_PREAMBLE_DETECT_8                  0x04        //  7     0                                                         8 bits
#define SX126X_GFSK_PREAMBLE_DETECT_16                 0x05        //  7     0                                                         16 bits
#define SX126X_GFSK_PREAMBLE_DETECT_24                 0x06        //  7     0                                                         24 bits
#define SX126X_GFSK_PREAMBLE_DETECT_32                 0x07        //  7     0                                                         32 bits
#define SX126X_GFSK_ADDRESS_FILT_OFF                   0x00        //  7     0   GFSK address filtering: disabled
#define SX126X_GFSK_ADDRESS_FILT_NODE                  0x01        //  7     0                           node only
#define SX126X_GFSK_ADDRESS_FILT_NODE_BROADCAST        0x02        //  7     0                           node and broadcast
#define SX126X_GFSK_PACKET_FIXED                       0x00        //  7     0   GFSK packet type: fixed (payload length known in advance to both sides)
#define SX126X_GFSK_PACKET_VARIABLE                    0x01        //  7     0                     variable (payload length added to packet)
#define SX126X_GFSK_CRC_OFF                            0x01        //  7     0   GFSK packet CRC: disabled
#define SX126X_GFSK_CRC_1_BYTE                         0x00        //  7     0                    1 byte
#define SX126X_GFSK_CRC_2_BYTE                         0x02        //  7     0                    2 byte
#define SX126X_GFSK_CRC_1_BYTE_INV                     0x04        //  7     0                    1 byte, inverted
#define SX126X_GFSK_CRC_2_BYTE_INV                     0x06        //  7     0                    2 byte, inverted
#define SX126X_GFSK_WHITENING_OFF                      0x00        //  7     0   GFSK data whitening: disabled
#define SX126X_GFSK_WHITENING_ON                       0x01        //  7     0                        enabled
#define SX126X_LORA_HEADER_EXPLICIT                    0x00        //  7     0   LoRa header mode: explicit
#define SX126X_LORA_HEADER_IMPLICIT                    0x01        //  7     0                     implicit
#define SX126X_LORA_CRC_OFF                            0x00        //  7     0   LoRa CRC mode: disabled
#define SX126X_LORA_CRC_ON                             0x01        //  7     0                  enabled
#define SX126X_LORA_IQ_STANDARD                        0x00        //  7     0   LoRa IQ setup: standard
#define SX126X_LORA_IQ_INVERTED                        0x01        //  7     0                  inverted

//SX126X_CMD_SET_CAD_PARAMS
#define SX126X_CAD_ON_1_SYMB                           0x00        //  7     0   number of symbols used for CAD: 1
#define SX126X_CAD_ON_2_SYMB                           0x01        //  7     0                                   2
#define SX126X_CAD_ON_4_SYMB                           0x02        //  7     0                                   4
#define SX126X_CAD_ON_8_SYMB                           0x03        //  7     0                                   8
#define SX126X_CAD_ON_16_SYMB                          0x04        //  7     0                                   16
#define SX126X_CAD_GOTO_STDBY                          0x00        //  7     0   after CAD is done, always go to STDBY_RC mode
#define SX126X_CAD_GOTO_RX                             0x01        //  7     0   after CAD is done, go to Rx mode if activity is detected
#define SX126X_CAD_PARAM_DEFAULT                       0xFF        //  7     0   used by the CAD methods to specify default parameter value
#define SX126X_CAD_PARAM_DET_MIN                       10          //  7     0   default detMin CAD parameter

//SX126X_CMD_GET_STATUS
#define SX126X_STATUS_MODE_STDBY_RC                    0b00100000  //  6     4   current chip mode: STDBY_RC
#define SX126X_STATUS_MODE_STDBY_XOSC                  0b00110000  //  6     4                      STDBY_XOSC
#define SX126X_STATUS_MODE_FS                          0b01000000  //  6     4                      FS
#define SX126X_STATUS_MODE_RX                          0b01010000  //  6     4                      RX
#define SX126X_STATUS_MODE_TX                          0b01100000  //  6     4                      TX
#define SX126X_STATUS_DATA_AVAILABLE                   0b00000100  //  3     1   command status: packet received and data can be retrieved
#define SX126X_STATUS_CMD_TIMEOUT                      0b00000110  //  3     1                   SPI command timed out
#define SX126X_STATUS_CMD_INVALID                      0b00001000  //  3     1                   invalid SPI command
#define SX126X_STATUS_CMD_FAILED                       0b00001010  //  3     1                   SPI command failed to execute
#define SX126X_STATUS_TX_DONE                          0b00001100  //  3     1                   packet transmission done
#define SX126X_STATUS_SPI_FAILED                       0b11111111  //  7     0   SPI transaction failed

//SX126X_CMD_GET_PACKET_STATUS
#define SX126X_GFSK_RX_STATUS_PREAMBLE_ERR             0b10000000  //  7     7   GFSK Rx status: preamble error
#define SX126X_GFSK_RX_STATUS_SYNC_ERR                 0b01000000  //  6     6                   sync word error
#define SX126X_GFSK_RX_STATUS_ADRS_ERR                 0b00100000  //  5     5                   address error
#define SX126X_GFSK_RX_STATUS_CRC_ERR                  0b00010000  //  4     4                   CRC error
#define SX126X_GFSK_RX_STATUS_LENGTH_ERR               0b00001000  //  3     3                   length error
#define SX126X_GFSK_RX_STATUS_ABORT_ERR                0b00000100  //  2     2                   abort error
#define SX126X_GFSK_RX_STATUS_PACKET_RECEIVED          0b00000010  //  2     2                   packet received
#define SX126X_GFSK_RX_STATUS_PACKET_SENT              0b00000001  //  2     2                   packet sent

//SX126X_CMD_GET_DEVICE_ERRORS
#define SX126X_PA_RAMP_ERR                             0b100000000 //  8     8   device errors: PA ramping failed
#define SX126X_PLL_LOCK_ERR                            0b001000000 //  6     6                  PLL failed to lock
#define SX126X_XOSC_START_ERR                          0b000100000 //  5     5                  crystal oscillator failed to start
#define SX126X_IMG_CALIB_ERR                           0b000010000 //  4     4                  image calibration failed
#define SX126X_ADC_CALIB_ERR                           0b000001000 //  3     3                  ADC calibration failed
#define SX126X_PLL_CALIB_ERR                           0b000000100 //  2     2                  PLL calibration failed
#define SX126X_RC13M_CALIB_ERR                         0b000000010 //  1     1                  RC13M calibration failed
#define SX126X_RC64K_CALIB_ERR                         0b000000001 //  0     0                  RC64K calibration failed

//SX126X_CMD_SET_LBT_SCAN_PARAMS + SX126X_CMD_SET_SPECTR_SCAN_PARAMS
#define SX126X_SCAN_INTERVAL_7_68_US                   10          //  7     0   RSSI reading interval: 7.68 us
#define SX126X_SCAN_INTERVAL_8_20_US                   11          //  7     0                          8.20 us
#define SX126X_SCAN_INTERVAL_8_68_US                   12          //  7     0                          8.68 us

// SX126X SPI register variables
//SX126X_REG_HOPPING_ENABLE
#define SX126X_HOPPING_ENABLED                         0b00000001  //  0     0   intra-packet hopping for LR-FHSS: enabled
#define SX126X_HOPPING_DISABLED                        0b00000000  //  0     0                                     (disabled)

//SX126X_REG_LORA_SYNC_WORD_MSB + LSB
#define SX126X_SYNC_WORD_PUBLIC                        0x34        // actually 0x3444  NOTE: The low nibbles in each byte (0x_4_4) are masked out since apparently, they're reserved.
#define SX126X_SYNC_WORD_PRIVATE                       0x12        // actually 0x1424        You couldn't make this up if you tried.

// SX126X_REG_TX_BITBANG_ENABLE_1
#define SX126X_TX_BITBANG_1_DISABLED                   0b00000000  //  6     4   Tx bitbang: disabled (default)
#define SX126X_TX_BITBANG_1_ENABLED                    0b00010000  //  6     4               enabled

// SX126X_REG_TX_BITBANG_ENABLE_0
#define SX126X_TX_BITBANG_0_DISABLED                   0b00000000  //  3     0   Tx bitbang: disabled (default)
#define SX126X_TX_BITBANG_0_ENABLED                    0b00001100  //  3     0               enabled

// SX126X_REG_DIOX_OUT_ENABLE
#define SX126X_DIO1_OUT_DISABLED                       0b00000010  //  1     1   DIO1 output: disabled
#define SX126X_DIO1_OUT_ENABLED                        0b00000000  //  1     1                enabled
#define SX126X_DIO2_OUT_DISABLED                       0b00000100  //  2     2   DIO2 output: disabled
#define SX126X_DIO2_OUT_ENABLED                        0b00000000  //  2     2                enabled
#define SX126X_DIO3_OUT_DISABLED                       0b00001000  //  3     3   DIO3 output: disabled
#define SX126X_DIO3_OUT_ENABLED                        0b00000000  //  3     3                enabled

// SX126X_REG_DIOX_IN_ENABLE
#define SX126X_DIO1_IN_DISABLED                        0b00000000  //  1     1   DIO1 input: disabled
#define SX126X_DIO1_IN_ENABLED                         0b00000010  //  1     1               enabled
#define SX126X_DIO2_IN_DISABLED                        0b00000000  //  2     2   DIO2 input: disabled
#define SX126X_DIO2_IN_ENABLED                         0b00000100  //  2     2               enabled
#define SX126X_DIO3_IN_DISABLED                        0b00000000  //  3     3   DIO3 input: disabled
#define SX126X_DIO3_IN_ENABLED                         0b00001000  //  3     3               enabled

// SX126X_REG_RX_GAIN
#define SX126X_RX_GAIN_BOOSTED                         0x96        //  7     0   Rx gain: boosted
#define SX126X_RX_GAIN_POWER_SAVING                    0x94        //  7     0            power saving
#define SX126X_RX_GAIN_SPECTRAL_SCAN                   0xCB        //  7     0            spectral scan

// SX126X_REG_PATCH_UPDATE_ENABLE
#define SX126X_PATCH_UPDATE_DISABLED                   0b00000000  //  4     4   patch update: disabled
#define SX126X_PATCH_UPDATE_ENABLED                    0b00010000  //  4     4                 enabled

// SX126X_REG_SPECTRAL_SCAN_STATUS
#define SX126X_SPECTRAL_SCAN_NONE                      0x00        //  7     0   spectral scan status: none
#define SX126X_SPECTRAL_SCAN_ONGOING                   0x0F        //  7     0                         ongoing
#define SX126X_SPECTRAL_SCAN_ABORTED                   0xF0        //  7     0                         aborted
#define SX126X_SPECTRAL_SCAN_COMPLETED                 0xFF        //  7     0                         completed

// SX126X_REG_RSSI_AVG_WINDOW
#define SX126X_SPECTRAL_SCAN_WINDOW_DEFAULT            (0x05 << 2) //  7     0   default RSSI average window

// SX126X_REG_ANA_LNA
#define SX126X_LNA_RNG_DISABLED                        0b00000001  //  0     0   random number: disabled
#define SX126X_LNA_RNG_ENABLED                         0b00000000  //  0     0                  enabled

// SX126X_REG_ANA_MIXER
#define SX126X_MIXER_RNG_DISABLED                      0b00000001  //  7     7   random number: disabled
#define SX126X_MIXER_RNG_ENABLED                       0b00000000  //  7     7                  enabled



typedef enum {
	RADIO_IDLE = 0,
	RADIO_RX = 1,
	RADIO_TX = 2
} SX1262_STATE;

#endif /* INC_SX1262_DEFINITIONS_H_ */
