/*my own header. Maybe included by other source files*/
#ifndef _mylib_h
#define _mylib_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include<sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 
#define MAXLINE 4096 /*max text line length*/
#define BUFFSIZE 8192 /*buffer size for read and write*/
#define SA struct sockaddr
#define LISTENQ 1024
#define PORT 9988
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);


#endif
