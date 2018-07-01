
//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #2
// FILE NAME: myStrcat.c 
// FILE PURPOSE:
// vzima dva stringa i vrushta drug sting koito e kombinaciq ot minalite dva
// ...
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// FUNCTION: strlen  (име на функцията)
// предназначение на функцията
// PARAMETERS:
// vzima dva masiva ot charove
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strcat( char* destination, const char* source );

int main()
{
	char zdr[20]="ssd";
	char zadr2[20]="sss";
	char *zad = strcat(zdr,zadr2);	
}

char* strcat( char* destination, const char* source )
{
	int i=0,z=0,q=0,t=0;
	for(;source[z]!='\0';z++){}
	for(;destination[i]!='\0';i++){}
	for(q=i;q<=strlen(destination)&&t<=z;q++,t++)
	{
		destination[q]=source[t];
	}
	return destination;
}
