minimal-demo
===========

this demo shows how to build with no OS - the flash Usage should be very very small.

this demo works on any board with SDIO support.


build
-----

First, set up the stm32-build-env (see https://github.com/drmetal/stm32-build-env)
 
then clone the demo project:
 
 - git clone https://github.com/drmetal/minimal-demo.git
  
Make a new eclipse "Makefile" project, if you like to use eclipse, in the folder minimal-demo.
The Makefile in that project requires the following settings:
 
``` make

	BOARD = uemb4
	PROJECT_NAME = minimal-demo
	
	SOURCE = main.c
	
	USE_MINSTDLIBS = 1
	USE_DRIVER_SYSTEM_TIMER = 1
	USE_DRIVER_LEDS = 1
	USE_DRIVER_SDCARD_SDIO = 1
	USE_DRIVER_FAT_FILESYSTEM = 1
	
	USE_FULL_ASSERT = 0
	
	STM32DEVSUPPORTDIR = ../..
	include $(STM32DEVSUPPORTDIR)/stm32-build-env/setup.mk

```
 
**to build:**

``` bash 
	
	cd path/to/minimal-demo
	
	# build optimized for size
	make clean small
	
	# OR build optimized for speed
	make clean release
	
	# OR build for debugging (size will be much bigger)
	make clean debug
	
	# programming with st-flash (tool by texane)
	st-flash write bin/minimal-demo.bin 0x08000000
	
	# to debug the elf file is located in the bin directory...

```

**to test:**

 - note the led flashes
 - the number of flashes is defined in a file on the SD card :)
