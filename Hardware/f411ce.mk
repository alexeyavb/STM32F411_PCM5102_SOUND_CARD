# Library path
LIBROOT=$(OPENWARE)/Libraries/Drivers

# Build path
BUILD=$(BUILDROOT)/build

# Tool path
OPENOCD ?= openocd -f $(OPENWARE)/Hardware/openocd_f4.cfg

# Code Paths
DRIVERS=$(LIBROOT)/STM32F4xx_HAL_Driver
CHERRY=$(OPENWARE)/Libraries/CherryUSB
CMSIS_DEVICE=$(LIBROOT)/CMSIS/Device/ST/STM32F4xx
CMSIS_CORE=$(LIBROOT)/CMSIS/Include
DSPLIB=$(LIBROOT)/CMSIS/DSP/Source
# USB_DEVICE_FILE=$(OPENWARE)/Libraries/Middlewares/ST/STM32_USB_Device_Library
# USB_HOST_FILE=$(OPENWARE)/Libraries/Middlewares/ST/STM32_USB_Host_Library
FREERTOS_DIR=$(OPENWARE)/Libraries/Middlewares/Third_Party/FreeRTOS/Source
SYSCALLS_DIR=$(OPENWARE)/Libraries/syscalls

INC_FLAGS = -I$(CMSIS_CORE) -I$(CMSIS_DEVICE)/Include -I$(DRIVERS)/Inc
INC_FLAGS += -I$(OPENWARE)/Source -I$(BUILDROOT)/Inc
# INC_FLAGS += -I$(USB_HOST_FILE)/Core/Inc
# INC_FLAGS += -I$(USB_HOST_FILE)/Class/HID/Inc
# INC_FLAGS += -I$(USB_DEVICE_FILE)/Core/Inc
INC_FLAGS += -I$(CHERRY)/common/
INC_FLAGS += -I$(CHERRY)/core/
INC_FLAGS += -I$(CHERRY)/class/cdc/
INC_FLAGS += -I$(CHERRY)/class/audio/
INC_FLAGS += -I$(CHERRY)/class/audio/
INC_FLAGS += -I$(CHERRY)/class/hub/
INC_FLAGS += -I$(CHERRY)/class/msc/
INC_FLAGS += -I$(CHERRY)/port/dwc2/
INC_FLAGS += -I$(CHERRY)/port/fsdev/
INC_FLAGS += -I$(FREERTOS_DIR)/include/
INC_FLAGS += -I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F/
INC_FLAGS += -I$(FREERTOS_DIR)/CMSIS_RTOS_V2/
INC_FLAGS += -I$(LIBROOT)/CMSIS/DSP/Include/
INC_FLAGS += -I$(BUILDROOT)/Core/Inc/
INC_FLAGS += -I$(BUILDROOT)/Bsp/Inc/
INC_FLAGS += -I$(BUILDROOT)/Drivers/Inc/
CPPFLAGS += -mtune=cortex-m4
CFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
CXXFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
LDFLAGS += -T$(LDSCRIPT) $(ARCH_FLAGS)

include $(OPENWARE)/Hardware/f411ce-libs.mk
include $(OPENWARE)/Hardware/common.mk
