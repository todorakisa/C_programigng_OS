#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
int main(){
	int fd = open("chat", O_WRONLY);
	char buffer[SIZE];
	ssize_t rbytes;
	while( (rbytes = read(STDIN_FILENO, buffer, SIZE)) != 0 )
	{
		write(fd, buffer, rbytes);
	}	
	close(fd);
	return 0;
}
