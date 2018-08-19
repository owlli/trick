XX=gcc
CFLAGS=-Wall
LIBS=-lm
SOURCES=$(wildcard ./source/*.c)
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))

main:$(OBJECTS)
#	$(XX) -o xray $^ $(CFLAGS)
	#$(XX) -o xray ./source/xray.c
	#$(XX) -o server ./source/server.c
	# $(XX) -o client ./source/client.c
	$(XX) -g -o client_main ./client_main.c ./source/client.c ./source/parse.c
	$(XX) -g -o server_main ./server_main.c ./source/server.c ./source/get_time.c ./source/surprise.c
	# cp ./unit/trick.service /etc/systemd/system/
	# cp tkexample /etc/
	# systemctl daemon-reload
	# systemctl start trick.service
	# systemctl enable trick.service
#$(OBJECTS):%.o:%.c
#	$(XX) -c $(CFLAGS) $< -o $@

clean:
	rm client_main server_main $(OBJECTS)
