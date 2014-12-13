#include "mylib.h"
#include <iostream>

using namespace std;

/*deal exception briefly*/
void err_dump(const char* fmt,... )
{
	cout<<"err_dump:"<<fmt<<endl;
}
void err_msg(const char *fmt,...)
{
	cout<<"err_msg:"<<fmt<<endl;
}
void err_quit(const char* fmt,...)
{
	cout<<"err_quit:"<<fmt<<endl;
}
void err_ret(const char * fmt,...)
{
	cout<<"err_ret:"<<fmt<<endl;
}
void err_sys(const char * fmt,...)
{
	cout<<"err_sys:"<<fmt<<endl;
}
