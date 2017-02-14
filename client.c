#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void error(char *);
int myconnect(void);

int main(void)
{
        int sock = 0;
        sock = myconnect();

        return 0;
}

int myconnect(void)
{
        int sock = 0;
        struct sockaddr_in si;
        int c = 0;
        si.sin_family = PF_INET;
        si.sin_addr.s_addr = inet_addr("127.0.0.1");
        si.sin_port = htons(3000);

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if( -1 == sock )
                error("cannot create sock\n");

        c = connect(sock,(struct sockaddr*)&si, sizeof(si));
        if( -1 == c )
                error("cannot connect\n");
        return sock;
}
void error(char *s)
{
        printf("%s",s);
}
