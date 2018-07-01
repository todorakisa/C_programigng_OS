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
    int fd = open("chat", O_RDONLY);
    char buffer[SIZE];
    ssize_t rbytes;
    while( (rbytes = read(fd, buffer, SIZE)) != 0 )
    {
            write(STDOUT_FILENO, buffer, rbytes);
    }
    close(fd);
    return 0;
}

