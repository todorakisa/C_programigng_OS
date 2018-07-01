//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: myChat_v1.c (unix file name)
// FILE PURPOSE:
// osushtestvqva komunikaciq mejdu dva procesa s imenuvani pipe-ove
// ...
//------------------------------------------------------------------------
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

    int fd,fd2;
    char buffer_read[SIZE];
    char buffer_write[SIZE];
    ssize_t rbytes;
    pid_t pid = fork();
    if(pid < 0){
    	perror("fork");
    }else if(pid == 0){ 
    	fd2 = open(argv[2], O_RDONLY);
		if(fd2<0){
			perror("open fd2");
		}  
    	while( (rbytes = read(fd2, buffer_read, SIZE)) != 0 )
    	{
    	    if(rbytes < 0){
    	        perror("read");
    	    }
            write(STDOUT_FILENO, buffer_read, rbytes);
    	}
    	exit(0);
    }else{
    	fd = open(argv[1], O_WRONLY);
    	if(fd<0){
    		perror("open fd");
    	}
		while( (rbytes = read(STDIN_FILENO, buffer_write, SIZE)) != 0 )
		{
		    if(rbytes < 0){
    	        perror("read");
    	    }
			write(fd, buffer_write, rbytes);
		}		
    }
    close(fd);
    close(fd2);
	return 0;
}
