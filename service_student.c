#include<mysql/mysql.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
void server_student(int myconnect,MYSQL mysql,char flag)
{
	char mesg[1024];
	char buff[2] = {'0'};
	bzero(mesg,sizeof(mesg));
	if( flag ==  '0' )
	{
		buff[0] = '0';buff[1] = '0';
		send(myconnect,buff,sizeof(buff),0);
//		printf("%c  %c\n",buff[0],buff[1]);
		recv(myconnect,mesg,sizeof(mesg),0);
		printf("mesg---->%s\n",mesg);
		while( buff[0] != '1' && buff[1] != '1' )
		{
			if( buff[1] == '0' )//get data from  mysql;
			{


			}
			else
				printf("something error\n");
			recv(myconnect,buff,sizeof(buff),0);
		}
		exit(0);
	}
	else if( flag == '1')
	{

	}
	else
	{
		printf("service_studnt recv data error\n");
	}

}
