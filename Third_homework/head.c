//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: head.c
// FILE PURPOSE:
// otvarq fail i chete purvite 10 reda ot faila i gi printira
//------------------------------------------------------------------------

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int myHeadMethod();

int main(){
	int fd = open("a.txt",O_RDONLY); 
	short read_bytes,linecount = 0;
	short err_check,err_check_2;
	char buffer[1];
	
	if(fd < 0){
		perror( "ERR: open_" );
		return 1;
	}
	
	while(1){
		
	read_bytes = read(fd, buffer, 1);

		if(read_bytes < 0){
			perror( "ERR: read_" );
			return 2;
		}else if( read_bytes == 0 ){
			break;
		}
	
		if(linecount == 10){break;}
		else if(buffer[0]=='\n'){
		linecount++;
		}
	
	err_check = write(STDOUT_FILENO, buffer, 1);
		if( err_check < 0){
			perror( "ERR: write_" );
			return 3;	
		}
	}
	
	err_check_2 = close(fd);
	if(err_check_2 < 0){
		perror( "ERR: close_" );
		return 4;
	}
	return 0;
}

int myHeadMethod(){
int fd = open("a.txt",O_RDONLY);
         short read_bytes,linecount = 0;
         short err_check,err_check_2;
         char buffer[1];
 
        if(fd < 0){
                         perror( "ERR: open_" );
                                          return 1;
         }
 
         while(1){
                 
         read_bytes = read(fd, buffer, 1);
 
                 if(read_bytes < 0){
                         perror( "ERR: read_" );
                         return 2;
                 }else if( read_bytes == 0 ){
                         break;
                 }

                 if(linecount == 10){break;}
                else if(buffer[0]=='\n'){
                 linecount++;
                 }
 
         err_check = write(STDOUT_FILENO, buffer, 1);
                 if( err_check < 0){
                         perror( "ERR: write_" );
                         return 3;
                 }
         }                                                    
}


