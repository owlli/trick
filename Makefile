XX=gcc
CFLAGS=-Wall
LIBS=-lm
SOURCES=$(wildcard ./source/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

main:$(OBJECTS)
	$(XX) -g -o client_main client_main.c $(SOURCES)
	$(XX) -g -o server_main  server_main.c $(SOURCES)
	$(XX) -g -o client_daemon client_daemon.c $(SOURCES)

#$(OBJECTS):%.o:%.c
#	$(XX) -c $(CFLAGS) $< -o $@
install:
	cp ./unit/trick.service /etc/systemd/system/
	cp tkexample /etc/
	systemctl daemon-reload
	systemctl start trick.service
	systemctl enable trick.service
clean:
	rm client_main server_main client_daemon $(OBJECTS)
	rm -f ./include/*.gch
uninstall:
	systemctl stop trick.service
	systemctl disable trick.service
	rm /etc/systemd/system/trick.service
	systemctl daemon-reload
