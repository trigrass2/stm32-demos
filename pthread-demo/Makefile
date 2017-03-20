
# these may be set from the command line

BOARD ?= uemb4

PROJECT_NAME ?= pthread-demo

## project source
SOURCE = ./main.c
CFLAGS = -I./config

USE_PTHREADS = 1
USE_FREERTOS= 1
USE_MINLIBC = 1
USE_LOGGER = 1
USE_LOGGER_TIMESTAMP = 1
USE_DRIVER_SYSTEM_TIMER = 1
USE_DRIVER_LEDS = 1
USE_DRIVER_USART = 1
USE_STDIO_USART = 1
USE_MINSTDIO_FLOAT_SUPPORT = 1
DEBUG_PRINTF_EXCEPTIONS = 1
USE_FULL_ASSERT = 1

APP_ADDRESS_OFFSET = 0x00000

LIKEPOSIX_DIR = ../../like-posix
## be sure to include the other makefiles
include $(LIKEPOSIX_DIR)/build-env/setup.mk


	