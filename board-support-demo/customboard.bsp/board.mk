## demo of a custom board support directory - this is just a copy of the stm32f4-discovery board config

## override board configurations in appleseed/stm32-device-support/board/board.mk
BOARDDIR = ./
## name the board
BOARDS = customboard

## configure the board
# set oscillator frequency
HSE_VALUE = 8000000
# set device (choose from devices listed in appleseed/stm32-device-support/device/device.mk)
DEVICE = stm32f407vg
# PHY selection is a board level thing 
ifeq ($(USE_DRIVER_LWIP_NET), 1)
USE_DRIVER_ENC28J60_PHY = 1
USE_DRIVER_MII_RMII_PHY = 0
endif
