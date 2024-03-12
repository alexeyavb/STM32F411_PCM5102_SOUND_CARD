#include <memory.h>
#include <cmsis_os2.h>
#include "i2s.h"
#include "i2s_ex.h"
// @brief This worked direct transmission
// #define MIN_SAMPLES_FOR 16U
// #define RX_BUFFER_SZ ((MIN_SAMPLES_FOR*sizeof(uint16_t)*256U)+2U)
// @brief This worked direct transmission
#define MIN_SAMPLES_FOR 4U
#define RX_BUFFER_SZ ((MIN_SAMPLES_FOR*sizeof(uint16_t)*256U)+2U)

static uint16_t tmpBuffer[RX_BUFFER_SZ];
/**
 * @brief additional func for I2SPR set
*/
static inline HAL_StatusTypeDef I2S_Config_I2SPR(I2S_HandleTypeDef *hi2s, uint32_t regVal) {

    uint32_t tickstart = 0U;

    __HAL_RCC_PLLI2S_DISABLE();
    tickstart = HAL_GetTick();

    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLI2SRDY)  != RESET) {
        if((HAL_GetTick() - tickstart ) > PLLI2S_TIMEOUT_VALUE) {
            return HAL_TIMEOUT;
        }
    }

    // SPI2->I2SPR = regVal;
    hi2s->Instance->I2SPR = regVal;

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
  * @brief  Clock Config, assumes input to PLL I2S Block = 1MHz
  * @param
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @note   This API is called by BSP_AUDIO_OUT_Init() and BSP_AUDIO_OUT_SetFrequency()
  *         Being __weak it can be overwritten by the application
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
void I2S_BUS_ClockConfig(I2S_HandleTypeDef *hi2s, uint32_t AudioFreq, void *Params) {
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
    I2S_Config_I2SPR(hi2s, I2S_PR);
    }
  else { // Default PLL I2S configuration for 96000 Hz 24bit  
    N = I2S_Clk_Config24[2].N;
    R = I2S_Clk_Config24[2].R;
    I2SDIV = I2S_Clk_Config24[2].I2SDIV;
    ODD = I2S_Clk_Config24[2].ODD;
    
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
    I2S_Config_I2SPR(hi2s, I2S_PR);
  }
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
    if(hi2s->Instance == SPI3){
        uint16_t rxBuffer[RX_BUFFER_SZ];
        memcpy(rxBuffer, tmpBuffer, RX_BUFFER_SZ);
        // HAL_I2S_Transmit_DMA(&hi2s2, tmpBuffer, RX_BUFFER_SZ);
        HAL_I2S_Transmit_DMA(&hi2s2, tmpBuffer, RX_BUFFER_SZ);
    }
}

// void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
//     if(hi2s->Instance == SPI3){
//         memcpy(rxBuffer, tmpBuffer, RX_BUFFER_SZ/2);
//         HAL_I2S_Transmit_DMA(&hi2s2, rxBuffer, RX_BUFFER_SZ/2);
//     }
// }

void StartRezerved3Task(void *argument){
    AUDIO_MUTE_OFF();
    // extern osStatust osDelay(int delay);
    // HAL_I2S_Receive_DMA(&hi2s3, tmpBuffer, RX_BUFFER_SZ);
    HAL_I2S_Receive_DMA(&hi2s3, tmpBuffer, RX_BUFFER_SZ);
    for(;;)
    {    
        osDelay(1);
    }
}