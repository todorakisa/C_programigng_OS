//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: zad.c 
// FILE PURPOSE:
// vseki put kato trqbva da kalkulira prostite chisla go pravi v otdelna nishka
//------------------------------------------------------------------------
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#define NUM_THREADS 5
 
void *pintAllPrimeNumbersToN(void* fake_n)
{
    int n;
    n = (int)fake_n;

    printf("Prime calculation started for N=%d\n",n);
    int broi=1;
    int flag = 1;
    int num_of_primes=0;
    for(int z=2;z<n;z++,broi++){
        for(int i=2;i<z;i++){
            if(z%i==0){
                flag=0;
                break;
            }    
        }
        if(flag){
            num_of_primes++;
        }else{
            flag=1;
        }
    }
    printf("Number of primes for N=%d is %d\n",n,num_of_primes);
    fflush(stdout);
}

int main()
{
    pthread_t thread[100];
    int n,i;
    char masive[200];
    for(i=0;;i++){
        scanf("%s",masive);
        if(strlen(masive)==1 && masive[0]=='p'){
            scanf("%d",&n);
            int rc = pthread_create(&thread[i],NULL,pintAllPrimeNumbersToN,(void*)n);
            if(rc)
            {
                printf("ERROR: pthread_create() return %d\n",rc);
                exit(-1);
            }
        }else if(strlen(masive)==1 && masive[0]=='e'){
            break;
        }else{
            printf("Supported commands:\n p N - Starts a new calculation for the number of primes from 1 to N\n e - Waits for all calculations to finish and exits\n");
        }
    }
    for(int br=0;br < i;br++){
        int rc = pthread_join(thread[br],NULL);
    }
    return 0;
}
