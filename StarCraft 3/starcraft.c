//------------------------------------------------------------------------
// NAME: Simeon Dimitrov
// CLASS: XIb
// NUMBER: 23
// PROBLEM: #1
// FILE NAME: starcraft.c (unix file name)
// FILE PURPOSE: Program for digging minerals with multi pthreads
//------------------------------------------------------------------------

#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int bloks = 2;
int marines = 0;
int minersNum = 5;
int centerMinerals = 0;
pthread_t miners_[1000];
pthread_mutex_t MutexMineralsCenter;
pthread_mutex_t mutex_soldiers;

int *mineralsOfBloks;
pthread_mutex_t *bloksMutex;

void* miners(void* attr){
    int MinerNumber = (int*)attr;
    int fullbloks[bloks];
    int breakCon = 0,j = -1,miner_resource = 0;
    for(int l = 0; l < bloks; l++)
    {
        fullbloks[l] = 1;
    }

    while(1)
    {
        j++;
        if(j == bloks)
        {    
            j = 0;
        }
        for(int i = 0;i < bloks;i++)
        {
            if(fullbloks[i] == 0)
            {
                breakCon++;
            }
            if(breakCon == bloks)
            {
                return NULL;
            }
        }
        sleep(3);
        if(fullbloks[j] == 0)
        {
            j++;
            if(j == bloks)
            {    
                j = 0;
            }
            continue;
        }
        if(pthread_mutex_trylock(&bloksMutex[j]) == 0)
        {
            if(mineralsOfBloks[j] > 4)
            {
                mineralsOfBloks[j] -= 8;
                miner_resource += 8;            
            }
            else if(mineralsOfBloks[j] == 4)
            {
                fullbloks[j] = 0; 
                miner_resource += 4;
                mineralsOfBloks[j] -= 4;
            }
            else if(mineralsOfBloks[j] == 0)
            {
                pthread_mutex_unlock(&bloksMutex[j]);
                fullbloks[j] = 0;
                j++;
                if(j == bloks)
                {    
                    j = 0;
                }
                continue;
            }
            printf("SCV %d is mining from mineral bloc %d\n",MinerNumber,j+1);
            pthread_mutex_unlock(&bloksMutex[j]);
            printf("SCV %d is transporting minerals\n",MinerNumber);
            sleep(2);
            pthread_mutex_lock(&MutexMineralsCenter);
            printf("SCV %d delivered minerals to the Command center\n",MinerNumber);
            if(miner_resource == 4){
                centerMinerals += 4;
                miner_resource -= 4;
            }else{
                centerMinerals += 8;
                miner_resource -= 8;
            }
            pthread_mutex_unlock(&MutexMineralsCenter);
        }
    }
    return NULL;
}

void run()
{
    char c = 0;
    int maxMinerals = bloks * 500;
    while(1)
    {
        scanf("%c",&c);
        switch(c)
        {
            case 's':
                pthread_mutex_lock(&MutexMineralsCenter);
                if(centerMinerals < 50)
                {
                    printf("Not enough minerals.");
                }else{
                    sleep(4); 
                    centerMinerals -= 50;
                    printf("SCV good to go, sir.\n");                   
                    minersNum++;
                    pthread_create(&miners_[minersNum],NULL,miners,minersNum);
                }
                pthread_mutex_unlock(&MutexMineralsCenter);
            break;
            case 'm':
                pthread_mutex_lock(&MutexMineralsCenter);
                if(centerMinerals < 50)
                {
                    printf("Not enough minerals."); 
                }else{
                    sleep(1);  
                    pthread_mutex_lock(&mutex_soldiers);
                    marines+=1;
                    pthread_mutex_unlock(&mutex_soldiers);
                    printf("You wanna piece of me, boy?\n");
                    centerMinerals-=50;
                }
                pthread_mutex_unlock(&MutexMineralsCenter);
            break;
        }
        pthread_mutex_lock(&mutex_soldiers);
        if(marines == 20)
        {
            for (int i = 0; i < minersNum; ++i)
            {
                int z = pthread_join(miners_[i], NULL);
            }
            break;
        }
        pthread_mutex_unlock(&mutex_soldiers);
    }
    printf("Map minerals %d,player minerals %d, SCVs %d, Marines %d\n",maxMinerals,centerMinerals,minersNum,marines);
    free(mineralsOfBloks);
    free(bloksMutex);
}

int main(int argc, char **argv)
{
    if(argc > 1)
    {
        bloks = atoi(argv[1]);
    }

    int i = 0;
    centerMinerals = 0;
    mineralsOfBloks = malloc(bloks * sizeof(int));
    bloksMutex = malloc(bloks * sizeof(pthread_mutex_t));
    pthread_mutex_init(&MutexMineralsCenter,NULL);
    pthread_mutex_init(&mutex_soldiers,NULL);

    for(i = 0; i < bloks; i++)
    {
        mineralsOfBloks[i] = 0;
        pthread_mutex_init(&bloksMutex[i],NULL);
        mineralsOfBloks[i] += 500;
    } 
    for (i = 0; i < 5; ++i)
    {   
        int p = pthread_create(&miners_[i],NULL,miners,i + 1);
    }
    run();
    return 0;
}