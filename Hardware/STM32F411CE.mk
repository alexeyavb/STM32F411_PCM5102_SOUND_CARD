# Debug / Release
CONFIG ?= Debug
ifeq ($(CONFIG),Debug)
  CPPFLAGS = -O0 -g -ggdb -Wall -Wcpp -Wunused-function -DDEBUG # -DUSE_FULL_ASSERT
else ifeq ($(CONFIG),Release)
  CPPFLAGS = -O3
else
  $(error Invalid CONFIG=$(CONFIG))
endif

# compile with semihosting if Debug is selected
ifeq ($(CONFIG),Debug)
  LDLIBS += -lrdimon
  LDFLAGS += -specs=rdimon.specs
#   C_SRC += libnosys_gnu.c
else
  CPPFLAGS += -nostdlib -nostartfiles -fno-builtin -ffreestanding
#  C_SRC += libnosys_gnu.c
  LDFLAGS += --specs=nano.specs
endif

# Compilation Flags
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,-u,vfprintf
LDFLAGS += -Wl,-u,_printf_float
LDFLAGS += -Wl,-u,_scanf_float

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
DEF_FLAGS = -DSTM32F411xE -DARM_MATH_CM4 -DUSE_MATH_FF -DUSE_HAL_DRIVER
DEF_FLAGS += -D__FPU_PRESENT=1U
# S_SRC = $(OPENWARE)/Source/STM32F411CE.s
S_SRC = $(OPENWARE)/Hardware/startup_stm32f411xe.s
