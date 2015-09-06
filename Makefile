target  = 420ToNv12
sources = main.c $(target).c
objects = $(patsubst %.c,%.o,$(sources))
CC = gcc
OPTS = -Wall -O2

all: $(objects)
	$(CC) $(OPTS) -o $(target) $(objects)

$(target).o: $(target).c
	$(CC) $(OPTS) -c $<

clean:
	$(RM) $(target) $(objects)
