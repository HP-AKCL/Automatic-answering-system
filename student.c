#include"student.h"
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

char *smenu[] ={
	"1: answer\n",
	"2: select\n",
	"3: look grades\n",
	"0: exit\n",
	"in your chiose:"};
int student_menu_print(void);
void function_1(int,char[][10]);
void function_2(int,char**);
void function_3(int,char**);
void function_2(int sock,char** info){}
void function_3(int sock,char** info){}
void function_1(int sock,char info[][10])
{
	char mesg[1024];
	char buff[2];
	int flag;
	bzero(buff,sizeof(buff));
	buff[0] = '1';
	buff[1] = '1';
	flag = send(sock,buff,sizeof(buff),0);
	if( flag != 2 )
	{
		printf("send data error\n");
		exit(0);
	}
//	recv(sock,mesg,sizeof(mesg),0);
	printf("%s\n",buff);
	printf("%s\n",&info[0]);
	printf("%s\n",&info[1]);
	printf("%s\n",buff);
}
void student(int sock,char info[][10])
{
	int num = 0;
	while(1)
	{
		num = student_menu_print();
		switch(num)
		{
			case 1:
				function_1(sock,info);
				break;
			case 2:
				function_2(sock,info);
				break;
			case 3:
				function_3(sock,info);
				break;
			case 0:
			default:
				exit(0);
				break;
		}
	}
}
int student_menu_print(void)
{
	int i;
	int num;
	while(1)
	{
		for( i = 0; i < 5; i++)
			printf("\t%s",smenu[i]);
		scanf("%d",&num);
		(void)getchar();
		if( num >=0 && num < 5)
			return num;
		printf("\tin a error num\n");
	}
}
