/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern volatile uint8_t Rec_int_flg;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NRESET_LORA_Pin GPIO_PIN_0
#define NRESET_LORA_GPIO_Port GPIOA
#define DI03_LORA_Pin GPIO_PIN_1
#define DI03_LORA_GPIO_Port GPIOA
#define DI03_LORA_EXTI_IRQn EXTI0_1_IRQn
#define BUSY_LORA_Pin GPIO_PIN_2
#define BUSY_LORA_GPIO_Port GPIOA
#define DI01_LORA_Pin GPIO_PIN_3
#define DI01_LORA_GPIO_Port GPIOA
#define DI01_LORA_EXTI_IRQn EXTI2_3_IRQn
#define NSS_LORA_Pin GPIO_PIN_4
#define NSS_LORA_GPIO_Port GPIOA
#define SCK_LORA_Pin GPIO_PIN_5
#define SCK_LORA_GPIO_Port GPIOA
#define MISO_LORA_Pin GPIO_PIN_6
#define MISO_LORA_GPIO_Port GPIOA
#define MOSI_LORA_Pin GPIO_PIN_7
#define MOSI_LORA_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
