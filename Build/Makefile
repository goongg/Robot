CC = g++
CFLAGS = -Wall -I../Controller/ -I../IOPlatform
WINLDFLAGS = -lXinput
WINOBJS = GamePad.o Robot.o RaspSysfs.o Main.o 

GamePad.o: ../Controller/Src/GamePad.cpp ../Controller/Src/GamePad.h
	$(CC) $(CFLAGS) -c ../Controller/Src/GamePad.cpp

RaspSysfs.o: ../IOPlatform/Src/RaspSysfs.cpp ../IOPlatform/Src/RaspSysfs.h
	$(CC) $(CFLAGS) -c ../IOPlatform/Src/RaspSysfs.cpp

Robot.o: ../Robot/Robot.cpp ../Robot/Robot.h
	$(CC) $(CFLAGS) -c ../Robot/Robot.cpp

Main.o: ../Main/Main.cpp
	$(CC) $(CFLAGS) -c ../Main/Main.cpp

WIN: $(WINOBJS)
	$(CC)	$(CFLAGS) -o RunRobot_WIN	$(WINOBJS)	$(WINLDFLAGS)

LINUX:	$(WINOBJS)
	$(CC)	$(CFLAGS)	-o	RunRobot_LINUX	$(WINOBJS)