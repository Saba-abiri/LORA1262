/*
 * SX1262.c
 *
 *  Created on: Feb 8, 2025
 *      Author: Saba_Abiri
 */


#include "SX1262.h"
#include "string.h"
#include "math.h"

#define XTAL_FREQUENCY (double)32000000
#define FREQ_DIV  (double)pow(2, 25)
#define FREQ_STEP (double)(XTAL_FREQUENCY / FREQ_DIV)
#define Buf_Len		10

uint8_t cmnd[Buf_Len]={0};
uint8_t answ[Buf_Len]={0};

SX1262 SX_stc = {0};

uint8_t inReceiveMode = 0;
volatile uint8_t Status_Now=0;

HAL_StatusTypeDef err22 = 0;

//**************************************************************************************************************************************************************//
SX1262 *SX1262_Get_st(void)
{
	return(&SX_stc);
}

//**************************************************************************************************************************************************************//
// sets the CS pin low
void SX1262_CSLow(void)
{
	HAL_GPIO_WritePin(SX_stc.NSS_Port, (int)SX_stc.NSS_Pin, GPIO_PIN_RESET);
}

//**************************************************************************************************************************************************************//
// sets the CS pin high
void SX1262_CSHigh(void)
{
	HAL_GPIO_WritePin(SX_stc.NSS_Port, (int)SX_stc.NSS_Pin, GPIO_PIN_SET);
}

//**************************************************************************************************************************************************************//
// check if module is free or not?
int SX1262_IsBusy(void)
{
	return HAL_GPIO_ReadPin(SX_stc.Busy_Port, SX_stc.Busy_Pin);
}

//**************************************************************************************************************************************************************//
// wait for mdule to be free
void SX1262_BusyWait(void)
{
	while(HAL_GPIO_ReadPin(SX_stc.Busy_Port,SX_stc.Busy_Pin)) 
	{
		HAL_GPIO_ReadPin(SX_stc.Busy_Port, SX_stc.Busy_Pin);
	}
}

//**************************************************************************************************************************************************************//
// wait in tx mode
void SX1262_TxWait(void)
{
	while(SX_stc.State == RADIO_TX) {}
}

//**************************************************************************************************************************************************************//
// set command function
void SX1262_Set_Command(uint8_t *cmnd_, uint8_t *ans_, uint16_t Len,uint32_t Time_out ,uint16_t Delay)
{
	SX1262_BusyWait();

	SX1262_CSLow();
	err22 = HAL_SPI_TransmitReceive(&SX_stc.SPI, cmnd_, ans_, Len, Time_out); // 1 command byte, 1 wait, 2 response
	SX1262_CSHigh();
	
	if(Delay)
	{
		HAL_Delay(Delay);
	}
}

