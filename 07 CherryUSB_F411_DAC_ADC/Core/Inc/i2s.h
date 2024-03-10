/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2s.h
  * @brief   This file contains all the function prototypes for
  *          the i2s.c file
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
#include <stdint.h>
 /**
  * PLL FRQ
const uint32_t I2SFreq[3] = {44100, 48000, 96000};
#if defined(STM32F411xE) && defined(USE_MCLK_OUT) // Makefile compile flag
const I2S_CLK_CONFIG I2S_Clk_Config24[3]  = {
{271, 2, 6, 0, 0x0B06EAB0}, // 44.1081
{258, 3, 3, 1, 0x0BFF6DB2}, // 47.9911
{344, 2, 3, 1, 0x17FEDB64}  // 95.9821
};
#else
const I2S_CLK_CONFIG I2S_Clk_Config24[3]  = {
{429, 4, 19, 0, 0x0B065E56}, // 44.0995  
{384, 5, 12, 1, 0x0C000000}, // 48.0000  
{424, 3, 11, 1, 0x1800ED70}  // 96.0144  
};
  * 
 */
typedef struct I2S_CLK_CONFIG_ {
        uint32_t N;
        uint32_t R;
        uint32_t I2SDIV;
        uint32_t ODD;
        uint32_t nominal_fdbk;
} I2S_CLK_CONFIG;

extern const I2S_CLK_CONFIG I2S_Clk_Config24[];
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2S_H__
#define __I2S_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stm32f4xx_hal_i2s.h>
#include <stm32f4xx_hal_i2s_ex.h>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2S_HandleTypeDef hi2s1;

extern I2S_HandleTypeDef hi2s2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_I2S1_Init(void);
void MX_I2S2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2S_H__ */

