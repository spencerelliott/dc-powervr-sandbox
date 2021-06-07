#
# Basic KallistiOS skeleton / test program
# Copyright (C)2001-2004 Dan Potter
#   

# Put the filename of the output binary here
TARGET_NAME = PVRTest
TARGET = ../bin/$(TARGET_NAME).elf

# List all of your C files here, but change the extension to ".o"
# Include "romdisk.o" if you want a rom disk.
OBJS = main.o unim/core.o

# If you define this, the Makefile.rules will create a romdisk.o for you
# from the named dir.
KOS_ROMDISK_DIR = ../romdisk

# The rm-elf step is to remove the target before building, to force the
# re-creation of the rom disk.
all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	-rm -f $(TARGET) $(OBJS) romdisk.*
	-rm -f ../bin/*.cdi
	-rm -f ../bin/*.bin
	-rm -f ../bin/*.BIN

rm-elf:
	-rm -f $(TARGET) romdisk.*

$(TARGET): $(OBJS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) romdisk.o $(OBJEXTRA) -lm -lkosutils $(KOS_LIBS)

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

cdi: $(TARGET)
	sh-elf-objcopy -R .stack -O binary $(TARGET) ../bin/$(TARGET_NAME).bin
	${KOS_BASE}/utils/scramble/scramble ../bin/$(TARGET_NAME).bin ../cd/1ST_READ.bin
	${KOS_BASE}/utils/makeip/src/makeip -vf ../bin/IP.BIN
	cd ../cd; ${KOS_BASE}/utils/makedisc ../bin/$(TARGET_NAME).cdi . ../bin/IP.BIN $(TARGET_NAME)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)