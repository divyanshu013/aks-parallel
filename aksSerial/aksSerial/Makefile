CC = g++
CFLAGS = -lntl -lmpir -std=c++11 -pthread

all:
	$(CC) main.cpp helper.cpp $(CFLAGS) -o run

test:
	$(CC) test.cpp helper.cpp $(CFLAGS) -o run

clean:
	rm run
