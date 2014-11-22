socket-demo
===========

Simple socket demo. performs an HTTP GET on a simple HTTP server that is run on your local machine.

The demo targets the uemb1/4 development board, as they support ethernet (enc28j60 device). 


build
-----

First, set up the stm32-build-env (see https://github.com/drmetal/stm32-build-env)
 
then clone the demo project:
 
 - git clone https://github.com/drmetal/socket-demo.git
  
Make a new eclipse "Makefile" project, if you like to use eclipse, in the folder socket-demo.
The Makefile in that project requires the following settings:
 
``` make

	BOARD = uemb4
	PROJECT_NAME = socket-demo
	
	SOURCE = main.c
	
	USE_FREERTOS = 1
	USE_MINSTDLIBS = 1
	USE_CONFPARSE = 1
	USE_LOGGER = 1
	USE_POSIX_STYLE_IO = 1
	USE_SOCK_UTILS = 1
	USE_DRIVER_SYSTEM_TIMER = 1
	USE_DRIVER_LEDS = 1
	USE_DRIVER_USART = 1
	USE_DRIVER_LWIP_NET = 1
	USE_DRIVER_SDCARD_SDIO = 1
	USE_DRIVER_FAT_FILESYSTEM = 1
	
	USE_FULL_ASSERT = 1
	
	STM32DEVSUPPORTDIR = ../..
	include $(STM32DEVSUPPORTDIR)/stm32-build-env/setup.mk

```
 
**to build:**

``` bash 
	
	cd path/to/socket-demo
	# optimised build
	make clean release
	# debug build
	make clean debug
	
	# programming with st-flash (tool by texane)
	st-flash write bin/socket-demo.bin 0x08000000
	
	# to debug the elf file is located in the bin directory...

```

**to test:**

 - in one shell, run a serial-terminal program to monitor the board console output.
 - set host in the demo to your PC IP address or hostname.
 - in another shell, create a test file, and run an HTTP server.
 
``` bash
	
	# assumes you have pyserial installed, and that you use a USB serial port cable
	miniterm.py -p /dev/ttyUSB0 -b 115200

```

``` bash
	
	cd path/to/socket-demo
	echo "hello world!" > hello
	python -m SimpleHTTPServer

```
