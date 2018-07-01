//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #6
// FILE NAME: myStack.c (unix file name)
// FILE PURPOSE:
// osushtestvqva struktorata stack
// ...
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

struct stack_t{
    size_t size;
    size_t capacity;
    int *elements;
}stack;

void stack_init(struct stack_t* );
void stack_destroy(struct stack_t * );

int stack_empty(struct stack_t * );
void stack_push(struct stack_t *, int );
int stack_top(struct  stack_t * );
void stack_pop(struct  stack_t * );

int main(){
/*struct stack_t packa;
stack_init(&packa);
printf("%d",stack_empty(&packa));
stack_push(&packa,45);
printf("%d",stack_empty(&packa));
printf("%d",stack_top(&packa));
stack_pop(&packa);
printf("%d",stack_empty(&packa));*/
}

void stack_init(struct stack_t* p){
	p->size=0;
	p->elements = malloc(p->capacity*sizeof(int));
}

void stack_destroy(struct stack_t * p){
	p->size=0;
	p->capacity=0;
	free(p->elements);
	p->elements=NULL;
}

int stack_empty(struct stack_t * p){
	return p->size==0;
}

void stack_push(struct stack_t * p, int elem){
	p->elements[p->size++]=elem;
}

int stack_top(struct  stack_t * p){
	return p->elements[p->size-1];
}
void stack_pop(struct  stack_t * p){	
	p->size--;
}
