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
void function_2(int,char[][10]);
void function_3(int,char[][10]);
void function_3(int sock,char info[][10]){}
void function_2(int sock,char info[][10]){}
void function_1(int sock,char info[][10])
{
	char mesg[1024];//data
	char buff[2];//connect buff
	int flag,i;
	char *p,*swap;
	char ques[5][10] = {0};
	char ans[5][10] = {0};
	char answer[5][10];
	char grade[5];// true or faules;
	buff[0] = '0';//send  chioce.
	buff[1] = '1';// 00connect 01send name pas 10send data 11send exit
	flag = send(sock,buff,sizeof(buff),0);
//	printf("%d %c %c\n",sock,buff[1],buff[0]);
	if( flag != 2 )
	{
		printf("send data error\n");
		exit(0);
	}

	{//answer the question.
	recv(sock,mesg,sizeof(mesg),0);
//	printf("%s\n",mesg);
		swap = mesg;
		for( i = 0; i < 5;i++)
		{
			p = strchr(swap,'-');
			strncpy(ques[i],swap,p-swap);
			swap = p + 1;
			p = strchr(swap,'|');
			strncpy(ans[i],swap,p-swap);
			swap = p + 1;
		}
		for( i = 0; i < 5 ; i++)
		{
			printf("question%d : %s = ",i,ques[i]);
			fgets(answer[i],sizeof(answer)-1,stdin);
			if( atoi(answer[i]) == atoi(ans[i]) )
				grade[i] = 1;
			else
				grade[i] = 0;
			
		}
		for( i = 0; i < 5 ; i++)
		{
			printf("question%d:%s=%s",i,ques[i],answer[i]);
			if( grade[i] == 1 )
				printf("\tyou TRUE \n");
			else
				printf("\tyou WRONG the answer is%s\n",ans[i]);
			
		}
		bzero(mesg,sizeof(mesg));
		for( i = 0; i < 5 ; i++)//send answer to server.
		{
			p = strchr(answer[i],'\n');
			*p = '\0';
			strcat(mesg,answer[i]);
			if( i != 4 )
				strcat(mesg,"|");//split the answer.
		}
		send(sock,mesg,sizeof(mesg),0);
		getchar();
		
	}
//recv data 00 01 10 11
	if(buff[0] == '0' && buff[1] == '0')
	{
		;
	}
	else
	{
		printf("student fun1 recv data error\n");
	}
}
void student(int sock,char info[][10])
{
	int num = 0;
	char mesg[1024];//data
	char buff[2];//connect buff
	int flag;
	bzero(buff,sizeof(buff));
	buff[0] = '0';
	buff[1] = '0';// 00connect 01send name pas 10send data 11send exit
	flag = send(sock,buff,sizeof(buff),0);
//	printf("%d %c %c\n",sock,buff[1],buff[0]);
	if( flag != 2 )
	{
		printf("send data error\n");
		exit(0);
	}
	bzero(mesg,sizeof(mesg));
//	recv(sock,buff,sizeof(buff),0);
	/*** send name and pas ***/
	bzero(mesg,sizeof(mesg));
	strcat(mesg,&info[0]);
	strcat(mesg,"|");
	strcat(mesg,&info[1]);
	flag = send(sock,mesg,sizeof(mesg),0);
//	printf("----->mesg%s\n",mesg);

	while(1)
	{
		num = student_menu_print();
		switch(num)// student loop
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
