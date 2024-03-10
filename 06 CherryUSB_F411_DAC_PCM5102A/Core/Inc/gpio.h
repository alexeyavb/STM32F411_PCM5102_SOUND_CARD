/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#define I2S2_MUTE_CTRL_Pin                                      GPIO_PIN_2
#define I2S2_MUTE_CTRL_GPIO_Port                                GPIOB
#define AUDIO_MUTE_PORT_ENABLE()                    		        __HAL_RCC_GPIOB_CLK_ENABLE()
#define AUDIO_MUTE_ON()                                         HAL_GPIO_WritePin(I2S2_MUTE_CTRL_GPIO_Port, I2S2_MUTE_CTRL_Pin, GPIO_PIN_RESET)
#define AUDIO_MUTE_OFF()                                        HAL_GPIO_WritePin(I2S2_MUTE_CTRL_GPIO_Port, I2S2_MUTE_CTRL_Pin, GPIO_PIN_SET)

// #define LCD_SPI5_RS_PIN_Pin GPIO_PIN_6
#define LCD_SPI5_RST_PIN_Pin GPIO_PIN_7
#define LCD_SPI5_RST_PIN_GPIO_Port GPIOB
#define LCD_SPI5_RS_PIN_Pin GPIO_PIN_8
#define LCD_SPI5_RS_PIN_GPIO_Port GPIOB
#define LCD_SPI5_CS_PIN_Pin GPIO_PIN_9
#define LCD_SPI5_CS_PIN_GPIO_Port GPIOB
#define LCD_LED_LEVEL_Pin GPIO_PIN_6
#define LCD_LED_LEVEL_GPIO_Port GPIOB
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

