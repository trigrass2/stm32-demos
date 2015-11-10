stm32-demos
===========

This is a collection of demo programs that show how to write programs for the appleseed OS.

setup
-----

The demos are bundled together, and depend upon the appleseed project. They depend upon Appleseed, which should be placed in the same directory with the demos.

```bash
git clone https://github.com/drmetal/stm32-demos.git
git clone https://github.com/drmetal/appleseed.git
```

sdcard
------

some of the demos require an sd card inserted, loaded with the base filesystem.
copy the contents of appleseed/like-posix/base_fs to a card, and plug it into the board.

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
Board Support
-------------

Most of the demos can run on more than one target board, board support exists for:

 - HY-STM32_100P this is a cheap bord with lots of features, and a mini ENC28J60 addon
 	<a href="https://drive.google.com/uc?export=view&id=0B1Zk1jXs2BXaUUtaTU40YmZiZDQ"><img src="https://drive.google.com/uc?export=view&id=0B1Zk1jXs2BXaUUtaTU40YmZiZDQ" style="width: 500px; max-width: 100%;
 - uemb1, uemb4 these are my own design (STM32F103VE and STM32F407VE variants are available). includes support for TFT, stereo audio in and out, USB, FTDI RS232, Ethernet and GPIO. Can fit into a Hammond 1591 enclosure.
 	<a href="https://drive.google.com/uc?export=view&id=0B1Zk1jXs2BXaWU9YeEZyUlQ4QmM"><img src="https://drive.google.com/uc?export=view&id=0B1Zk1jXs2BXaWU9YeEZyUlQ4QmM" style="width: 500px; max-width: 100%; height: auto" title="Click for the larger version." /></a>
 - stm32f4-discovery
 	<a href="https://drive.google.com/uc?export=view&id=0B1Zk1jXs2BXaZzFxSXM1TkdKMm8"><img src="https://drive.google.com/uc?export=view&id=0B1Zk1jXs2BXaZzFxSXM1TkdKMm8" style="width: 500px; max-width: 100%;

