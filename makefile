target: service client
service : service.o service_student.o service_teacher.o
	gcc -g service.o service_student.o service_teacher.o -pthread -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -o service
service.o : service.c
	gcc -c -g service.c -o service.o
client : client.o window.o student.o teacher.o
	gcc client.o  window.o student.o teacher.o -o client
client.o : client.c
	gcc -c -g client.c -o client.o
window.o : window.c
	gcc -c -g window.c -o window.o
student.o : student.c
	gcc -c -g student.c -o student.o
service_student.o : service_student.c
	gcc -c -g service_student.c -o service_student.o
teacher.o : teacher.c
	gcc -c -g teacher.c -o teacher.o
service_teacher.o : service_teacher.c
	gcc -c -g service_teacher.c  -o service_teacher.o
clean :
	rm -f service client
rm :
	rm  *.o
all:
	rm -f service client *.o
