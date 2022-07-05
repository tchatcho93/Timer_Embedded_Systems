PROJECT =led
BUILD_DIR = bin

CFILES = main.c
#CFILES += systick.c

# TODO - you will need to edit these two lines!
DEVICE=stm32l152re
# OOCD_FILE = board/stm32f4discovery.cfg

LDSCRIPT = ./stm32-clicker.ld
LDFLAGS += -u _printf_float

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ./rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