//**************************************************************************************************************************************************************//
/*Receive a packet if available
If available, this will return the size of the packet and store the packet contents into the user-provided buffer.
A max length of the buffer can be provided to avoid buffer overflow.  If buffer is not large enough for entire payload, overflow is thrown out.
Recommended to pass in a buffer that is 255 bytes long to make sure you can received any lora packet that comes in.

Returns -1 when no packet is available.
Returns 0 when an empty packet is received (packet with no payload)
Returns payload size (1-255) when a packet with a non-zero payload is received. If packet received is larger than the buffer provided, this will return buffMaxLen
*/
void SX1262_HandleCallback(uint8_t *buf ,uint8_t *len)
{

 //Clear all interrupt flags.  This should result in the interrupt pin going low
	cmnd[0] = 0x12;          //Read IRQStatus command
	cmnd[1] = 0xFF;          //
	cmnd[2] = 0xFF;          //
	cmnd[3] = 0xFF;  				 //
		
	SX1262_Set_Command(cmnd,answ,4, 100,0);

	//==================================================================

	
  //Tell the radio to clear the interrupt, and set the pin back inactive.
  while (HAL_GPIO_ReadPin(DI01_LORA_GPIO_Port,DI01_LORA_Pin)) 
	{
   
		//==================================================================
	 //Clear all interrupt flags.  This should result in the interrupt pin going low
		cmnd[0] = 0x02;          //Opcode for ClearIRQStatus command
		cmnd[1] = 0xFF;          //IRQ bits to clear (MSB) (0xFFFF means clear all interrupts)
		cmnd[2] = 0xFF;          //IRQ bits to clear (LSB)
		
		SX1262_Set_Command(cmnd,answ,3,100,0);

		//==================================================================
  }
	// (Optional) Read the packet status info from the radio.
  // This is things like radio strength, noise, etc.
  // See datasheet 13.5.3 for more info
  // This provides debug info about the packet we received
		cmnd[0] = 0x14;          //Opcode for get packet status
		cmnd[1] = 0xFF;          //Dummy byte. Returns status
		cmnd[2] = 0xFF;          //Dummy byte. Returns rssi
		cmnd[3] = 0xFF;          //Dummy byte. Returns snd
		cmnd[4] = 0xFF;          //Dummy byte. Returns signal RSSI
		
		SX1262_Set_Command(cmnd,answ,5,100,0);
	//================================================================== 
  //We're almost ready to read the packet from the radio
  //But first we have to know how big the packet is, and where in the radio memory it is stored
		cmnd[0] = 0x13;          //Opcode for GetRxBufferStatus command
		cmnd[1] = 0xFF;          //Dummy.  Returns radio status
		cmnd[2] = 0xFF;          //Dummy.  Returns loraPacketLength
		cmnd[3] = 0xFF;          //Dummy.  Returns memory offset (address)
		
		SX1262_Set_Command(cmnd,answ,4,100,0);
		
	//================================================================== 
  uint8_t payloadLen = answ[2];    //How long the lora packet is
  uint8_t startAddress = answ[3];  //Where in 1262 memory is the packet stored

  //Make sure we don't overflow the buffer if the packet is larger than our buffer
  //if (buffMaxLen < payloadLen) {payloadLen = buffMaxLen;}
	answ[9]= answ[8]=answ[7]=answ[6]=answ[5]=answ[4]=answ[3]=answ[2]=answ[1]=answ[0]=0;
//================================================================== 
  //Read the radio buffer from the SX1262 into the user-supplied buffer
	cmnd[0] = 0x1E;          //Opcode for ReadBuffer command
  cmnd[1] = startAddress;  //SX1262 memory location to start reading from
  cmnd[2] = 0x00;          //Dummy byte
	cmnd[3] = 0x00;
	cmnd[4] = 0x00;
	cmnd[5] = 0x00;
	cmnd[6] = 0x00;
	
		SX1262_BusyWait();

		SX1262_CSLow();
		err22 = HAL_SPI_TransmitReceive(&SX_stc.SPI, cmnd,answ,3, 100);
		err22 = HAL_SPI_TransmitReceive(&SX_stc.SPI, &cmnd[3],answ,payloadLen, 100);
		SX1262_CSHigh();
		
		SX1262_BusyWait();
//================================================================== 
	memcpy(buf,answ,payloadLen);
	*len = payloadLen;
}


