CC= gcc
WFLAGS= -Wpedantic -Wall -Wextra -Wmissing-prototypes -Wundef \
-Wmissing-declarations -Wold-style-definition -Wshadow -Wstrict-prototypes
LDFLAGS= -std=gnu17  $(WFLAGS)
CFLAGS= $(LDFLAGS) -c

DAYNUM=03

all: day$(DAYNUM)p1 day$(DAYNUM)p2

day$(DAYNUM)p1: day$(DAYNUM)p1.o
	$(CC) $(LDFLAGS) $^ -o day$(DAYNUM)p1
	
day$(DAYNUM)p2: day$(DAYNUM)p2.o
	$(CC) $(LDFLAGS) $^ -o day$(DAYNUM)p2

day$(DAYNUM)p1.o: day$(DAYNUM)p1.c
	$(CC) $(CFLAGS) $<

day$(DAYNUM)p2.o: day$(DAYNUM)p2.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o ./day$(DAYNUM)p1 ./day$(DAYNUM)p2
