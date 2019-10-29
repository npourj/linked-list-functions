CC := gcc
CFLAGS := -Wall -Wuninitialized -Og -g
PROGS := dict 

.PHONY:all

all: $(PROGS)

dict: main.o dict.o dict_support.o
	$(CC) $(CFLAGS) -o $@ $^ 

main.o: dict.h
dict.o: dict.h
dict_support.o: dict.h

.PHONY:clean

clean:
	rm -f $(PROGS) *.o
