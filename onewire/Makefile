
BOARD = uemb4
PROJECT_NAME = onewire-demo

SOURCE = main.c

USE_PTHREADS = 1
USE_FREERTOS = 1
USE_MINLIBC = 1
USE_DRIVER_SYSTEM_TIMER = 1
USE_DRIVER_LEDS = 1
USE_DRIVER_USART = 1
USE_STDIO_USART = 1
USE_LOGGER = 1
USE_DRIVER_1WIRE = 1

# required to build with ONEWIRE_DEV=1
USE_LIKEPOSIX = 1
#USE_DRIVER_SPI = $(USE_LIKEPOSIX)
#USE_DRIVER_LWIP_NET = $(USE_LIKEPOSIX)
USE_DRIVER_SDCARD = $(USE_LIKEPOSIX)
USE_DRIVER_FAT_FILESYSTEM = $(USE_LIKEPOSIX)


USE_FULL_ASSERT = 1
DEBUG_PRINTF_EXCEPTIONS = 1
	
LIKEPOSIX_DIR = ../../like-posix
include $(LIKEPOSIX_DIR)/build-env/setup.mk
