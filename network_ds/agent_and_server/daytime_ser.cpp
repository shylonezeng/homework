#include "my_lib/mylib.h"
#include <fcntl.h>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <sys/epoll.h>
#include <iostream>
#include <errno.h>
#define MAXSIZE 1024

using namespace std;

typedef void Sigfunc(int);
//inter signel deal 
void sig_chld(int sigid)
{
	pid_t pid;
	int stat;
	if((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("child process %d is terminated\n", pid);
	return ;		
}
//set signal deal function
Sigfunc* signal(int sgid, Sigfunc *func)
{
	struct sigaction act,old_act;

	act.sa_handler=func;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	if(sigaction(sgid,&act,&old_act)<0)
		return SIG_ERR;
	return old_act.sa_handler;		

}
void read_and_write(int);

int setnoblock(int fd){
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL,new_option);
	return old_option;
}
void addfd(int epollfd,int fd,bool one_shot){
	epoll_event event;
	event.data.fd=fd;
	event.events = EPOLLIN | EPOLLET;	

	if(one_shot){
		event.events |= EPOLLONESHOT;
	}
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnoblock(fd);
}

int clients[MAXSIZE];
int cur_pos=0;
int main(int argc, char ** argv)
{
	int sockfd ;
	struct sockaddr_in servaddr;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
		err_sys("socket fault");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);	
	servaddr.sin_port=htons(PORT);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));	
	int ret=listen(sockfd,LISTENQ);
	if(ret<0)
		cout<<"failed to listen socket"<<endl;
	//deal with INTER signal
	signal(SIGCHLD,sig_chld);

	int epollfd=epoll_create(5);
	addfd(epollfd,sockfd,false);

	int stdifd=fileno(stdin);
	addfd(epollfd,stdifd,false);

	//accept connection and produce childprocess to deal with it
	int connfd;
#define MAX_EVENT_NUMBER 100
	epoll_event events[MAX_EVENT_NUMBER];
	cout<<"listening..."<<endl;
	while(true)
	{
		int ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);	
		if(ret<0){
			cout<<"failed to epoll wait "<<endl;
			break;
		}

		for(int i=0;i<ret;++i){
			int fd=events[i].data.fd;
			if(fd == sockfd){
				connfd=accept(sockfd,NULL,NULL)	;
				addfd(epollfd,connfd,false);
				cout<<"new connection, connfd id: "<<connfd<<endl;

				clients[cur_pos++]=connfd;
				if(cur_pos>MAXSIZE)
				{
					//one more connection permitted only
					err_dump("no more connection allowed\n");
					cur_pos--; 
				}

				/*		int pid=fork();
						if(pid==0)
						{
						close(listenfd);
						fprintf(stdout,"sub process %d serving:\n",getpid());
						read_and_write(connfd);
						}
						close(connfd);
						*/
			}
			else if(fd== stdifd){

				char rt_info[MAXSIZE],buff[MAXSIZE];
				int n;
				if((n=read(stdifd,rt_info,MAXSIZE))>0){
					cout<<"sending command to clients:"<<rt_info<<endl;
					for(int i=0;i<cur_pos;++i)
					{
						int clt_id=clients[i];
					//	sprintf(rt_info,"send to connID%d#: %s\n",clt_id,buff);
						write(clt_id,rt_info,strlen(rt_info));
						cout<<"agent client #"<<clt_id<<" sent"<<endl;

					}
				}
				else if(n==-1)
					cout<<strerror(errno)<<endl;
			}
			else{
				cout<<"unknown file descriptor"<<endl;
			}
		}/*end while*/


	}/*end for*/
}
/*
   void read_and_write(int connfd)
   {
   int n;
   char buff[MAXSIZE];
   char rt_info[MAXSIZE];
   while((n=read(connfd,buff,sizeof(buff)))>0)
   {
   char rt_info[MAXSIZE];
   printf("received: %s\n",buff);
   if(strlen(buff)!=0)
   {
//	int pid=fork();
//	if(fork==0)
{
for(int i=0;i<cur_pos;++i)
{
int clt_id=clients[i];
sprintf(rt_info,"connID%d#: %s\n",clt_id,buff);
//		fputs(rt_info,stdout);
write(clt_id,rt_info,strlen(rt_info));
}
}
}
}	
//have not yet deal with SIG_INTER from other processes
//...
}
*/
