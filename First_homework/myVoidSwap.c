
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

#include<stdlib.h>
#include<stdio.h>

void swap(void *a, void *b, size_t size);

int main(){

}

void swap(void *a, void *b, size_t size)
{
	char *q=a ,*w=b;
	char *help = malloc(1);
	for(size_t i=0;i<size;i++)
	{
		*help = q[i];
		q[i] = w[i];
		w[i] = *help;
	}	 
}

