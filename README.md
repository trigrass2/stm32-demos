stm32-demos
===========

This is a collection of demonstration programs, meant to make it possible to remeber how to use the many features of the appleseed framework.

Many of the demos can run on more than one target board, board support exists for:

 - HY-STM32_100P - http://www.youtube.com/watch?v=sqg3AJ9PEVg
 - uemb1
 - uemb4
 - stm32f4-discovery

setup
-----

The demos are bundled together, and depend upon the appleseed project. They depend upon Appleseed, which should be placed in the same directory with the demos.

```bash
git clone https://github.com/drmetal/stm32-demos.git
git clone https://github.com/drmetal/app-l-seed.git
```

sdcard
------

some of the demos require an sd card inserted, loaded with the base filesystem.
copy the contents of app-l-seed/like-posix/base_fs to a card, and plug it into the board.

build
-----
  
Each project is configured in its Makefile. To build say the socket demo:

``` bash 
	
cd stm32-demos/socket

# build optimized for size
make clean small

# OR build optimized for speed
make clean release

# OR build for debugging (binary size will be much bigger)
make clean debug

## if you use an stlink/stlink-v2 device
# programming with st-flash (tool by texane)
st-flash write bin/socket.bin 0x08000000

# to make a dfu file for DFU programming (stm32f4xx/stm32f107 only)
make dfu

## if you use USB/DFU programming
# programming with dfu-util (sudo apt-get install dfu-util)
[sudo] make dfuutil

# to debug, the elf file is located in the bin directory...

```



