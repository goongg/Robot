# 변수 정의
CC = gcc
CFLAGS = -Wall -Wextra

# 목표(Target) 및 의존성 지정
all: myprogram

# 컴파일 규칙 정의
myprogram: main.o utils.o
    $(CC) $(CFLAGS) -o myprogram main.o utils.o

main.o: main.c
    $(CC) $(CFLAGS) -c main.c

utils.o: utils.c
    $(CC) $(CFLAGS) -c utils.c

# clean 명령어 정의
clean:
    rm -f myprogram *.o