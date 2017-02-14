target : service client

service : service.c
        gcc service.c -o service
client  :  client.c
        gcc client.c -o client
