# object files

C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_cortex.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_gpio.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_rcc.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_dma.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_adc.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_tim.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_spi.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_flash.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_adc_ex.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_dma_ex.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_pwr_ex.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_rcc_ex.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_flash_ex.c
C_SRC += $(DRIVERS)/Src/stm32f4xx_hal_tim_ex.c

# optionals
C_SRC_UART = $(DRIVERS)/Src/stm32f4xx_hal_uart.c
C_SRC_UART += $(DRIVERS)/Src/stm32f4xx_hal_usart.c
# dac
C_SRC_DAC = $(DRIVERS)/Src/stm32f4xx_hal_dac.c
C_SRC_DAC += $(DRIVERS)/Src/stm32f4xx_hal_dac_ex.c
# CRC
C_SRC_CRC = $(DRIVERS)/Src/stm32f4xx_hal_crc.c

# RTC
C_SRC_RTC = $(DRIVERS)/Src/stm32f4xx_hal_rtc.c
C_SRC_RTC += $(DRIVERS)/Src/stm32f4xx_hal_pwr.c
C_SRC_RTC += $(DRIVERS)/Src/stm32f4xx_hal_rtc_ex.c

# IWDG
C_SRC_IWDG = $(DRIVERS)/Src/stm32f4xx_hal_iwdg.c

# external SDRAM
C_SRC_SDRAM = $(DRIVERS)/Src/stm32f4xx_hal_sdram.c
C_SRC_SDRAM += $(DRIVERS)/Src/stm32f4xx_ll_fmc.c

# required by OWL 1
C_SRC_SRAM = $(DRIVERS)/Src/stm32f4xx_hal_sram.c
C_SRC_SRAM += $(DRIVERS)/Src/stm32f4xx_ll_fsmc.c

# I2S
C_SRC_I2S = $(DRIVERS)/Src/stm32f4xx_hal_i2s.c
C_SRC_I2S += $(DRIVERS)/Src/stm32f4xx_hal_i2s_ex.c

# I2C
C_SRC_I2C = $(DRIVERS)/Src/stm32f4xx_hal_i2c.c
C_SRC_I2C += $(DRIVERS)/Src/stm32f4xx_hal_i2c_ex.c

# USB PCD & USB_LL Device Library ###
C_SRC_USBD = $(DRIVERS)/Src/stm32f4xx_hal_pcd.c
C_SRC_USBD += $(DRIVERS)/Src/stm32f4xx_hal_pcd_ex.c
C_SRC_USBD += $(DRIVERS)/Src/stm32f4xx_ll_usb.c

# system if need (normally placed in in src)
C_SRC_SYSTEM = $(CMSIS_DEVICE)/Source/Templates/system_stm32f4xx.c

# ST USBD LIB
# C_SRC_USBD += $(USB_DEVICE_FILE)/Core/Src/usbd_core.c
# C_SRC_USBD += $(USB_DEVICE_FILE)/Core/Src/usbd_ioreq.c
# C_SRC_USBD += $(USB_DEVICE_FILE)/Core/Src/usbd_ctlreq.c

### USB Host Library ###
# C_SRC_USBH = $(DRIVERS)/Src/stm32f4xx_hal_hcd.c
# C_SRC_USBH += $(USB_HOST_FILE)/Core/Src/usbh_core.c
# C_SRC_USBH += $(USB_HOST_FILE)/Core/Src/usbh_pipes.c
# C_SRC_USBH += $(USB_HOST_FILE)/Core/Src/usbh_ioreq.c
# C_SRC_USBH += $(USB_HOST_FILE)/Core/Src/usbh_ctlreq.c
# C_SRC_USBH_HID = $(wildcard $(USB_HOST_FILE)/Class/HID/Src/*.c)

### CMSIS DSP Library ####
C_SRC_DSP = $(DSPLIB)/FastMathFunctions/arm_sin_f32.c
C_SRC_DSP += $(DSPLIB)/FastMathFunctions/arm_cos_f32.c
C_SRC_DSP += $(DSPLIB)/CommonTables/arm_common_tables.c
C_SRC_DSP += $(DSPLIB)/TransformFunctions/arm_cfft_f32.c
C_SRC_DSP += $(DSPLIB)/TransformFunctions/arm_cfft_radix8_f32.c
C_SRC_DSP += $(DSPLIB)/TransformFunctions/arm_bitreversal.c
C_SRC_DSP += $(DSPLIB)/TransformFunctions/arm_rfft_fast_f32.c
C_SRC_DSP += $(DSPLIB)/TransformFunctions/arm_rfft_fast_init_f32.c
C_SRC_DSP += $(DSPLIB)/CommonTables/arm_const_structs.c

