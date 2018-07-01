#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,  char **argv){

struct stat st;

    for(int i=1;i<argc;i++){
        int t = stat(argv[i],&st);
        if(t!=0){
            perror("stat:");
            return 1;
        }
        printf("%s %ld\n",argv[i],st.st_size);
    }
    return 0;
}
