socket-demo
===========

Simple socket demo. performs an HTTP GET on a simple HTTP server that is run on your local machine.


boards
------

 - uemb1 
 - uemb4
 - HY-STM32_100P with enc28j60 expansion board
 - Any stm32f1 or stm32f4 board with SDIO, ethernet and a console USART support would work.


test
----

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
