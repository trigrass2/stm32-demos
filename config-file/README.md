config-file-demo
================

Demonstrates configuration file editing and reading. 

the demo:

  - initializes the console logger
  - initializes the file system 
 
then loops:
 
  - deletes the config file if any
  - writes some key value pairs to the config file
  - reads all key value pairs to the config file
  - modifies some key value pairs in the config file
  - reads all key value pairs to the config file

boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P
 - Any stm32f1 or stm32f4 board with SDIO and a console USART support would work.

**to test:**

 - run a serial-terminal program to monitor the board console output.

 
``` bash
	
	# assumes you have pyserial installed, and that you use a USB serial port cable
	miniterm.py -p /dev/ttyUSB0 -b 115200

```
