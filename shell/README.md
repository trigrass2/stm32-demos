shell
=====

shell demo. starts a shell server, serving inbuilt commands and one custom one.


boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P with enc28j60 expansion board
 - Any stm32f1 or stm32f4 board with SDIO, ethernet and a console USART support would work.


test
----

 - connect to the shell with putty, miniterm.py or netcat.
 
``` bash
	
	# netcat - specify ip address and port 22, hit enter a few times for the prompt
	# type help to see commands
	nc 192.168.0.xxx 22
	0:#
	0:#
	0:# help
	...

```
