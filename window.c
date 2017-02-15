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
extern void student(int);
extern void teacher(int);

int my_client_al_print(int sock)
{
	int n = 1;
	int i ;
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
					student(sock);
					break;
				case 2:
					teacher(sock);
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
