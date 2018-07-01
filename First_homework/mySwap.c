
//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #3
// FILE NAME: mySwap.c 
// FILE PURPOSE:
// vzima dve promenlivi i im razmenq stoinostite
// ...
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// FUNCTION: swap  (име на функцията)
// предназначение на функцията
// PARAMETERS:
// vzima dve promenlivi
//------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>

void swap(int *a, int *b);
int main()
{
int a=3,b=4;
swap(&a,&b);
printf("%d%d",a,b);
}
void swap(int *a , int *b)
{
int c=*b;
*b=*a;
*a=c;
}
