.PHONY:clean
CC=gcc
#CFLAGS=-Wall
all: person_info
objects=main.o person_mysql.o

debug:
	make DEBUG=TRUE
ifeq ($(DEBUG), TRUE)
		CFLAGS += -g
endif

person_info:$(objects)
	$(CFLAGS) $(CC) -I/usr/local/Cellar/mysql/5.7.19/include/mysql -L/usr/local/lib/ $^ -o $@ -lmysqlclient
main.o:main.c
	$(CFLAGS) $(CC) -c $< -o $@
person_mysql.o:person_mysql.c
	$(CFLAGS) $(CC) -c $< -o $@


clean:
	-rm person_info $(objects)
