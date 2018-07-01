//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: bmp-info.c (unix file name)
// FILE PURPOSE:
// chete ot argumentite dadena kartinka i namira v pametta kude se namira 
// neiniq height i weight i gi izkarva na konzolata
// ...
//------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

void *read_image(const char *filepath);

int main(int argc,char *argv[])
{
	char *p =read_image(argv[1]);
	uint32_t *p1=p+18, *p2=p+22;
	printf("BMP image width: %d\n",*p1);
	printf("BMP image height: %d\n",*p2);

	return 0;
}

/*void *read_image(const char *filepath){
	int fd = open(filepath, O_RDONLY);
        if (fd < 0) {
            return NULL;
        }
        size_t size = 1000;
        size_t offset = 0;
        size_t res;
        char *buff = malloc(size);

        while((res = read(fd, buff + offset, 100)) != 0) {
                offset += res;
                if (offset + 100 > size) {
                        size *= 2;
                        buff = realloc(buff, size);
                }
        }
        close(fd);
        return buff;
}*/
