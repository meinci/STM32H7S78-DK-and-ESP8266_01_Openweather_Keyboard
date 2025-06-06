/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32h7rsxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define FRAME_RATE_Pin GPIO_PIN_3
#define FRAME_RATE_GPIO_Port GPIOF
#define RENDER_TIME_Pin GPIO_PIN_2
#define RENDER_TIME_GPIO_Port GPIOF
#define MCU_ACTIVE_Pin GPIO_PIN_4
#define MCU_ACTIVE_GPIO_Port GPIOF
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOM
#define VSYNC_FREQ_Pin GPIO_PIN_1
#define VSYNC_FREQ_GPIO_Port GPIOF
#define LCD_EN_Pin GPIO_PIN_15
#define LCD_EN_GPIO_Port GPIOE
#define TP_IRQ_Pin GPIO_PIN_3
#define TP_IRQ_GPIO_Port GPIOE
#define TP_IRQ_EXTI_IRQn EXTI3_IRQn
#define LCD_BL_CTRL_Pin GPIO_PIN_15
#define LCD_BL_CTRL_GPIO_Port GPIOG
#define ESP8266_EN_Pin GPIO_PIN_13
#define ESP8266_EN_GPIO_Port GPIOF

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
