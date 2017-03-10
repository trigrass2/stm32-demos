usart-demo
========

this demo shows USART  driver modes.

- The USART pin mappings are pre-defined in: 
	like-posix/stm32-device-support/drivers/base_usart.h
- The USART chip select pins and peripheral pin mappings are defined in: 
	like-posix/stm32-device-support/boards/uemb4.bsp/usart_config.h


boards
------

 - any board with an sdcard, console usart and an extra usart that can be connected in loop back configuration

test
----

 the console USART prints a messsage that is sent and looped back.

- link TX and RX pins for loop back, on USART2 link PA3 and PA2 for example.

