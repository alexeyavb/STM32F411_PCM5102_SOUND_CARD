BUILDROOT = .
OPENWARE ?= $(BUILDROOT)/..

include $(OPENWARE)/Hardware/STM32F411CE.mk

C_SRC = $(wildcard Core/Src/*.c)
CPP_SRC = $(wildcard Core/Src/*.cpp)

C_BSP_SRC = $(wildcard Bsp/Src/*.c)
CPP_BSP_SRC = $(wildcard Bsp/Src/*.cpp)

ifndef PLATFORM
# Available values 
# SoundCard - without RTOS
# Modular with RTOS
PLATFORM = SoundCard
endif

ifeq ($(PLATFORM),SoundCard)
  PROJECT = simple_adc_dac
  CPPFLAGS += -DUSE_HAL_DRIVER -DUSE_MATH_FF -DUSE_USB_FS -DDEBUG
#  C_SRC += $(C_SRC_SYSTEM)
#  C_SRC += $(C_SRC_LNOSYS)
else ifeq ($(PLATFORM),Modular)
  PROJECT = modular_adc_dac
  CPPFLAGS += -DUSE_HAL_DRIVER -DUSE_MATH_FF -DUSE_USB_FS -DDEBUG -DUSE_RTOS
  C_SRC += $(C_SRC_OS)
else
  $(error Invalid PLATFORM=$(PLATFORM))
endif

include $(OPENWARE)/Hardware/sources.mk

C_SRC += $(C_SRC_I2S)
C_SRC += $(C_SRC_DSP)
C_SRC += $(C_SRC_UART)
C_SRC += $(C_SRC_USART)
C_SRC += $(C_SRC_USBD)
C_SRC += $(C_SRC_CHRY_USB_CORE)
C_SRC += $(C_SRC_CHRY_USB_PORT_DWC2)
C_SRC += $(C_SRC_CHRY_USB_CLASS_AUDIO)
C_SRC += $(C_BSP_SRC)
# C_SRC += $(C_SRC_MIC_SPK_MCH_V2_AUDIO_DMO_TEMPLATE)

include $(OPENWARE)/Hardware/f411ce.mk

DFUCMD = dfu-util -d 0483:df11 -c 1 -i 0 -a 0 -R
dfu: bin
	@echo Flashing OWL $(PLATFORM) $(CONFIG) firmware
	$(DFUCMD) -s 0x8000000:leave -D $(BIN)
