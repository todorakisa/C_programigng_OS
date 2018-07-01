//--------------------------------------------
//NAME: Todor Dimitrov
//CLASS: 11b
//NUMBER: 27
//PROBLEM: #1
//---------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
int NUM_OF_MINERS = 1;
int NUM_OF_TRADERS = 1;
 
int  gold;
pthread_mutex_t mutex; 
 
void* miner(void* attr)
{
    int i;
    int num = (int)attr;
 
    for (i = 0; i < 20; ++i)
    {
        pthread_mutex_lock(&mutex);
        gold += 10;
        printf("Miner %d gathered 10 gold\n",num+1);
        pthread_mutex_unlock(&mutex);
        
        sleep(2);
    }
    return NULL;
}

void* trader(void* attr)
{
    int i;
    int num = (int)attr;

    for (i = 0; i < 20; ++i)
    {
       
        if(gold==0){
            printf("The warehouse is empty, cannot sell!\n");
        }else{
        pthread_mutex_lock(&mutex);
            gold -= 10;   
        pthread_mutex_unlock(&mutex);
        printf("Trader %d sold 10 gold\n",num+1);
        }
        
        sleep(2);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    if(argc!=1){
        NUM_OF_MINERS = atoi(argv[1]);
        NUM_OF_TRADERS = atoi(argv[2]);
    }
    pthread_mutex_t mutex;
    pthread_t threads_miner[NUM_OF_MINERS];
    pthread_t threads_trader[NUM_OF_TRADERS];
    pthread_mutex_init(&mutex,NULL);
    int i;
    for (i = 0; i < NUM_OF_MINERS; ++i)
    {    
        pthread_create(&threads_miner[i],NULL,miner,i);
    }
    for (i = 0; i < NUM_OF_TRADERS; ++i)
    {
        pthread_create(&threads_trader[i],NULL,trader,i);
    }
 
    for (i = 0; i < NUM_OF_TRADERS; ++i)
    {
        pthread_join(threads_trader[i], NULL);
    }

    for (i = 0; i < NUM_OF_MINERS; ++i)
    {
        pthread_join(threads_miner[i], NULL);
    }

    printf("Gold: %d\n",gold);
    pthread_mutex_destroy(&mutex);
    return 0;
}
