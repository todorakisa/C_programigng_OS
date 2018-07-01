//------------------------------------------------------------------------
// NAME: Todor Dimitrov
// CLASS: XIb
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: my_ls.c (unix file name)
// FILE PURPOSE:
// simulira ls i sa dobaveni flagovete -R,-A,-l
//------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

//------------------------------------------------------------------------
// FUNCTION: printDir 
// Podava i se direktoriq i tq q printira v konzolata spored uslovieto
// PARAMETERS:
// char* Directory - podaden string
//------------------------------------------------------------------------
int printDir(char* Directory);
//------------------------------------------------------------------------
// FUNCTION: whatFile
// podava i se structora stat i tq proverqva dali podadenata structora e fail,
// direktoriq ili neshto drugo spored mod i vrushta suotvetniq charakter
// PARAMETERS:
// st - podadena structora stat
//------------------------------------------------------------------------
char whatFile(struct stat* st);
//------------------------------------------------------------------------
// FUNCTION: chekForFlags
// podava is se argument i tq proverqva dali e flag.Ako e flag otbelqzva v 
// globalniq masif za flagove za da moje posle printDir da se orientira i da printira pravilno
// PARAMETERS:
// char* argument - podaden string
//------------------------------------------------------------------------
int chekForFlags(char* argument);
//------------------------------------------------------------------------
// FUNCTION: printMore
// podava i se struktora ot tip stat i printira poveche informaciq za faila,
// tazi funkciq e napravena za poddrujkata na flaga -l.
// PARAMETERS:
// st - podadena structora stat
//------------------------------------------------------------------------
void printMore(struct stat* st);
//------------------------------------------------------------------------
// FUNCTION: printPermisions 
// priema promenliva ot tip struct stat i i printira permishunite.
// Tazi funkciq e napravena specialno za poddrujkata na flaga -l
// PARAMETERS:
// st - podadena structora stat
//------------------------------------------------------------------------
void printPermisions(struct stat* st);
//------------------------------------------------------------------------
// FUNCTION: totalBloks 
// priema daden direktoriq otvarq q i sumita obshtiq broi blokove.
// Tazi funkciq e napravena specialno za poddrujkata na flaga -l
// PARAMETERS:
// path - podaden string
//------------------------------------------------------------------------
int totalBloks(char * path);

int flags[3];
int actualArguments = 1;
int MegaFirst = 1;
int main(int argc,  char **argv){

struct stat st;
DIR *dir;
for(int i=1;i<argc;i++){
    chekForFlags(argv[i]);
    if(argv[i][0] != '-'){
        actualArguments++;
    }
}

    if(actualArguments == 1){
        printDir(".");
    }else{
        int help = 0;
        for(int i = 1;i < argc;i++){
            if(chekForFlags(argv[i]) == 1){
                continue;
            }
            int t = stat(argv[i],&st);
            if(t!=0){
                char pr[1000] = "ls: cannot access ";
                strcat(pr,argv[i]);
                perror(pr);
                continue;
            }

            char mode = whatFile(&st);
            if(mode == 'd'){
                if(help == 1){
                    printf("\n");
                    help = 0; 
                }
                if(flags[2] == 1 ){
                    printf("%s:\n",argv[i]);
                    MegaFirst = 0;
                }
                if(actualArguments > 2 && MegaFirst == 1){
                    printf("%s:\n",argv[i]);
                }
                printDir(argv[i]);
                if(actualArguments > 2 && i+1!=actualArguments){
                    printf("\n");
                }
            }else{
                if(flags[1] == 1){
                    printMore(&st);
                    printf("%s\n",argv[i]);
                    help = 1;
                }else{
                    printf("%c %s\n",mode,argv[i]);
                    help = 1;
                }              
            }
        }
    }
}

