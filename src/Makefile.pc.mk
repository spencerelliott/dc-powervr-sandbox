TARGET_NAME = PVRTest

OBJS = platform/pc.o main.o unim/core.o game/game.o
INCLUDES = 

%.o: %.c
	gcc -c $< -o $@

all: $(OBJS)
	gcc -o ../bin/$(TARGET_NAME) $(OBJS)

clean:
	-rm -f ../bin/$(TARGET_NAME) $(OBJS) romdisk.*