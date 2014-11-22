config-file-demo
================

Demonstrates configuration file editing and reading. 

Any stm32f1 or stm32f4 board with SDIO and a console USART support would work.

the demo:

  - initializes the console logger
  - initializes the file system 
 
then loops:
 
  - deletes the config file if any
  - writes some key value pairs to the config file
  - reads all key value pairs to the config file
  - modifies some key value pairs in the config file
  - reads all key value pairs to the config file


build
-----

First, set up the stm32-build-env (see https://github.com/drmetal/stm32-build-env)
 
then clone the demo project:
 
 - git clone https://github.com/drmetal/config-file-demo.git
  
Make a new eclipse "Makefile" project, if you like to use eclipse, in the folder file-io-demo.
The Makefile in that project requires the following settings:
 
``` make 

	BOARD = uemb4
	
	PROJECT_NAME = config-file-demo
	
	SOURCE = main.c
	
	USE_FREERTOS = 1
	USE_MINSTDLIBS = 1
	USE_LOGGER = 1
	USE_CONFPARSE = 1
	USE_POSIX_STYLE_IO = 1
	USE_DRIVER_LEDS = 1
	USE_DRIVER_SYSTEM_TIMER = 1
	USE_DRIVER_USART = 1
	USE_DRIVER_SDCARD_SDIO = 1
	USE_DRIVER_FAT_FILESYSTEM = 1
	
	USE_FULL_ASSERT = 1
	
	STM32DEVSUPPORTDIR = ../..
	include $(STM32DEVSUPPORTDIR)/stm32-build-env/setup.mk

```
 
**to build:**

``` bash 
	
	cd path/to/config-file-demo
	# optimised build
	make clean release
	# debug build
	make clean debug
	
	# programming with st-flash (tool by texane)
	st-flash write bin/config-file-demo.bin 0x08000000
	
	# to debug the elf file is located in the bin directory...
```

**to test:**

 - run a serial-terminal program to monitor the board console output.

 
``` bash
	
	# assumes you have pyserial installed, and that you use a USB serial port cable
	miniterm.py -p /dev/ttyUSB0 -b 115200

```