//**************************************************************************************************************************************************************//
//Transmit data using LORA module
void SX1262_Transmit(uint8_t* data, uint8_t len){
	

	uint8_t counter =5;
	
	//==================================================================
		cmnd[0] = 0x8C;          //Opcode for "SetPacketParameters"
		cmnd[1] = 0x00;          //PacketParam1 = Preamble Len MSB
		cmnd[2] = 0x0C;          //PacketParam2 = Preamble Len LSB
		cmnd[3] = 0x00;          //PacketParam3 = Header Type. 0x00 = Variable Len, 0x01 = Fixed Length
		cmnd[4] = len;          //PacketParam4 = Payload Length (Max is 255 bytes)
		cmnd[5] = 0x00;          //PacketParam5 = CRC Type. 0x00 = Off, 0x01 = on
		cmnd[6] = 0x00;          //PacketParam6 = Invert IQ.  0x00 = Standard, 0x01 = Inverted
		SX1262_Set_Command(cmnd,answ,7,100,0);
	
		//==================================================================
		SX1262_waitForRadioCommandCompletion(100);  //Give time for radio to process the command
	  //==================================================================
		//Write the payload to the buffer
		//  Reminder: PayloadLength is defined in setPacketParams
		cmnd[0] = 0x0E,          //Opcode for WriteBuffer command _ Write data into the FIFO
		cmnd[1] = 0x00;          //Dummy byte before writing payload
		
		SX1262_BusyWait();

		SX1262_CSLow();
		
		err22 = HAL_SPI_TransmitReceive(&SX_stc.SPI, cmnd,answ,2 , 100);
		err22 = HAL_SPI_TransmitReceive(&SX_stc.SPI,data,answ,len+1, 100);
		
		SX1262_CSHigh();

		SX1262_BusyWait();
		//==================================================================
		SX1262_waitForRadioCommandCompletion(100);  //Give time for radio to process the command
	  //==================================================================
		//Transmit!
  // An interrupt will be triggered if we surpass our timeout
		cmnd[0] = 0x83;          //Opcode for SetTx command
		cmnd[1] = 0xFF;          //Timeout (3-byte number)
		cmnd[2] = 0xFF;          //Timeout (3-byte number)
		cmnd[3] = 0xFF;          //Timeout (3-byte number)
		
		SX1262_Set_Command(cmnd,answ,4,100,0);
		//==================================================================
		SX1262_waitForRadioCommandCompletion(500);  //Give time for radio to process the command
		//==================================================================
		
		while(SX1262_getstatus() != 0x06 && counter--){HAL_Delay(10);};
		
		//Remember that we are in Tx mode.  If we want to receive a packet, we need to switch into receiving mode
		inReceiveMode = 0;	
}

