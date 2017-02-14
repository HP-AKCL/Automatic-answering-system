target: service client

service : service.c
        gcc service.c -pthread -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -o service 
client : client.c
        gcc client.c -o client
clean:
        rm -f service client

