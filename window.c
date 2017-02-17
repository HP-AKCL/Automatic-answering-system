#include<termios.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"student.h"
#include"teacher.h"
char *menu[] = {
	"0: exit",
	"1: student",
	"2: teacher",
	"int your chioce:"};
char *win_info[] = {
	"name    :",
	"password:"};
extern void student(int,char[][10]);
extern void teacher(int,char**);

int my_client_al_print(int sock)
{
	int n = 1;
	int i ;
	char info[2][10] = {0};
	if( !isatty(fileno(stdout)) )
	{
		printf("the atty isnot a terminal\n");
	}
	while( n != 0 )
	{
		for( i = 0; i < 3; i++)
		{
			printf("%s\n",menu[i]);
		}
		scanf("%d",&n);
		getchar();

		if( n >= 0 && n < 4 )
		{
			switch(n)
			{
				case 1:
					for( i = 0; i < 2; i++)
					{
						printf("%s",win_info[i]);
						scanf("%s",info[i]);
						getchar();
					}
					student(sock,info);
					break;
				case 2:
					for( i = 0; i < 2; i++)
					{
						printf("%s",win_info[i]);
						scanf("%s",info[i]);
						getchar();
					}
					teacher(sock,info);
					break;
				case 0:
					printf("will exit...\n");
					exit(0);
					break;
				default:
					break;
			}
		}
	}
}
