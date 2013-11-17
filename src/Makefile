ARDUINO_LIBS = Ethernet SPI OneWire
BOARD_TAG = uno
MONITOR_PORT = /dev/ttyACM*

USER_LIB_PATH := server

EXTRA_FLAGS = -include favicon.h

default: all

dev: EXTRA_FLAGS += -DDEV
dev: default

ARDUINO_DIR := /usr/share/arduino
AVR_TOOLS_DIR = /usr

ARDMK_DIR := $(realpath ../Arduino-Makefile)
ARDMK_PATH := $(ARDMK_DIR)/bin

include $(ARDMK_DIR)/arduino-mk/Arduino.mk

