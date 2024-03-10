/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2s.c
  * @brief   This file provides code for the configuration
  *          of the I2S instances.
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
/* Includes ------------------------------------------------------------------*/

#include "i2s.h"
/* USER CODE BEGIN 0 */
static uint32_t AudioFrqDef  = I2S_AUDIOFREQ_48K;

static HAL_StatusTypeDef I2S_Config_I2SPR(uint32_t regVal);
void I2Sx_Init(uint32_t AudioFreq);
void I2Sx_DeInit(void);
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
  
#endif

/* USER CODE END 0 */

I2S_HandleTypeDef hi2s1;
I2S_HandleTypeDef hi2s2;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi2_tx;

/* I2S1 init function */
void MX_I2S1_Init(void)
{
  return;

  /* USER CODE BEGIN I2S1_Init 0 */

  /* USER CODE END I2S1_Init 0 */

  /* USER CODE BEGIN I2S1_Init 1 */

  /* USER CODE END I2S1_Init 1 */
  hi2s1.Instance = SPI1;
  hi2s1.Init.Mode = I2S_MODE_SLAVE_TX;
  hi2s1.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s1.Init.DataFormat = I2S_DATAFORMAT_16B_EXTENDED;
  hi2s1.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s1.Init.AudioFreq = I2S_AUDIOFREQ_48K;
  hi2s1.Init.CPOL = I2S_CPOL_LOW;
  hi2s1.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s1.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S1_Init 2 */

  /* USER CODE END I2S1_Init 2 */

}
/* I2S2 init function */
void MX_I2S2_Init(void)
{

  /* USER CODE BEGIN I2S2_Init 0 */

  /* USER CODE END I2S2_Init 0 */

  /* USER CODE BEGIN I2S2_Init 1 */

  /* USER CODE END I2S2_Init 1 */
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILLIPS;
  // hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B; // do not use
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B_EXTENDED;
  // hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B; // I2S_DATAFORMAT_16B_EXTENDED; //I2S_DATAFORMAT_24B;
  // hi2s2.Init.DataFormat = I2S_DATAFORMAT_32B; // do not use
  
// #ifdef USE_MCLK_OUT  
//   hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
// #else
//   hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
// #endif

#if defined(STM32F411xE) && defined(USE_MCLK_OUT)
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
#else
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
#endif
  // 48K Default
  hi2s2.Init.AudioFreq = AudioFrqDef;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S2_Init 2 */

  /* USER CODE END I2S2_Init 2 */

}

