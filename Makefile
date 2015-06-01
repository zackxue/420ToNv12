sources = main.c 420ToNv12.c
objects = $(patsubst %.c,%.o,$(sources))
CC = gcc
OPTS = -Wall

420ToNv12: $(objects)
	$(CC) $(OPTS) -o $@ $(objects)

clean:
	rm 420ToNv12 $(objects)