#include<mysql/mysql.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#define TIMUNUM 5
void server_student(int myconnect,MYSQL mysql,char flag)
{
	char mesg[1024];
	char my_sql[1024] = { 0 };//mysql_query
	char buff[2] = {'0'};
	char name[10] = {0};
	char pas[10] = {0};
	char *p = NULL;//split the mesg.
	int i = 0;//mysql_query();
	int num = 0;//the question's num
	char *ia = NULL;// itoa;  a num to char
	MYSQL_RES *res;
	MYSQL_ROW *row;
	bzero(mesg,sizeof(mesg));
	if( flag ==  '0' )
	{
		buff[0] = '0';buff[1] = '0';
		send(myconnect,buff,sizeof(buff),0);//OK. you can do.
//		printf("%c  %c\n",buff[0],buff[1]);
		recv(myconnect,mesg,sizeof(mesg),0);
//		printf("mesg---->%s\n",mesg);
	//	while( strcmp(mesg,"exit") )//deal the chioces loop
		{
			p = strchr(mesg,'|');
		//printf("%s %d %s\n",p,p-mesg,mesg);
			strncpy(name,mesg,p-mesg);
		//printf("%s\n",name);
			strncpy(pas,p+1,strlen(p)-1);
		//printf("%s\n",pas);
			strcat(my_sql,"select sid from student where sname ='");
			strcat(my_sql,name);
			strcat(my_sql,"' and spas ='");
			strcat(my_sql,pas);
			strcat(my_sql,"'");
		//	printf("%s\n",my_sql);
			//mysql_select_db("tiku",&mysql);
			if( i = mysql_query(&mysql,my_sql) )
			{
				printf("cannot know name or password%d\n",i);
				printf("%s\n",mysql_error(&mysql));
				pthread_exit(0);
			}
			res = mysql_store_result(&mysql);
			if( mysql_num_rows(res) == NULL )
			{
				//bzero(mesg,sizeof(mesg)); //deal error
				//strcpy(mesg,"11name or pas error");
				printf("name or password error %d\n",i);
				pthread_exit(0);
			}
			mysql_free_result(res);

			srand((int)time(NULL));//for num
			num = rand()%TIMUNUM/5 + 1;
			bzero(my_sql,sizeof(my_sql));
			strcat(my_sql,"select tname,answer from timu where tid in (");
			ia = (char*)malloc(sizeof(int)+1);
			for( i = 0; i < 5 ; i++)
			{
				sprintf(ia,"%d",num);
				strcat(my_sql,ia);
				if( i != 4 )
				strcat(my_sql,",");
				num = num + 1;
			}
			free(ia);
			strcat(my_sql,")");
//printf("%s\n",my_sql);

			while( mysql_query(&mysql,my_sql) && --i )
				;//5 times
//printf("%d\n",i);
			if( i == 0)
			{
				printf("error %s\n",mysql_error(&mysql));
				pthread_exit(0);
			}
			res = mysql_store_result(&mysql);
			if( mysql_num_rows(res) != NULL)
			{
				bzero(mesg,sizeof(mesg));
//printf("ok\n");
				while(row = mysql_fetch_row(res))
				{
					strcat(mesg,row[0]);
					strcat(mesg,"-");//name-pas;
					strcat(mesg,row[1]);
					strcat(mesg,"|");// 1 | 2 | 3 timu-ans;
				}
				mysql_free_result(res);
			}
			else
			{
				printf("error %s\n",mysql_error(&mysql));
				pthread_exit(0);
			}
//printf("ok\n");
			send(myconnect,mesg,sizeof(mesg),0);
//	printf("%s\n",mesg);
			recv(myconnect,mesg,sizeof(mesg),0);
		}
		pthread_exit(0);
	}
	else if( flag == '1')
	{

	}
	else
	{
		printf("service_studnt recv data error\n");
	}

}