void HAL_I2S_MspInit(I2S_HandleTypeDef* i2sHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2sHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */
    return;
  /* USER CODE END SPI1_MspInit 0 */
    /* I2S1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**I2S1 GPIO Configuration
    PA4     ------> I2S1_WS
    PA5     ------> I2S1_CK
    PA7     ------> I2S1_SD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* I2S1 DMA Init */
    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA2_Stream2;
    hdma_spi1_tx.Init.Channel = DMA_CHANNEL_2;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL; //DMA_CIRCULAR;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_spi1_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_spi1_tx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_spi1_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(i2sHandle,hdmatx,hdma_spi1_tx);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
  else if(i2sHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspInit 0 */

  /* USER CODE END SPI2_MspInit 0 */
    /* I2S2 clock enable */
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2S2 GPIO Configuration
    PA6     ------> I2S2_MCK
    PB12     ------> I2S2_WS
    PB13     ------> I2S2_CK
    PB15     ------> I2S2_SD
    */
   
#ifdef USE_MCLK_OUT   
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_SPI2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2S2 DMA Init */

    /* SPI2_TX Init */
    hdma_spi2_tx.Instance = DMA1_Stream4;
    hdma_spi2_tx.Init.Channel = DMA_CHANNEL_0;
    hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi2_tx.Init.Mode =  DMA_CIRCULAR;
    hdma_spi2_tx.Init.Priority =  DMA_PRIORITY_LOW;
    hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_spi2_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_spi2_tx.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_spi2_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
    if (HAL_DMA_Init(&hdma_spi2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(i2sHandle,hdmatx,hdma_spi2_tx);

  /* USER CODE BEGIN SPI2_MspInit 1 */
  /* USER CODE END SPI2_MspInit 1 */
  }
}

void HAL_I2S_MspDeInit(I2S_HandleTypeDef* i2sHandle)
{

  if(i2sHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**I2S1 GPIO Configuration
    PA4     ------> I2S1_WS
    PA5     ------> I2S1_CK
    PA7     ------> I2S1_SD
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7);

    /* I2S1 DMA DeInit */
    HAL_DMA_DeInit(i2sHandle->hdmatx);

    /* I2S1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SPI1_IRQn);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
  else if(i2sHandle->Instance==SPI2)
  {
  /* USER CODE BEGIN SPI2_MspDeInit 0 */

  /* USER CODE END SPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI2_CLK_DISABLE();

    /**I2S2 GPIO Configuration
    PA6     ------> I2S2_MCK
    PB12     ------> I2S2_WS
    PB13     ------> I2S2_CK
    PB15     ------> I2S2_SD
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_15);

    /* I2S2 DMA DeInit */
    HAL_DMA_DeInit(i2sHandle->hdmatx);

    /* I2S2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(SPI2_IRQn);
  /* USER CODE BEGIN SPI2_MspDeInit 1 */

  /* USER CODE END SPI2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
  * @brief  Clock Config, assumes input to PLL I2S Block = 1MHz
  * @param
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @note   This API is called by BSP_AUDIO_OUT_Init() and BSP_AUDIO_OUT_SetFrequency()
  *         Being __weak it can be overwritten by the application
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_AUDIO_OUT_ClockConfig(I2S_HandleTypeDef *hi2s, uint32_t AudioFreq, void *Params) {
  RCC_PeriphCLKInitTypeDef RCC_ExCLKInitStruct;
  int index = 0, freqindex = -1;
    
  for(index = 0; index < 3; index++)  {
          if (I2SFreq[index] == AudioFreq) {
                  freqindex = index;
                  break;
                  }
          }
  uint32_t N, R, I2SDIV, ODD, I2S_PR;
#ifdef STM32F411xE
  uint32_t MCKOE;
#ifdef USE_MCLK_OUT
    MCKOE = 1;
#else
    MCKOE = 0;
#endif
#endif
// PLLI2S_VCO = f(VCO clock) = f(PLLI2S clock input)  (PLLI2SN/PLLM)
// I2SCLK = f(PLLI2S clock output) = f(VCO clock) / PLLI2SR
    
  HAL_RCCEx_GetPeriphCLKConfig(&RCC_ExCLKInitStruct);
  if (freqindex != -1)  {
    N = I2S_Clk_Config24[freqindex].N;
    R = I2S_Clk_Config24[freqindex].R;
    I2SDIV = I2S_Clk_Config24[freqindex].I2SDIV;
    ODD = I2S_Clk_Config24[freqindex].ODD;

    RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
#ifdef STM32F411xE
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SM = 25;
#endif
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = N;
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SR = R;
    HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct);
#ifdef STM32F411xE
    I2S_PR = (MCKOE<<9) | (ODD<<8) | I2SDIV;
#else
    I2S_PR = (ODD<<8) | I2SDIV;
#endif
    I2S_Config_I2SPR(I2S_PR);
  }
  UNUSED(Params);
}

static HAL_StatusTypeDef I2S_Config_I2SPR(uint32_t regVal) {
uint32_t tickstart = 0U;
    __HAL_RCC_PLLI2S_DISABLE();
    tickstart = HAL_GetTick();
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET) {
      if((HAL_GetTick() - tickstart ) > PLLI2S_TIMEOUT_VALUE) {
         return HAL_TIMEOUT;
         }
      }

    SPI2->I2SPR = regVal;

    __HAL_RCC_PLLI2S_ENABLE();
    tickstart = HAL_GetTick();
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  == RESET)    {
      if((HAL_GetTick() - tickstart ) > PLLI2S_TIMEOUT_VALUE)      {
        return HAL_TIMEOUT;
      }
    }
   return HAL_OK;
}


  
/**
  * @brief  Initializes the Audio Codec audio interface (I2S).
  * dataFormat : I2S_DATAFORMAT_16B, I2S_DATAFORMAT_24B
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral.
  */
void I2Sx_Init(uint32_t AudioFreq) {
  __HAL_I2S_DISABLE(&hi2s2);    
  AudioFrqDef = AudioFreq;
  MX_I2S2_Init();
}


/**
  * @brief  Deinitialize the Audio Codec audio interface (I2S).
  */
void I2Sx_DeInit(void) {  
  __HAL_I2S_DISABLE(&hi2s2);
  HAL_I2S_DeInit(&hi2s2);
}
    

/* USER CODE END 1 */
