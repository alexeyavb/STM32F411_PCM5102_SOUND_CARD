#ifndef _I2S_EX_H__
#define _I2S_EX_H__
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>

#ifndef I2S2_MUTE_CTRL_Pin
#define I2S2_MUTE_CTRL_Pin GPIO_PIN_2
#define I2S2_MUTE_CTRL_GPIO_Port GPIOB
#endif

#define AUDIO_MUTE_PIN                                          I2S2_MUTE_CTRL_Pin
#define AUDIO_MUTE_PORT                                         I2S2_MUTE_CTRL_GPIO_Port
#define AUDIO_MUTE_PORT_ENABLE()                                __HAL_RCC_GPIOB_CLK_ENABLE()
#define AUDIO_MUTE_ON()                                         HAL_GPIO_WritePin(AUDIO_MUTE_PORT, AUDIO_MUTE_PIN, GPIO_PIN_RESET)
#define AUDIO_MUTE_OFF()                                        HAL_GPIO_WritePin(AUDIO_MUTE_PORT, AUDIO_MUTE_PIN, GPIO_PIN_SET)

typedef struct I2S_CLK_CONFIG_ {
        uint32_t N;
        uint32_t R;
        uint32_t I2SDIV;
        uint32_t ODD;
        uint32_t nominal_fdbk;
} I2S_CLK_CONFIG;

#if defined(STM32F411xE) && defined(USE_MCLK_OUT) // Makefile compile flags
// for 32bit I2S frame
#define AUDIO_CLOCKS_AVAILABLE 3
const uint32_t I2SFreq[AUDIO_CLOCKS_AVAILABLE] = {44100, 48000, 96000};
const I2S_CLK_CONFIG I2S_Clk_Config24[AUDIO_CLOCKS_AVAILABLE]  = {
    {271, 2, 6, 0, 0x0B06EAB0},     // 44.1081
    {258, 3, 3, 1, 0x0BFF6DB2},     // 47.9911
    {344, 2, 3, 1, 0x17FEDB64},     // 95.9821
};
#else
// for 32bit I2S frame
#define AUDIO_CLOCKS_AVAILABLE 4
const uint32_t I2SFreq[AUDIO_CLOCKS_AVAILABLE] = {44100, 48000, 96000, 192000};
const I2S_CLK_CONFIG I2S_Clk_Config24[AUDIO_CLOCKS_AVAILABLE]  = {
    {429, 4, 19, 0, 0x0B065E56},    // 44.0995
    {384, 5, 12, 1, 0x0C000000},    // 48.0000
    {424, 3, 11, 1, 0x1800ED70},    // 96.0144
    {258, 3, 3, 1,  0x3001DAE0}     // 192.0288
};
#endif

#ifdef __cplusplus
}
#endif

#endif // _I2S_EX_H__
