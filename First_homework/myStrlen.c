
//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: myStrlen.c 
// FILE PURPOSE:
// namira kolko e dulug string
// ...
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// FUNCTION: strlen  (име на функцията)
// предназначение на функцията
// PARAMETERS:
// vzima edin masiv ot charove
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

size_t strlen( const char *);

int main()
{
char string[1000];
fgets(string,1000,stdin);
size_t g = strlen(string);
printf("%zx",g);
}

size_t strlen( const char* str)
{
	size_t i=0;
	for(;str[i]!='\0';i++){}
	return i;
}

