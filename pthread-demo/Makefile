
# these may be set from the command line

BOARD ?= uemb1

PROJECT_NAME ?= pthread-demo
APP_ADDRESS_OFFSET ?= 0x00000
USE_MINSTDIO_FLOAT_SUPPORT = 1
DEBUG_PRINTF_EXCEPTIONS = 1
USE_FULL_ASSERT = 1

APPDIR = .

## project source
SOURCE = $(APPDIR)/main.c


CFLAGS =

# configuration headers
CFLAGS += -I $(APPDIR)/config

USE_PTHREADS = 1
USE_FREERTOS= 1
USE_MINLIBC = 1
USE_LOGGER = 1
USE_LOGGER_TIMESTAMP = 1
USE_DRIVER_SYSTEM_TIMER = 1
USE_DRIVER_LEDS = 1
USE_DRIVER_USART = 1
USE_STDIO_USART = 1


STM32DEVSUPPORTDIR = ../../appleseed
## be sure to include the other makefiles
include $(STM32DEVSUPPORTDIR)/build-env/setup.mk


	