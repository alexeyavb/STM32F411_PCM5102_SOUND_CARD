# Debug / Release
CONFIG ?= Release
ifeq ($(CONFIG),Debug)
  CPPFLAGS = -g3 -Wall -Wcpp -Wunused-function -DDEBUG # -DUSE_FULL_ASSERT
else ifeq ($(CONFIG),Release)
  CPPFLAGS = -O3
else
  $(error Invalid CONFIG=$(CONFIG))
endif

# compile with semihosting if Debug is selected
ifeq ($(CONFIG),Debug)
  LDLIBS += -lrdimon
  LDFLAGS += -specs=rdimon.specs
else
  CPPFLAGS += -nostdlib -nostartfiles -fno-builtin -ffreestanding
  C_SRC += libnosys_gnu.c
  LDFLAGS += --specs=nano.specs
endif

# Compilation Flags
LDFLAGS += -Wl,--gc-sections
LDSCRIPT ?= $(OPENWARE)/Hardware/STM32F411CE.ld
LDLIBS += -lc -lm
CPPFLAGS += -Wdouble-promotion -Werror=double-promotion
CPPFLAGS += -fdata-sections
CPPFLAGS += -ffunction-sections
CPPFLAGS += -fno-builtin -ffreestanding
LDFLAGS += -fno-builtin -ffreestanding
CXXFLAGS = -fno-rtti -fno-exceptions -std=gnu++17
CFLAGS  += -std=gnu99
ARCH_FLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS += -fsingle-precision-constant
DEF_FLAGS = -DSTM32F411CE -DARM_MATH_CM4 -DUSE_MATH_FF
DEF_FLAGS += -D__FPU_PRESENT=1U
# S_SRC = $(OPENWARE)/Hardware/startup_stm32f411xe.s
