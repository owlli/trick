CFLAGS=-Wall
LIBS=-lm
SOURCES=$(wildcard ./srouce/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

main:$(OBJECTS)
	gcc -o xray $(SOURCES) $(CFLAGS)

clean:
	rm xray
