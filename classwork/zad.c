#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc,char **argv){
	char *arguments[20];
	int t=1,i=0;
	if(argc > 3){
		arguments[0] = argv[2];
		for(i=3;i<argc;i++){
			arguments[t] = argv[i];
			t++;
		}
		arguments[t] = NULL;
	}else{
		arguments[0] = argv[2];
		arguments[1] = NULL; 
	}
	for(i=0;i<atoi(argv[1]);i++){
	pid_t pid = fork();
		if(pid == 0){
			int p = execv(argv[2],arguments);
			if(p<0){
				perror(argv[2]);
			}
			exit(0);	
		}else{
			waitpid(pid, 0 ,0);
		}
		
	}
return 0;
}