//**************************************************************************************************************************************************************//
//Initialize module
void SX1262_Init(void){

	// Toggle reset
	SX1262_CSHigh();
	
	HAL_GPIO_WritePin(SX_stc.Reset_Port,SX_stc.Reset_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(SX_stc.Reset_Port, SX_stc.Reset_Pin, GPIO_PIN_SET);
	HAL_Delay(100);

	//==================================================================
	 // SetDIO3asTCXOCtrl SPI Transaction
		cmnd[0] = 0x97;        // 0x97 is  SetDIO3asTCXOCtrl
		cmnd[1] = 0x00;        //  DIO3 outputs 1.6 V to supply the TCXO
		cmnd[2] = 0x00;
		cmnd[3] = 0x00;
		SX1262_Set_Command(cmnd,answ,4,100,10);
		//err22 = getstatus(SX);
		//==================================================================
	
	if(SX1262_Check_Correct() == 0)
	{
		SX1262_Radio_essental_Config();
	}
}


//**************************************************************************************************************************************************************//
//check if module is working or not
uint8_t SX1262_Check_Correct(void)
{

	cmnd[0] = 0x1D; //OpCode for "read register"
	cmnd[1] = 0x07;
	cmnd[2] = 0x40;
	
	SX1262_Set_Command(cmnd,answ,5,100,0);

	if(err22)
	{
		return(2);
	}
	
	if(answ[4] == 0x14)
	{
		return(0);
	}
	else
	{
		return(1);
	}
	
}
	
//**************************************************************************************************************************************************************//
//wait for module to execute commands
uint8_t SX1262_waitForRadioCommandCompletion(uint32_t timeout) 
{

  uint32_t startTime = HAL_GetTick();
  uint8_t dataTransmitted = 0;

  //Keep checking radio status until it has completed
  while (!dataTransmitted) {
    //Wait some time between spamming SPI status commands, asking if the chip is ready yet
    //Some commands take a bit before the radio even changes into a busy state,
    //so if we check too fast we might pre-maturely think we're done processing the command
    //3ms delay gives inconsistent results.  4ms seems stable.  Using 5ms to be safe
    //HAL_Delay(50);

    //Ask the radio for a status update
    //==================================================================
		cmnd[0] = 0xC0;          //Opcode for "getStatus" command
    cmnd[1] = 0x00;          //Dummy byte, status will overwrite this byte
		
		SX1262_Set_Command(cmnd,answ,2,100,0);
		
    //Parse out the status (see datasheet for what each bit means)
    uint8_t chipMode = (answ[1] >> 4) & 0x7;     //Chip mode is bits [6:4] (3-bits)
    uint8_t commandStatus = (answ[1] >> 1) & 0x7;//Command status is bits [3:1] (3-bits)
    
    //Status 0, 1, 2 mean we're still busy.  Anything else means we're done.
    //Commands 3-6 = command timeout, command processing error, failure to execute command, and Tx Done (respoectively)
    if (commandStatus != 0 && commandStatus != 1 && commandStatus != 2) {
      dataTransmitted = 1;
    }

    //If we're in standby mode, we don't need to wait at all
    //0x03 = STBY_XOSC, 0x02= STBY_RC
    if (chipMode == 0x03 || chipMode == 0x02) {
      dataTransmitted = 1;
    }

    //Avoid infinite loop by implementing a timeout
    if (HAL_GetTick() - startTime >= timeout) {
      return 1;
    }
  }

  //We did it!
  return 0;
}

//**************************************************************************************************************************************************************//
//go to standby mode
void SX1262_setModeStandby(void)
{

	
		cmnd[0] = 0x80;          //Opcode for "SetStatus" command
    cmnd[1] = 0x01;          //Dummy byte, status will overwrite this byte (STDBY_XOSC 1)
		
		SX1262_Set_Command(cmnd,answ,2,100,0);

		SX1262_waitForRadioCommandCompletion(100);

}

//**************************************************************************************************************************************************************//
// go to receive mode
void SX1262_setModeReceive(void) 
{

  //Set packet parameters
  //==================================================================

  cmnd[0] = 0x8C;          //Opcode for "SetPacketParameters"
  cmnd[1] = 0x00;          //PacketParam1 = Preamble Len MSB
  cmnd[2] = 0x0C;          //PacketParam2 = Preamble Len LSB
  cmnd[3] = 0x00;          //PacketParam3 = Header Type. 0x00 = Variable Len, 0x01 = Fixed Length
  cmnd[4] = 0xFF;     		 //PacketParam4 = Payload Length (Max is 255 bytes)
  cmnd[5] = 0x00;          //PacketParam5 = CRC Type. 0x00 = Off, 0x01 = on
  cmnd[6] = 0x00;          //PacketParam6 = Invert IQ.  0x00 = Standard, 0x01 = Inverted
	
	SX1262_Set_Command(cmnd,answ,7,100,0);

	//==================================================================
	// Tell the chip to wait for it to receive a packet.
  // Based on our previous config, this should throw an interrupt when we get a packet
  cmnd[0] = 0x82;          //0x82 is the opcode for "SetRX"
  cmnd[1] = 0xFF;          //24-bit timeout, 0xFFFFFF means no timeout
  cmnd[2] = 0xFF;          // ^^
  cmnd[3] = 0xFF;          // ^^
	SX1262_Set_Command(cmnd,answ,4,100,50);
  //==================================================================

  //Remember that we're in receive mode so we don't need to run this code again unnecessarily
  inReceiveMode = 1;
}

//**************************************************************************************************************************************************************//
//activate RX mode
void SX1262_setRX(void) 
{

  //==================================================================

  cmnd[0] = 0x8C;          //Opcode for "SetPacketParameters"
  cmnd[1] = 0x00;          //PacketParam1 = Preamble Len MSB
  cmnd[2] = 0x0C;          //PacketParam2 = Preamble Len LSB
  cmnd[3] = 0x00;          //PacketParam3 = Header Type. 0x00 = Variable Len, 0x01 = Fixed Length
  cmnd[4] = 0xFF;     //0xFF     //PacketParam4 = Payload Length (Max is 255 bytes)
  cmnd[5] = 0x00;          //PacketParam5 = CRC Type. 0x00 = Off, 0x01 = on
  cmnd[6] = 0x00;          //PacketParam6 = Invert IQ.  0x00 = Standard, 0x01 = Inverted
	
	SX1262_Set_Command(cmnd,answ,7,100,0);
	//==================================================================
	SX1262_waitForRadioCommandCompletion(100);
  //==================================================================
  // Tell the chip to wait for it to receive a packet.
  // Based on our previous config, this should throw an interrupt when we get a packet
  cmnd[0] = 0x82;          //0x82 is the opcode for "SetRX"
  cmnd[1] = 0xFF;          //24-bit timeout, 0xFFFFFF means no timeout
  cmnd[2] = 0xFF;          // ^^
  cmnd[3] = 0xFF;          // ^^
	
	SX1262_Set_Command(cmnd,answ,4,100,0);
  //==================================================================
  SX1262_waitForRadioCommandCompletion(100);
  //==================================================================

  //Remember that we're in receive mode so we don't need to run this code again unnecessarily
  inReceiveMode = 1;
	//==================================================================
}

//**************************************************************************************************************************************************************//
//get module status
uint8_t SX1262_getstatus(void)
{
		uint8_t cmnd2[2] = {0xC0,0x00};          //Opcode for "getStatus" command
		uint8_t answ2[2] = {0};          //Opcode for "getStatus" command
      //Dummy byte, status will overwrite this byte
		SX1262_Set_Command(cmnd2,answ2,2,100,0);
		
    //Parse out the status (see datasheet for what each bit means)
    uint8_t chipMode = (answ2[1] >> 4) & 0x7;     //Chip mode is bits [6:4] (3-bits)
    uint8_t commandStatus = (answ2[1] >> 1) & 0x7;//Command status is bits [3:1] (3-bits)
		Status_Now = chipMode;
		
		return(commandStatus);
}

//**************************************************************************************************************************************************************//
void SX1262_Radio_essental_Config(void)
{
		//==================================================================
		//"SetDIO2AsRfSwitchCtrl"
		//Tell DIO2 to control the RF switch so we don't have to do it manually
		cmnd[0] = 0x9D;		//Opcode for "SetDIO2AsRfSwitchCtrl"
		cmnd[1] = 0x01;   //Enable
	
		SX1262_Set_Command(cmnd,answ,2,100,10);
		//==================================================================
		//Opcode for "SetPacketType"
		cmnd[0] =  0x8A;          //Opcode for "SetPacketType"
		cmnd[1] =  0x01;          //Packet Type: 0x00=GFSK, 0x01=LoRa
		
		SX1262_Set_Command(cmnd,answ,2,100,10);

		//==================================================================
		//set freq for 433000000  => 0x1B100000
		cmnd[0] =  0x86;  //Opcode for set RF Frequencty
		cmnd[1] =  0x1B;
		cmnd[2] =  0x10;
		cmnd[3] =  0x00;
		cmnd[4] =  0x00;
		
		SX1262_Set_Command(cmnd,answ,5,100,10);
		//==================================================================
		 //Set Rx Timeout to reset on SyncWord or Header detection
		cmnd[0] = 0x9F;          //Opcode for "StopTimerOnPreamble"
		cmnd[1] = 0x00;          //Stop timer on:  0x00=SyncWord or header detection, 0x01=preamble detection  SPI.transfer(spiBuff,2);
	
		SX1262_Set_Command(cmnd,answ,2,100,10);
		//==================================================================
		//Set modulation parameters is just one more SPI command, but since it
  //is often called frequently when changing the radio config, it's broken up into its own function
		
		cmnd[0] = 0x8B; //Opcode for "SetModulationParameters"
		cmnd[1] =  7;   //ModParam1 = Spreading Factor.  Can be SF5-SF12, written in hex (0x05-0x0C)
		cmnd[2] =  5;   //ModParam2 = Bandwidth.  See Datasheet 13.4.5.2 for details. 0x00=7.81khz (slowest)
		cmnd[3] =  1;   //ModParam3 = CodingRate.  Semtech recommends CR_4_5 (which is 0x01).  Options are 0x01-0x04, which correspond to coding rate 5-8 respectively
		cmnd[4] =  0;   //LowDataRateOptimize.  0x00 = 0ff, 0x01 = On.  Required to be on for SF11 + SF12
		
		SX1262_Set_Command(cmnd,answ,5,100,10);
		//==================================================================
		// Set PA Config
  // See datasheet 13.1.4 for descriptions and optimal settings recommendations
		cmnd[0] = 0x95;          //Opcode for "SetPaConfig"
		cmnd[1] = 0x04;          //paDutyCycle. See datasheet, set in conjuntion with hpMax
		cmnd[2] = 0x07;          //hpMax.  Basically Tx power.  0x00-0x07 where 0x07 is max power
		cmnd[3] = 0x00;          //device select: 0x00 = SX1262, 0x01 = SX1261
		cmnd[4] = 0x01;          //paLut (reserved, always set to 1)
		
		SX1262_Set_Command(cmnd,answ,5,100,10);
		//==================================================================
		 // Set TX Params
  // See datasheet 13.4.4 for details
		cmnd[0] = 0x8E;          //Opcode for SetTxParams
		cmnd[1] = 22;            //Power.  Can be -17(0xEF) to +14x0E in Low Pow mode.  -9(0xF7) to 22(0x16) in high power mode
		cmnd[2] = 0x02;          //Ramp time. Lookup table.  See table 13-41. 0x02="40uS"
		
		SX1262_Set_Command(cmnd,answ,3,100,10);
		//==================================================================
		//Set LoRa Symbol Number timeout
  //How many symbols are needed for a good receive.
  //Symbols are preamble symbols
		cmnd[0] = 0xA0;          //Opcode for "SetLoRaSymbNumTimeout"
		cmnd[1] = 0x00;          //Number of symbols.  Ping-pong example from Semtech uses 5
		
		SX1262_Set_Command(cmnd,answ,2,100,10);
		//==================================================================
		 //Enable interrupts
		cmnd[0] = 0x08;        //0x08 is the opcode for "SetDioIrqParams"
		cmnd[1] = 0x00;        //IRQMask MSB.  IRQMask is "what interrupts are enabled"
		cmnd[2] = 0x02;        //IRQMask LSB         See datasheet table 13-29 for details
		cmnd[3] = 0xFF;        //DIO1 mask MSB.  Of the interrupts detected, which should be triggered on DIO1 pin
		cmnd[4] = 0xFF;        //DIO1 Mask LSB
		cmnd[5] = 0x00;        //DIO2 Mask MSB
		cmnd[6] = 0x00;        //DIO2 Mask LSB
		cmnd[7] = 0x00;        //DIO3 Mask MSB
		cmnd[8] = 0x00;        //DIO3 Mask LSB
		
		SX1262_Set_Command(cmnd,answ,9,100,10);

		//==================================================================
	 // SetRxTxFallbackMode
		cmnd[0] = 0x93;        // 0x93 is  setfallbackMode
		cmnd[1] = 0x30;        // The radio goes into STDBY_XOSC mode after Tx or Rx
		
		SX1262_Set_Command(cmnd,answ,2,100,10);
	//==================================================================
}


//**************************************************************************************************************************************************************//
//set frequency
void SX1262_SetFrequency(uint32_t frequency)
{
  uint8_t buf[5];

  uint32_t freq = (uint32_t)((double)frequency / (double)FREQ_STEP);
  buf[0] = 0x86; //Opcode for set RF Frequencty
	buf[1] = ((freq >> 24) & 0xFF);
  buf[2] = ((freq >> 16) & 0xFF);
  buf[3] = ((freq >> 8) & 0xFF);
  buf[4] = (freq & 0xFF);
	
	SX1262_Set_Command(buf,answ,5,100,0);
}