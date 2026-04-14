.PHONY: all build upload monitor clean discover

all: build

build:
	rm -rf build && mkdir build && pio run && mv .pio/build/m5stack-cardputer/firmware.bin build/M5CardRemote.bin

upload:
	pio run --target upload

monitor:
	pio device monitor

clean:
	pio run --target clean && rm -rf build

discover:
	pio device list
