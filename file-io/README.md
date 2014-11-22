file-io-demo
===========

Demonstrates posix like IO. The demo targets the HY-STM32_100P development board, as it supports sdio. 

Video of the HY-STM32_100P: http://www.youtube.com/watch?v=sqg3AJ9PEVg

Any stm32f1 or stm32f4 board with SDIO and a console USART support would work.

the demo:

  - installs the console USART as a readonly device in /dev/ttyS0
  - attaches a logger to to STDOUT (which happens to be the console USART tx device)
 
then loops:
 
 - reads from that device
 - if there is data
	 - stores it to a file "datafile.txt"
	 - then back to the top
 - if not
	 - logs the size of the file to STDOUT
	 - waits a second
	 - then back to the top


build
-----

First, set up the stm32-build-env (see https://github.com/drmetal/stm32-build-env)
 
then clone the demo project:
 
 - git clone https://github.com/drmetal/file-io-demo.git
  
Make a new eclipse "Makefile" project, if you like to use eclipse, in the folder file-io-demo.
The Makefile in that project requires the following settings:
 
``` make 

	BOARD = HY-STM32_100P
	
	PROJECT_NAME = file-io-demo
	
	SOURCE = main.c
	
	USE_FREERTOS = 1
	USE_MINSTDLIBS = 1
	USE_LOGGER = 1
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
	
	cd path/to/file-io-demo
	# optimised build
	make clean release
	# debug build
	make clean debug
	
	# programming with st-flash (tool by texane)
	st-flash write bin/file-io-demo.bin 0x08000000
	
	# to debug the elf file is located in the bin directory...
```

**to test:**

 - run a serial-terminal program to monitor the board console output.

 
``` bash
	
	# assumes you have pyserial installed, and that you use a USB serial port cable
	miniterm.py -p /dev/ttyUSB0 -b 115200

```
