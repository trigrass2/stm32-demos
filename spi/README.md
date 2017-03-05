spi-demo
========

this demo shows SPI  driver modes.

- The SPI pin mappings are pre-defined in: like-posix/**/drivers/base_spi.h
- The SPI chip select pins and peripheral pin mappings are defined in: like-posix/**/boards/stm32f4_dicovery.bsp/spi_config.h


boards
------

 - stm32f4_discovery

test
----

 the console USART prints a count up if the SPI MOSI ad MISO lines are connected together.

- link MISO and MOSI pins for loop back 
 - SPI1 link PA6 and PA7.
 - SPI2 link PB14 and PB15.
 - SPI3 link PB4 and PB5.

- use a scope to check
  -  SPI1 on PA4, PA5, PA6 and PA7.
  -  SPI2 on PB12, PB13, PB14 and PB15.
  -  SPI3 on PA15, PB3, PB4 and PB5.
