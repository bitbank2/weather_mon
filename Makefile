# Weather monitor
CFLAGS=-c -Wall -O2
LIBS = -lm -lbme280 -lccs811 -loled96 -lpthread

all: wm

wm: main.o
	$(CC) main.o $(LIBS) -o wm

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o wm
