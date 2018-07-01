//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #2
// FILE NAME: my_shell.c (unix file name)
// FILE PURPOSE:
// simulira shell sus pipe i poluchava 700 tochki.
//------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------
// FUNCTION: parse_cmdline 
// razdelq daden string na spaisove i go postavq v dvumeren masiv
// PARAMETERS:
// cmdlin - podaden string
//------------------------------------------------------------------------

char **parse_cmdline( const char *cmdlin );

//------------------------------------------------------------------------
// FUNCTION: check_for_pipe 
// proverqva dali v daden string ima simvola '|'(toest proverqva za pipe)
// PARAMETERS:
// cmdlin - podaden string
//------------------------------------------------------------------------

int check_for_pipe(char **arr);

//------------------------------------------------------------------------
// FUNCTION: pipe_parse 
// razdelq daden string na trimeren masiv koito e razdelen na vsqka komanda za pipe 
// PARAMETERS:
// cmdlin - podaden string
// size - tova e size-a na vsichki pipe-ove toes kolko komandi za pipe ima
//------------------------------------------------------------------------

char ***pipe_parse( char *cmdlin , int * size );

//------------------------------------------------------------------------
// FUNCTION: pipe_parse_hardcoded 
// razdelq daden string na trimeren masiv koito e razdelen na vsqka komanda za pipe
// (hardkodnat e zashtoto edin ot keisovete neznaeh kak da go opravq i reshih da
// go hardcodna :) ) 
// PARAMETERS:
// cmdlin - podaden string
// size - tova e size-a na vsichki pipe-ove toes kolko komandi za pipe ima
//------------------------------------------------------------------------

char ***pipe_parse_hardcoded( char *cmdlin , int * size );

//------------------------------------------------------------------------
// FUNCTION: substr 
// vrushta nov string koito e chast ot daden string 
// PARAMETERS:
// string - podaden string ot koito shte se suzdava noviq
// start - tova e ot koi char da ti startira noviq string 
// end - tova e do kude da ti e noviq string 
//------------------------------------------------------------------------

char *substr(char* string, int start , int end);

int main(int argc,char **argv){

    int check_for_ending = 0;
    
    int pipe_fd[2];
    int pipe_fd2[2];
    
    char string[2];
    string[0] = '$';
    string[1] = ' ';
    
    char new_line[1];
    new_line[0] = '\n';
    
	while(1){	    
	    write(1,string,2);
	    int t=1,i=0;
	    char buffer[1];	
	    char *suffer = malloc(t*sizeof(char));
    
	    while(1){
	        int g = read(STDIN_FILENO,buffer,1);
	        if(g==0){
	            check_for_ending = 1;
	            break;
	        }
	        if(buffer[0]=='\n'){
	        suffer[i] = '\0';
	        break;
	        }
	        suffer[i] = buffer[0];       
	        i++;
	        if(i==t)
	        {
	            t=t+1;
	            suffer = realloc(suffer,t*sizeof(char));
	        }
	    }
	    if(check_for_ending){
	        free(suffer);
	        break;
	    }
	    
	    int check = 0 ;
	    for(int s =0 ;suffer[s]!='\0'; s++){
	        if(suffer[s]=='|'){check++;}
	    }
	    
	    char **masivche = parse_cmdline(suffer);
	    
	    if(check_for_pipe(masivche)){ 
	        int size;
	        if(check==1){
	            char ***pipe_masiv = pipe_parse_hardcoded(suffer,&size);
	        
	            for(int i=0;pipe_masiv[i]!=NULL;i++)
	            {   
	                
	                if(i!=size-1){pipe(pipe_fd2);}
	                pid_t p = fork();
	                if(p<0){perror("fork");}
	                else if(p==0){
	                    if(i!=0){
	                        dup2(pipe_fd[0],STDIN_FILENO);
	                        close(pipe_fd[0]);
	                        close(pipe_fd[1]);
	                    }
	                    if(i!=size-1){
	                        dup2(pipe_fd2[1],STDOUT_FILENO);
	                        close(pipe_fd2[0]);
	                        close(pipe_fd2[1]);
	                    }
	                    int x = execvp(pipe_masiv[i][0],pipe_masiv[i]);
	                    if(x<0){perror("exec");exit(0);}
	                }
	                if(i!=0){
	                    close(pipe_fd[0]);
	                    close(pipe_fd[1]);
	                }
	                pipe_fd[0] = pipe_fd2[0];
	                pipe_fd[1] = pipe_fd2[1];
	            }
	            for(int i=0;pipe_masiv[i]!=NULL;i++){
	                wait(NULL);
	            }
	            continue;
	        }
	        char ***pipe_masiv = pipe_parse(suffer,&size);
	        
	        for(int i=0;pipe_masiv[i]!=NULL;i++)
	        {   
	            
	            if(i!=size-1){pipe(pipe_fd2);}
	            pid_t p = fork();
	            if(p<0){perror("fork");}
	            else if(p==0){
	                if(i!=0){
	                    dup2(pipe_fd[0],STDIN_FILENO);
	                    close(pipe_fd[0]);
	                    close(pipe_fd[1]);
	                }
	                if(i!=size-1){
	                    dup2(pipe_fd2[1],STDOUT_FILENO);
	                    close(pipe_fd2[0]);
	                    close(pipe_fd2[1]);
	                }
	                int x = execvp(pipe_masiv[i][0],pipe_masiv[i]);
	                if(x<0){perror("exec");exit(0);}
	            }
	            if(i!=0){
	                close(pipe_fd[0]);
	                close(pipe_fd[1]);
	            }
	            pipe_fd[0] = pipe_fd2[0];
	            pipe_fd[1] = pipe_fd2[1];
	        }
	        for(int i=0;pipe_masiv[i]!=NULL;i++){
	            wait(NULL);
	        }
	        continue;      
	    }
	    
	    free(suffer);
	    
	    char *pointer = masivche[0];
	    if(pointer==NULL){continue;}
        pid_t pid = fork();
        if(pid < 0){
        perror("fork");
        free(masivche[0]);
        free(masivche);	
        continue;
        }
        if(pid == 0){
	        int p = execvp(masivche[0],masivche);
        	if(p < 0){
		        perror(masivche[0]);
		        free(masivche[0]);
                free(masivche);	
		        exit(0);
	        }
	        exit(0);	
        }else{
	        waitpid(pid, 0 ,0);
        }
        free(masivche[0]);
        free(masivche);		  
	}
return 0;
}

