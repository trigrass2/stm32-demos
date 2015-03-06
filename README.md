stm32-demos
===========

This is a collection of demos. 

 - some run on a specific target
 - some run on more than one target 
 - all have differing dependencies
 - the build note below explains how to build any demo
 
sdcard
------

some of the demos require an sd card inserted, loaded with the base filesystem.
copy the contents of like-posix/base_fs to a card, and plug it into the board.

build
-----

First, set up **stm32-build-env** (see https://github.com/drmetal/stm32-build-env)
 
then clone the demo collection:
 
 - git clone https://github.com/drmetal/stm32-demos.git
  
Each project is configured in its Makefile.


``` bash 
	
	cd stm32-demos/name-of-demo
	
	# build optimized for size
	make clean small
	
	# OR build optimized for speed
	make clean release
	
	# OR build for debugging (binary size will be much bigger)
	make clean debug
	
	## if you use an stlink/stlink-v2 device
	# programming with st-flash (tool by texane)
	st-flash write bin/name-of-demo.bin 0x08000000
	
	# to make a dfu file for DFU programming (stm32f4xx/stm32f107 only)
	make dfu
	
	## if you use USB/DFU programming
	# programming with dfu-util (sudo apt-get install dfu-util)
	[sudo] make dfuutil
	
	# to debug, the elf file is located in the bin directory...

```

boards
------

board support exists for:

 - HY-STM32_100P - http://www.youtube.com/watch?v=sqg3AJ9PEVg
 - uemb1
 - uemb4
 - stm32f4-discovery


