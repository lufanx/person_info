.PHONY:clean
objects = main.o person_mysql.o

person_info:$(objects)
	cc -o $@ $(objects)

main.o:main.c init.h
	cc -c main.c
person_mysql.o:person_mysql.c person_mysql.h
	cc -I/usr/local/Cellar/mysql/5.7.19/include/mysql $^ -L /usr/local/Cellar/mysql -lmysqlclient


clean:
	-rm person_info $(objects) *.h.gch
