XX=gcc
CFLAGS=-Wall
LIBS=-lm
SOURCES=$(wildcard ./srouce/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

main:$(OBJECTS)
#	$(XX) -o xray $^ $(CFLAGS)
	$(XX) -o xray ./srouce/xray.c
	$(XX) -o server ./srouce/server.c
	$(XX) -o client ./srouce/client.c

#$(OBJECTS):%.o:%.c
#	$(XX) -c $(CFLAGS) $< -o $@

clean:
	rm xray server client $(OBJECTS)
