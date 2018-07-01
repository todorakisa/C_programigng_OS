
//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #4
// FILE NAME: myVoidSwap.c 
// FILE PURPOSE:
// vzima dve kakvito i da sa promenlivi i im razmenq stoinostite
// ...
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// FUNCTION: VoidSwap  (име на функцията)
// предназначение на функцията
// PARAMETERS:
// vzima dva pointera km promenlivi ot kakuvto i da e tip i vzima i kolko 
// bita zaemat dadenite promenlivi
//------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *strdup( const char * );

int main()
{

}

char *strdup( const char *origin ){
	char b;
	char *newString = malloc(sizeof(origin));
	for(int i=0;i<strlen(origin);i++)
	{
		newString[i]=origin[i];
	}
	newString[strlen(origin)]='\0';
	return newString;
}
