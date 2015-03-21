socket-demo
===========

demonstartes how to set up serial port, file, and udp loggers. 


boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P with enc28j60 expansion board
 - Any stm32f1 or stm32f4 board with SDIO, ethernet and a console USART support would work.


test
----

 - in one shell, run a serial-terminal program to monitor the board console output. this demo's serial logging.
 - in another shell, run netcat to listen for udp packets. this demo's udp logging.
 - in another shell, run netcat as a tcp client (specify your devices IP address), and use the shell to cat the log file. this demo's file logging.
 
``` bash
	
	# assumes you have pyserial installed, and that you use a USB serial port cable
	miniterm.py -p /dev/ttyUSB0 -b 115200

```

``` bash
	# udp listener
	nc -l -u 32000
```

``` bash
	# tcp client
	nc 192.168.0.10 22
```
