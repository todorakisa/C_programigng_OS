//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: head.c
// FILE PURPOSE:
// otvarq fail i zapochva ot daden bait i printira baitove spored towa kolko sled tova iskame da printirame
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
	int fd = open(argv[1],O_RDONLY); 
	short read_bytes,linecount = 0;
	char buffer[1];
	int start = atoi(argv[2]);
	int bytes = atoi(argv[3]) ;
	
	int u=0;
	off_t size = lseek(fd,start,SEEK_SET);

	while(1){
		
		read_bytes = read(fd, buffer, 1);
		if( read_bytes == 0 ){
			break;
		}
		write(STDOUT_FILENO, buffer, 1);
		u++;
		
		if(u==bytes){break;}                                                        
	}
	if(close(fd) < 0){
		perror( "ERR: close_" );
		return 4;
	}
	return 0;
}
