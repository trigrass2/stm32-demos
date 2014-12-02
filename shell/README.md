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

 - connect to the shell with putty, miniterm.py or netcat on port 22.
 
``` bash
	
	# netcat - specify ip address and port 22, hit enter a few times for the prompt
	# type help to see commands
	nc 192.168.0.xxx 22
	0:#
	0:#
	
	...
	
	# or miniterm.py, this is a little better as it isnt line based like netcat
	
	0:/# 
	0:/# help
	the following commands exist:
	mycmd
	top
	ifconfig
	netstat
	cp
	mv
	cat
	echo
	mkdir
	rm
	cd
	ls
	date
	exit
	help
	0:/# 
	0:/# ls
	etc             var             
	0:/# mkdir tmp            
	
	0:/# cd tmp
	
	0:/tmp# echo "hi cat!" > del
	
	0:/tmp# ls
	.               ..              del             
	0:/tmp# cat del
	hi cat!
	0:/tmp# 
	0:/tmp# mycmd
	
	0:/tmp# mycmd -h
	mycmd usage
	demo shell command 
	flags:
	 -a  print out the argument given directly after this flag, if any
	 -b  this is a binary flag, if specified prints a special message
	0:/tmp# mhcmd -a 123
	no such command mhcmd
	0:/tmp# mycmd -a 123
	got arg -a: 123
	
	0:/tmp# mycmd -a 123 -b
	got arg -a: 123
	got arg -b yeay!
	
	0:/tmp# 
	...

```
