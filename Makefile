server:*.c *.h
	gcc -I/usr/include/mariadb *.c *.h -o mana_server -lwiringPi -lpthread -L /usr/lib/aarch64-linux-gnu/ -lmariadbclient
clean:
	rm mana_server

install:
