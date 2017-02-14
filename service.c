#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>
#include<pthread.h>
#include<mysql/mysql.h>
//#include<mysql.h>
int mysocket(void);
void error(char *);
int myaccept(int mysock);
void *deal(void *);
pthread_t create_pthread(int myconnect);
void mysql_do(int);
MYSQL mysql_connect(void);
int main(void)
{
        int mysock = 0;
        int myconnect = 0;
        pthread_t tid = 0;
        mysock = mysocket();
        while(1)
        {
                myconnect = myaccept(mysock);
                tid = create_pthread(myconnect);
        }
        return 0;
}
void mysql_do(int myconnect)
{
        char buff[1024];
        int c = 0;
        MYSQL mysql;
        c = recv( (int*)myconnect, buff,1024,0);
        if( -1 == c )
                error("cannot get buff\n");
        mysql = mysql_connect();
}
MYSQL mysql_connect(void)
{
        MYSQL my;
        int c = 0;
        mysql_init(&my);
        c = mysql_real_connect(&my, "localhost", "root", "lihuanpu", "tiku",0,NULL,0);
        if( !c )
                error("cannot connect database");
        return my;
}
void *deal(void *myconnect)
{
        mysql_do((int*)myconnect);
        return NULL;
}
pthread_t create_pthread(int myconnect)
{
        int *p ;
        pthread_t tid = 0;
        p = (int*)malloc(sizeof(int));
        if( NULL == p )
                error("cannot malloc\n");
        *p = myconnect;
        tid = pthread_create(&tid, NULL, deal,(void *)p);
        if( -1 == tid )
                error("cannot create pthread\n");
        return tid;
}
int myaccept(int mysock)
{
        struct sockaddr_storage client;
        unsigned int address_size = sizeof(client);
        int myconnect = 0;
        myconnect = accept(mysock,(struct sockaddr*)&client,&address_size);
        if( -1 == myconnect )
                error("caanot accept\n");
        return myconnect;
}
int mysocket(void)
{
        int mysocket = 0;
        int reuse = 1;
        struct sockaddr_in name;
        int c;

        mysocket = socket( PF_INET, SOCK_STREAM, 0);
        if( -1 == mysocket )
                error("cannot create socket\n");
        name.sin_family = AF_INET;
        name.sin_port = (in_port_t)htons(3000);
        name.sin_addr.s_addr = htonl(INADDR_ANY);

        c = setsockopt(mysocket, SOL_SOCKET, SO_REUSEADDR, (char *)reuse,sizeof(int));
        if( -1 == c )
                error("cannot set port\n");
        c = bind(mysocket, (struct sockaddr *)&name, sizeof(name));
        if( -1 == c )
                error("cannot bind\n");
        c = listen(mysocket,5);
        if( -1 == c )
                error("cannot listen\n");
        return mysocket;
}
/*******
int _mysocket(void)
{
        struct addrinfo *res = NULL;
        struct addrinfo hints;
        int mysocket = 0;
        int myconnect = 0;
        memset(&hints,0,sizeof(hints));
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        if( -1 == getaddrinfo( "127.0.0.1","8180",&hints,&res) )
                error("cannot create the address\n");
        mysocket = socket( res->ai_family, res->ai_socktype, res->ai_protocol);
        if( -1 == mysocket )
                error("cannot open socket\n");
        myconnect = connect(mysocket, res->ai_addr, res->ai_addrlen);
        freeaddrinfo(res);
        if( -1 == myconnect )
                error("cannot connect to socket\n");
        return myconnect;
}
****/
void error(char *a)
{
        printf("%s",a);
}
