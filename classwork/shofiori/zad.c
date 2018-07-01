#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
int NUM_OF_DRIVERS = 20;
pthread_mutex_t cars[5];
 
void* driver(void* attr)
{
    int i;
    int num = (int)attr;
    int car = 0;
    int tryedcar[5];

    for(int i=0;i<5;i++){
        tryedcar[i] = 0;
    }
    
    while(1)
    {
        if(tryedcar[car] == 0 && pthread_mutex_trylock(&cars[car]) == 0){
        printf("Buyer %d takes car %d.\n",num,car);
        sleep(1);
        tryedcar[car] = 1;
        printf("Buyer %d returns car %d.\n",num,car);
        pthread_mutex_unlock(&cars[car]);
        if(tryedcar[0] == 1 && tryedcar[1] == 1 && tryedcar[2] == 1 && tryedcar[3] == 1 && tryedcar[4] == 1 ){        
            break;
        }
        }else if(car<4){
            car++;
        }else{
            car = 0;
        }
    }
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t threads_driver[NUM_OF_DRIVERS];
    pthread_mutex_init(&cars[5],NULL);

    for (int i = 0; i < NUM_OF_DRIVERS; ++i)
    {    
        pthread_create(&threads_driver[i],NULL,driver,i + 1);
    }
    for (int i = 0; i < NUM_OF_DRIVERS; ++i)
    {
        pthread_join(threads_driver[i], NULL);
    }
    //sudo apt install glibc-doc
    pthread_mutex_destroy(&cars[5]);
    return 0;
}
