target: service client

service : service.c
	gcc service.c -pthread -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -o service 
client : client.o window.o student.o teacher.o
	gcc client.o  window.o student.o teacher.o -o client
client.o : client.c
	gcc -c client.c -o client.o
window.o : window.c
	gcc -c window.c -o window.o
student.o : student.c
	gcc -c student.c -o student.o
teacher.o : teacher.c
	gcc -c teacher.c -o teacher.o
clean :
	rm -f service client
rm :
	rm  *.o
