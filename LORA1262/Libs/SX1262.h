/*
 * SX1262.c
 *
 *  Created on: Feb 8, 2025
 *      Author: Saba_Abiri
 */

#ifndef INC_SX1262_H_
#define INC_SX1262_H_

#include "SX1262_Definitions.h"

typedef struct{
	// peripheral config
	SPI_HandleTypeDef		SPI;
	GPIO_TypeDef*			Reset_Port;
	uint16_t				Reset_Pin;
	GPIO_TypeDef*			NSS_Port;
	uint16_t				NSS_Pin;
	GPIO_TypeDef*			Busy_Port;
	uint16_t				Busy_Pin;

	SX1262_STATE			State;

	uint8_t					TX_Buf[300]; // internal buffer for SPI commands
	uint8_t					RX_Buf[300]; // internal buffer for SPI commands

	uint8_t					Packet_Buf[SX126X_MAX_PACKET_LENGTH];

	void 					(*RX_Callback)(uint8_t*, uint8_t);




} SX1262;

SX1262 *SX1262_Get_st(void);

void SX1262_CSLow(void);
void SX1262_CSHigh(void);

void SX1262_BusyWait(void);
int  SX1262_IsBusy(void);

void SX1262_Set_Command(uint8_t *cmnd_, uint8_t *ans_, uint16_t Len,uint32_t Time_out ,uint16_t Delay);

void SX1262_HandleCallback(uint8_t *buf ,uint8_t *len);

void SX1262_Transmit(uint8_t*, uint8_t);
void SX1262_Init(void);

void SX1262_setRX(void);
uint8_t SX1262_Check_Correct(void);
uint8_t SX1262_waitForRadioCommandCompletion(uint32_t timeout);
void SX1262_setModeStandby(void);
void SX1262_setModeReceive(void);
uint8_t SX1262_getstatus(void);
void SX1262_Radio_essental_Config(void);
void SX1262_SetFrequency(uint32_t frequency);
#endif /* INC_SX1262_H_ */
