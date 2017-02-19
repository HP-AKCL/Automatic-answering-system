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
	char *swap = NULL;//split the mesg.
	int i = 0;//mysql_query();
	int sid = 0;
	int tid = 0;
	int num = 0;//the question's num
	char *ia = NULL;// itoa;  a num to char
	MYSQL_RES *res;
	MYSQL_ROW *row;
//	recv(myconnect,buff,sizeof(buff),0);//student's chioces
	bzero(mesg,sizeof(mesg));
	if( flag ==  '0' )
	{
		buff[0] = '0';buff[1] = '0';
//		send(myconnect,buff,sizeof(buff),0);//OK. you can do.
//		printf("%c  %c\n",buff[0],buff[1]);
			i = 0;
			recv(myconnect,mesg,sizeof(mesg),0);
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
			row = mysql_fetch_row(res);
			sid = atoi(row[0]);
			mysql_free_result(res);
//		printf("mesg---->%s\n",mesg);
		bzero(buff,sizeof(buff));
		recv(myconnect,buff,sizeof(buff),0);
		while( buff[0] == '0' && buff[1] != '3' )//deal the chioces loop
		{
			srand((int)time(NULL));//for num
			num = rand()%TIMUNUM/5 + 1;
			tid = num;
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
			send(myconnect,mesg,sizeof(mesg),0);//send an qu to s
			recv(myconnect,mesg,sizeof(mesg),0);//student's answer
			ia = (char *)malloc(sizeof(int)+1);
			swap = mesg;
			for( i = 0; i < 5 ; i++)//insert into asnwer.
			{
				bzero(my_sql,sizeof(my_sql));
				bzero(pas,sizeof(pas));
				strcat(my_sql,"insert into answer values(");
				sprintf(ia,"%d",tid++);
				strcat(my_sql,ia);
				strcat(my_sql,",");
				sprintf(ia,"%d",sid);
				strcat(my_sql,ia);
				strcat(my_sql,",'");
/**  **/
				if( 4 != i)
				{
					p = strchr(swap,'|');
					strncpy(pas,swap,p-swap);
					swap = p + 1;
					strcat(my_sql,pas);
				}
				else
				{
					strcat(my_sql,swap);
				}
				strcat(my_sql,"',");
				strcat(my_sql,"'20170112');");
				mysql_query(&mysql,my_sql);
//printf("%s\n",my_sql);
			}
			free(ia);
			bzero(buff,sizeof(buff));
			recv(myconnect,buff,sizeof(buff),0);
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
