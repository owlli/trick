XX=gcc
CFLAGS=-Wall
LIBS=-lm
SOURCES=$(wildcard ./source/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

main:$(OBJECTS)
#	$(XX) -o xray $^ $(CFLAGS)
	$(XX) -o xray ./source/xray.c
	$(XX) -o server ./source/server.c
	$(XX) -o client ./source/client.c

#$(OBJECTS):%.o:%.c
#	$(XX) -c $(CFLAGS) $< -o $@

clean:
	rm xray server client $(OBJECTS)