int printDir(char* p){

    if(flags[2] == 1 && actualArguments == 1 && MegaFirst == 1){
        printf("%s:\n",p);
        MegaFirst = 0;
    }

    DIR *dir;  
    int first = 1;
    struct stat st;
    struct dirent *entry;
    int total = totalBloks(p);
    char **arrOfDirectoryes = NULL;
    int sizeOfarrOfDirectoryes = 0;
    dir = opendir(p);

    if(dir == NULL){
        char pr[1000] = "ls: cannot open directory ";
        strcat(pr,p);
        perror(pr);
        return 1;
    }
    
    while(1){
        entry = readdir( dir );
        if(entry != NULL){
            char filename[1000];
            strcpy(filename,p);
            strcat(filename,"/");
            strcat(filename,entry->d_name);
            int chek = stat(filename,&st);
            if(chek != 0){
                perror("zdr");
            }
            char type = whatFile(&st);
            if(flags[2] == 1 && type == 'd' && strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                if(flags[0] == 1 && entry->d_name[0] == '.'){
                    sizeOfarrOfDirectoryes++;
                    arrOfDirectoryes = realloc(arrOfDirectoryes,(sizeOfarrOfDirectoryes)*sizeof(char*));
                    arrOfDirectoryes[sizeOfarrOfDirectoryes-1] = strdup(filename);
                }else if(entry->d_name[0] != '.'){
                     sizeOfarrOfDirectoryes++;
                    arrOfDirectoryes = realloc(arrOfDirectoryes,(sizeOfarrOfDirectoryes)*sizeof(char*));
                    arrOfDirectoryes[sizeOfarrOfDirectoryes-1] = strdup(filename);
                }       
            }
            if(first == 1 && flags[1] == 1){
                printf("total %d\n",(total/2));
                first = 0;
            }
            if(entry->d_name[0] != '.'){
                if(flags[1] == 1){
                    printMore(&st);
                    printf("%s\n",entry->d_name);
                }else{
                    printf("%c %s\n",type,entry->d_name);
                }                  
            }else if(flags[0] == 1){
                if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                    if(flags[1] == 1){
                        printMore(&st);
                        printf("%s\n",entry->d_name);
                    }else{
                        printf("%c %s\n",type,entry->d_name);
                    }  
                }
            }
        }else if( entry == NULL && errno != 0){
            perror("readdir");
        }if(entry == NULL){
            break;
        }
    }

    int rc = closedir(dir);
    if(rc != 0){
        perror("closedir");
        return 1;
    }

    if(flags[2] == 1){
        for(int i=0 ;i<sizeOfarrOfDirectoryes;i++){
            printf("\n%s:\n",arrOfDirectoryes[i] );
            printDir(arrOfDirectoryes[i]);
        }
    }

    for(int i=sizeOfarrOfDirectoryes-1 ;i>=0;i--){
        free(arrOfDirectoryes[i]);
    }
    free(arrOfDirectoryes);

    return 0;
}

int chekForFlags(char* argv){
    if(argv[0] == '-'){
        for(int i = 0;i<strlen(argv);i++){
            if(argv[i] == 'A'){
                flags[0] = 1;
            }
            if(argv[i] == 'l'){
                flags[1] = 1;
            }
            if(argv[i] == 'R'){
                flags[2] = 1;
            }
        }
        return 1;
    }
    return 0;
}


void printPermisions(struct stat* st){
    if((S_ISDIR(st->st_mode))) printf("d"); else printf("-");
    if((st->st_mode & S_IRUSR)) printf("r"); else printf("-");
    if((st->st_mode & S_IWUSR)) printf("w"); else printf("-");
    if((st->st_mode & S_IXUSR)) printf("x"); else printf("-");
    if((st->st_mode & S_IRGRP)) printf("r"); else printf("-");
    if((st->st_mode & S_IWGRP)) printf("w"); else printf("-");
    if((st->st_mode & S_IXGRP)) printf("x"); else printf("-");
    if((st->st_mode & S_IROTH)) printf("r"); else printf("-");
    if((st->st_mode & S_IWOTH)) printf("w"); else printf("-");
    if((st->st_mode & S_IXOTH)) printf("x"); else printf("-");
    printf(" ");
}

char whatFile(struct stat *st){
    if(S_ISDIR(st->st_mode)){
        return 'd';
    }else if(S_ISREG(st->st_mode)){
        return '-';
    }else if(S_ISLNK(st->st_mode)){
        return 'l';
    }else if(S_ISBLK(st->st_mode)){
        return 'b';
    }else if(S_ISFIFO(st->st_mode)){
        return 'p';
    }else if(S_ISSOCK(st->st_mode)){
        return 's';
    }else if(S_ISCHR(st->st_mode)){
        return 'c';
    }
    return 'f';
}

void printMore(struct stat* st){
    printPermisions(st);
    printf("%lu ",st->st_nlink);
    printf("%s ",getpwuid(st->st_uid)->pw_name);
    printf("%s ",getgrgid(st->st_gid)->gr_name);
    printf("%lu ",st->st_size);
    char buff[20]; 
    struct tm * Tinfo;
    Tinfo = localtime (&(st->st_mtime)); 
    strftime(buff, 20, "%b %d %H:%M", Tinfo); 
    printf("%s ",buff);
}

int totalBloks(char* directory){
    int size = 0;
    struct stat st;
    struct dirent *entry;
    DIR* dir = opendir(directory);
    if(dir == NULL){
        char pr[1000] = "ls: cannot open directory ";
        strcat(pr,directory);
        perror(pr);
        return 1;
    }
    while(1){
        entry = readdir( dir );
        if(entry != NULL){
            char filename[1000];
            strcpy(filename,directory);
            strcat(filename,"/");
            strcat(filename,entry->d_name);
            stat(filename,&st);
            if(entry->d_name[0] != '.'){
                size += st.st_blocks;
            }else if(flags[0] == 1){
                if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                    size += st.st_blocks;
                }
            }
        }else if( entry == NULL && errno != 0){
            perror("readdir");
        }if(entry == NULL){
            break;
        }
    }

    int rc = closedir(dir);
    if(rc != 0){
        perror("closedir");
        return 1;
    }
    return size;
}