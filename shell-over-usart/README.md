shell-over-usart
================

shell demo. starts a single shell instance connected to a usart rather than served over TCP.


boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P
 - Any stm32f1 or stm32f4 board with SDIO, and a console USART support would work.


test
----

 - connect to the shell with putty or miniterm.py or any other terminal emulator.
 
``` bash
	
	$ miniterm.py -p /dev/ttyUSB0 -b 115200


```
