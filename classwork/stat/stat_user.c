#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<errno.h>
#include<pwd.h>

int main(int argc,  char **argv){

struct stat st;
struct passwd *z;
    for(int i=1;i<argc;i++){
        int t = stat(argv[i],&st);
        if(t!=0){
            perror("stat:");
            return 1;
        }
        z = getpwuid(st.st_uid);
        printf("%s %s\n",argv[i],z->pw_name);
    }
    return 0;
}
