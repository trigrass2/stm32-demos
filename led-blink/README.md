led-blink-demo
==============

Simple led blinker. The demo targets the stm32f4_discovery development board, as it supports leds. 

Any stm32f1 or stm32f4 board with leds support would work ;)


build
-----

First, set up the stm32-build-env (see https://github.com/drmetal/stm32-build-env)
 
then clone the demo project:
 
 - git clone https://github.com/drmetal/led-blink-demo.git
  
Make a new eclipse "Makefile" project, if you like to use eclipse, in the folder led-blink-demo.
The Makefile in that project requires the following settings:
 
``` make

	BOARD = stm32f4_discovery
	PROJECT_NAME = led-blink-demo
	
	SOURCE = main.c
	
	USE_FREERTOS = 1
	USE_MINSTDLIBS = 1
	USE_DRIVER_LEDS = 1
	
	USE_FULL_ASSERT = 1
		
	STM32DEVSUPPORTDIR = ../..
	include $(STM32DEVSUPPORTDIR)/stm32-build-env/setup.mk

```
 
**to build:**

``` bash 
	
	cd path/to/led-blink-demo
	# optimised build
	make clean release
	# debug build
	make clean debug
	
	# programming with st-flash (tool by texane)
	st-flash write bin/led-blink-demo.bin 0x08000000
	
	# to debug the elf file is located in the bin directory...
```