CC = g++ $(CFLAGS)
CFLAGS = -g -O0

all: threadtst semExample

threadtst: threadtst.cpp
	$(CC) -o threadtst threadtst.cpp -lpthread

semExample: semExample.cpp
	$(CC) -o semExample semExample.cpp -lpthread

clean:
	rm -f threadtst semExample *.o a.out core