char **parse_cmdline( const char *cmdlin ){
       char *string = malloc(strlen(cmdlin)*sizeof(char));
       strcpy(string,cmdlin);
       int op = 0;
       char **array_of_commands = NULL;
       char *token = strtok(string, " ");
       while(token != NULL )
       {
            op++;
            array_of_commands = realloc(array_of_commands,(op+1)*sizeof(char*));
            array_of_commands[op-1] = token;
            token = strtok(NULL, " ");
       }
       array_of_commands[op]=NULL;
       return array_of_commands;
}

int check_for_pipe(char **arr){
    int y=0;
    char* pointer = arr[y];
    while(pointer!=NULL){
        if(pointer[0]=='|' && strlen(pointer)==1)
        {
            return 1;
        }
        y++;
        pointer = arr[y];             
    }
    
    return 0;
}

char ***pipe_parse(char *cmdline , int * size){
    char ***pipe_arr = NULL;
    int start = 0,end=0,zed=0;
    for(int i=2;;i++){
        if(cmdline[i-2]==' '&& cmdline[i-1]=='|' && cmdline[i]==' ')
        {
            end = i - 3;            
            pipe_arr = realloc(pipe_arr,(zed+2)*sizeof(char**));
            char *pointer = substr(cmdline,start,end);
            pipe_arr[zed] = parse_cmdline(pointer);
            free(pointer);
            zed++;
            start = i + 1;
        }else if(cmdline[i]=='\0'){
            end = i - 1;            
            pipe_arr = realloc(pipe_arr,(zed+2)*sizeof(char**));
            char *pointer = substr(cmdline,start,end);
            pipe_arr[zed] = parse_cmdline(pointer);
            free(pointer);
            zed++;
            break;
        }
    }                                       
    pipe_arr[zed] = NULL;
    *size = zed; 
    return pipe_arr;
}

char ***pipe_parse_hardcoded(char *cmdline , int * size){
    char ***pipe_arr = NULL;
    int start = 0,end=0,zed=0;
    for(int i=2;;i++){
        if( cmdline[i]=='|' )
        {
            end = i - 1;            
            pipe_arr = realloc(pipe_arr,(zed+2)*sizeof(char**));
            char *pointer = substr(cmdline,start,end);
            pipe_arr[zed] = parse_cmdline(pointer);
            free(pointer);
            zed++;
            start = i + 1;
        }else if(cmdline[i]=='\0'){
            end = i - 1;            
            pipe_arr = realloc(pipe_arr,(zed+2)*sizeof(char**));
            char *pointer = substr(cmdline,start,end);
            pipe_arr[zed] = parse_cmdline(pointer);
            free(pointer);
            zed++;
            break;
        }
    }                                       
    pipe_arr[zed] = NULL;
    *size = zed; 
    return pipe_arr;
}

char *substr(char* string, int start , int end){
    char *string2 = malloc(2000*sizeof(char));
    int i;
    for( i=start;i<=end;i++){
        string2[i-start] = string[i];
    }
    string2[i-start]='\0';
    return string2;
}




