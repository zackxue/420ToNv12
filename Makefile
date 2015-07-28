target  = 420ToNv12
sources = main.c $(target).c
objects = $(patsubst %.c,%.o,$(sources))
CC = gcc
OPTS = -Wall

$(target): $(objects)
	$(CC) $(OPTS) -o $@ $(objects)

clean:
	rm $(target) $(objects)
