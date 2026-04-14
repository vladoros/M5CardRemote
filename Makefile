.PHONY: all build install upload monitor clean discover

VERSION := 0.1

all: build

install:
	pip3 install --upgrade --break-system-packages platformio

build:
	rm -rf build && mkdir build && pio run && mv .pio/build/m5stack-cardputer/firmware.bin build/M5CardRemote-${VERSION}.bin

upload:
	pio run --target upload

monitor:
	pio device monitor

clean:
	pio run --target clean && rm -rf build

discover:
	pio device list
