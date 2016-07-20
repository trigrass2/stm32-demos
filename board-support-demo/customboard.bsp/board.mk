## demo of a custom board support directory - this is just a copy of the stm32f4-discovery board config
BOARD=customboard
# add the custom board to the boards list
BOARDS = customboard

## configure the board
# set oscillator frequency
HSE_VALUE = 8000000
# set device (choose from devices listed in appleseed/stm32-device-support/device/device.mk)
DEVICE = STM32F407xx
# PHY selection is a board level thing 
ifeq ($(USE_DRIVER_LWIP_NET), 1)
USE_DRIVER_ENC28J60_PHY = 1
USE_DRIVER_MII_RMII_PHY = 0
endif
