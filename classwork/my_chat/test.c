#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

int main(int argc, char **argv){

    pid_t child = fork();
    
    char *argument = malloc(strlen(argv[1])*sizeof(char));
    strcpy(argument,argv[1]);

    if(child < 0){
    	perror("fork");
    }else if(child == 0){
        if(strcmp("What",argument)==0){
            write(STDOUT_FILENO, "Yes i did it", 11);
        }else{
            write(STDOUT_FILENO, "Something went wrong...", 23);
        }
        exit(0);
    }else{

    }
	return 0;
}
