TOOLCHAIN ?= ~/android/toolchain/
SDK ?= ~/android/android-sdk-linux/
ANDROID_TARGET ?= android-10

CC = $(TOOLCHAIN)/bin/arm-linux-androideabi-gcc
LD = $(TOOLCHAIN)/bin/arm-linux-androideabi-ld
ADB = $(SDK)/platform-tools/adb
SYSROOT = $(TOOLCHAIN)/sysroot/

SYSTEM = android
ARCH = arm

CFLAGS += -O0 -g -Wall

.PHONY: all clean install

all: serial_noise

clean:
	rm -f *.o
	rm -f serial_noise

serial_noise: noise.o
	$(CC) -static -Wl -o $@ $^

install: $(ADB) serial_noise
	$(ADB) push serial_noise /cache/

remount: $(SDK)/platform-tools/adb
	 $(SDK)/platform-tools/adb remount
