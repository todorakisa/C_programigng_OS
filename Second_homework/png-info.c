
//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #2
// FILE NAME: png-info.c (unix file name)
// FILE PURPOSE:
// chete edna kartinka i namira mestata v pametta kudeto se suhranqva weight i hight
// i posle gi zivajda na konzolata
// ...
//------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>

void *read_image(const char *filepath);

int main(int argc,char *argv[])
{
        char *p =read_image(argv[1]);
	if(p==NULL)
	{
		printf("Unable to open file");
		return 0;
	}
	if(*(p+1)!='P'||*(p+2)!='N'||*(p+3)!='G')
	{
		printf("Unable to parse file");
		return 0;
	}else{
        uint32_t *p1=p+16, *p2=p+20;
        printf("PNG image width: %d\n",ntohl(*p1));
        printf("PNG image height: %d\n",ntohl(*p2));
	for(int i=0;;i++)
	{
		if(*(p+i)=='I'&&*(p+i+1)=='E'&&*(p+i+2)=='N'&&*(p+i+3)=='D'){
		printf("PNG file size: %d\n",i+8);
		return 0;
		}
	}
        }
	return 0;	
}