# C_SRC += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_init_f32.c
# C_SRC += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_f32.c

# C_SRC += $(DSPLIB)/SupportFunctions/arm_copy_f32.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_float_to_q31.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_q31_to_float.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_float_to_q15.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_q15_to_float.c

# C_SRC += $(DSPLIB)/FastMathFunctions/arm_sin_f32.c
# C_SRC += $(DSPLIB)/FastMathFunctions/arm_cos_f32.c
# C_SRC += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_f32.c
# C_SRC += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_init_f32.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_float_to_q31.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_q31_to_float.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_float_to_q15.c
# C_SRC += $(DSPLIB)/SupportFunctions/arm_q15_to_float.c

### FreeRTOS ###
# C_SRC_OS  = $(OPENWARE)/Source/freertos.c
# C_SRC_OS += $(FREERTOS_DIR)/CMSIS_RTOS/cmsis_os.c
# C_SRC_OS += $(FREERTOS_DIR)/portable/GCC/ARM_CM4F/port.c
# C_SRC_OS += $(FREERTOS_DIR)/tasks.c
# C_SRC_OS += $(FREERTOS_DIR)/timers.c
# C_SRC_OS += $(FREERTOS_DIR)/queue.c
# C_SRC_OS += $(FREERTOS_DIR)/list.c
# C_SRC_OS += $(FREERTOS_DIR)/croutine.c
# C_SRC_OS += $(FREERTOS_DIR)/portable/MemMang/heap_4.c

# C_SRC_USBD_AUDIO = $(OPENWARE)/Source/usb_device.c
# C_SRC_USBD_AUDIO += $(OPENWARE)/Source/usbd_conf.c
# C_SRC_USBD_AUDIO += $(OPENWARE)/Source/usbd_desc.c
# C_SRC_USBD_AUDIO += $(OPENWARE)/Source/usbd_audio.c

# C_SRC_USBH_MIDI = $(OPENWARE)/Source/usb_host.c
# C_SRC_USBH_MIDI += $(OPENWARE)/Source/usbh_conf.c
# C_SRC_USBH_MIDI += $(OPENWARE)/Source/usbh_midi.c

# HAL SYSTEM
C_SRC_SYSTEM = $(DRIVERS)/system_stm32f4xx.c
C_SRC_LNOSYS = $(SYSCALLS_DIR)/libnosys_gnu.c
C_SRC_LNOSYS += $(SYSCALLS_DIR)/libnosys_write.c

# CHERRY USB

C_SRC_CHRY_USB_CORE = $(CHERRY)/core/usbd_core.c
C_SRC_CHRY_USB_OSAL = $(CHERRY)/osal/usb_osal_rtems.c
# C_SRC_CHRY_USB_OSAL += $(CHERRY)/osal/usb_osal_freertos.c
# C_SRC_CHRY_USB_OSAL += $(CHERRY)/osal/usb_osal_rtthread.c
# C_SRC_CHRY_USB_OSAL += $(CHERRY)/osal/usb_osal_yoc.c

# FOR F103 USE FSDEV
C_SRC_CHRY_USB_PORT_FSDEV = $(CHERRY)/port/fsdev/usb_dc_fsdev.c

#FOR F411 USE DWC2
C_SRC_CHRY_USB_PORT_DWC2  = $(CHERRY)/port/dwc2/usb_dc_dwc2.c
C_SRC_CHRY_USB_PORT_DWC2  += $(CHERRY)/port/dwc2/usb_hc_dwc2.c
C_SRC_CHRY_USB_PORT_DWC2  += $(CHERRY)/port/dwc2/usb_glue_st.c

C_SRC_CHRY_USB_CLASS_CDC = $(CHERRY)/class/cdc/usbd_cdc.c
C_SRC_CHRY_USB_CLASS_CDC += $(CHERRY)/class/cdc/usbd_cdc_ecm.c

C_SRC_CHRY_USB_CLASS_AUDIO = $(CHERRY)/class/audio/usbd_audio.c

# USB HIGH_SPEED
# C_SRC_CHRY_USBH_CORE = $(CHERRY)/core/usbh_core.c
# C_SRC_CHRY_USBH_CLASS = $(CHERRY)/class/audio/usbdh_audio.c
# C_SRC_CHRY_USBH_CLASS += $(CHERRY)/class/hub/usbdh_hub.c
