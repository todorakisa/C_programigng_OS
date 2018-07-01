//------------------------------------------------------------------------
// NAME: Тодор Димитров
// CLASS: XIб
// NUMBER: 27
// PROBLEM: #1
// FILE NAME: myTail.c (unix file name)
// FILE PURPOSE:
// Пограмата трябва да се реализира стандартната UNIX команда tail.
// Командата tail се използва за показване(на стандартния изход) на
// последните 10 реда на файлове подадени като аргументи.
// Ако са подадени повече от един файлове преди всяко изписване на
// 10-те реда се изобразява заглавен ред със съответното име.
// Функцията трябва да може да чете от стандартния вход при 
// подаване на аргумент "-".
//------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdarg.h>

//------------------------------------------------------------------------
// FUNCTION: my_Tail
// Функцията чете един параметър(име на файл), отваря файла за четене,
// след което чете и принтира на стандартния изход само последните
// 10 реда от файла, а ако те са по малко от 10 изписва всичките.
// PARAMETERS:
// char* file_name -> името на файла който трябва да се прочете.
//------------------------------------------------------------------------

int my_Tail(char* file_name);

//------------------------------------------------------------------------
// FUNCTION: check_for_small_file_and_print_it
// Проверява дали даден файл е по-малък от 10 реда и ако е така извиква
// функцията print_small_file която принтира всичките му редове 
// и връща нула. check_for_small_file_and_print_it попринцип се извиква в
// my_Tail и ако върне 0, my_Tail свършва.
// PARAMETERS:
// char* file_name -> името на файла който искаме да проверим
// int file_descriptor -> файл дескриптора на файла който искаме да проверим
//------------------------------------------------------------------------

int check_for_small_file_and_print_it(char* file_name,int file_descriptor);

//------------------------------------------------------------------------
// FUNCTION: print_small_file
// Тази функция попринцип се извиква от check_for_small_file_and_print_it
// и принтира всичките редове във файла.
// PARAMETERS:
// char* file_name -> името на файла който искаме да принтираме
// int file_descriptor -> файл дескриптора на файла който искаме да принтираме
//------------------------------------------------------------------------

int print_small_file(char* file_name,int file_descriptor);

//------------------------------------------------------------------------
// FUNCTION: print_from_stdin
// функцията чете редове от стандартния вход и пише на стандартния 
// изход последните 10 реда, ако са по-малко от 10 изписва всичките.
// PARAMETERS:
// Няма параметри защото не и трябват тя направо изписва 
// заглавие ако са подадени повече от един аргумент на програмата 
// и започва да чете от стандартния вход.
//------------------------------------------------------------------------

int print_from_stdin();

//------------------------------------------------------------------------
// FUNCTION: check_for_errors
// Опитва се да отвори файл след това се опитва да прочете един елемент
// от него и накрая се опитва да затвори файла. Ако неуспее с някоя от 
// стъпките връща съответно 1 , 2 или 3. Тази функция обикновенно работи
// заедно с функцията print_error(int) която приема номера на 
// грешката и я принтира.
// PARAMETERS:
// char* file_name -> името на файла който искаме да тестваме.
//------------------------------------------------------------------------

int check_for_errors(char* file_name);

//------------------------------------------------------------------------
// FUNCTION: print_error
// Приема номера на грешката(1,2 или 3) която искаме да принтираме
// (получаваме този номер попринцип от функцията check_for_errors)
// приема и файла за който е грешката и след това я принтира.
// PARAMETERS:
// int error -> номера на грешката която искаме да изпринтираме.
// char* file_name -> файла за който трябва да изпринтираме грешката
//------------------------------------------------------------------------

void print_error(int error, char* file_name);	

int main(int argc ,char **argv){

	char str1[4] = {"==> "};
        char str2[5] = {" <==\n"};
	int err = 0;
	int last_err = 0,next_err = 0;

	if(argc==1){
		print_from_stdin();
	}
	
	for(int i = 1;i < argc;i++){
		if(argv[i][0]=='-' && strlen(argv[i]) == 1){
			if(argc >2){
				write(STDOUT_FILENO, str1, 4);
                write(STDOUT_FILENO, "standard input", 14);
                write(STDOUT_FILENO, str2, 5);
			}
			print_from_stdin();
			if(i!=argc-1){
			write(STDOUT_FILENO, "\n", 1);
			}
			continue;
		}
		if(argc>2){
			if(i+1!=argc){
			next_err = check_for_errors(argv[i+1]);
			}	

			err = check_for_errors(argv[i]);
			last_err = err;
			if(err == 0 || err!= 1){
					write(STDOUT_FILENO, str1, 4);
		        	write(STDOUT_FILENO, argv[i], strlen(argv[i]));
					write(STDOUT_FILENO, str2, 5);
			}
			if(err!=0){
				print_error(err,argv[i]);
			}else{
				my_Tail(argv[i]);
			}
			if(i!=argc-1 && next_err !=1 && next_err!=3){
				if((i==1 && next_err==0 && last_err==1) || (i==1 && next_err==0 && last_err==3)){}else{
				write(STDOUT_FILENO, "\n", 1);
				}
			}
		}else{
			err = check_for_errors(argv[i]);
			if(err!=0){
                                print_error(err,argv[i]);
                        }else{
                                my_Tail(argv[i]);
                        }
		}
	}
	return 0;
}

int my_Tail(char* p){
	
	int fd = open(p,O_RDONLY);

	int n = check_for_small_file_and_print_it(p,fd);
	if(n == 0){
	return 0;
	}else if(n == 1){
		close(fd);
	return 0;
	}

	short read_bytes,linecount = 0;
	short err_check,err_check_2;
	char buffer[1];
	
	if(fd < 0){
		perror( "ERR: open_" );
		return 1;
	}
	
	off_t size = lseek(fd,-1,SEEK_END);
	if(size < 0){
		perror( "ERR: lseek_" );
		return 5;
	}

	while(1){
		read_bytes = read(fd, buffer, 1);
		if(read_bytes == 0){break;}
		
		if(linecount == 11){read_bytes = read(fd, buffer, 1);break;}
		else if(buffer[0]=='\n'){
		linecount++;
		}
		lseek(fd,-2,SEEK_CUR);
	}

	while(1){
                read_bytes = read(fd, buffer, 1);
                if(read_bytes == 0){break;}
                if(read_bytes < 0){
                        perror( "ERR: read_" );
                        return 2;
                }
		err_check = write(STDOUT_FILENO, buffer, 1);
		if(err_check==0){
			do{
			err_check = write(STDOUT_FILENO, buffer, 1);
			}while(err_check==0);
		}
		if( err_check < 0){
				perror( "tail: error writing" );
				return 3;	
		}
	}

	close(fd);

return 0;
}

int check_for_small_file_and_print_it(char *p,int fd){

        short read_bytes,linecount = 0;
        char buffer[1];
        
        off_t size = lseek(fd,0,SEEK_SET);
	
        while(1){

                read_bytes = read(fd, buffer, 1);

                if(read_bytes == 0 && linecount <= 10){
			int z = print_small_file(p,fd);
			if(z==1){return 1;}
                        return 0;
                }
		
                if(linecount == 10){
			return 2;
		}
                if(buffer[0]=='\n'){
                        linecount++;
                }
        }            
}

int print_small_file(char *p,int fd){

        short read_byte,check_error=0;
        char buffer[1];
	lseek(fd,0,SEEK_SET);
        while(1){

                read_byte = read(fd, buffer, 1);

                if(read_byte == 0){
			break;
		}

		check_error = write(STDOUT_FILENO, buffer, 1);
                if(check_error < 0){
               		perror("tail: error writing");
                        return 1;
                }                
        }
	close(fd);
return 0;
}

int print_from_stdin(){
	char c[1];
	int size=20;
	char *b = malloc(size*sizeof(char));
	int i,count=0,g,right_position=0,j=0,check_error;
	for(i=0;read(STDIN_FILENO,c,1)!=0;i++){
		if(i==size){
			b=realloc(b,size+20);
			size+=20;
		}
		if(c[0]=='\n'){
			count++;
		}
		b[i]=c[0];
	}
	if(count<=10){
		for(int p=0;p<=i;p++){
			c[0]=b[p];
			check_error = write(STDOUT_FILENO, c, 1);
			if(check_error < 0){
                		perror("tail: error writing 'standart output'");
				return 1;
			}
		}
		return 0;
	}else{
		right_position = count-10;
		for(g=0;j!=right_position;g++){
		if(b[g]=='\n'){j++;}
		}
		for(;g<i;g++){
			c[0]=b[g];
			check_error = write(STDOUT_FILENO, c, 1);
                        if(check_error < 0){
                                perror("tail: error writing 'standart output'");
                                return 1;
                        }
        	}
	}
	free(b);
	return 0;
}

int check_for_errors(char *p){
	if(p[0]=='-' && strlen(p)==1){
		return 0;
	}
	char buffer[1];
	int fd = open(p,O_RDONLY);
        if(fd < 0){
                return 1;
        }
	
	int read_bytes = read(fd, buffer, 1);
        if(read_bytes < 0){
                return 2;
        }
	
        if(close(fd) < 0){
                return 3;
        }
	return 0;
}

void print_error(int i, char* p){
	char buffer[1];
	if(i == 1){
                char pr[1000];
                char pr1[100] = "tail: cannot open '";
                char pr2[100] = "' for reading";
                int i=0;
                for(i=0;i<strlen(pr1);){
                        pr[i]=pr1[i];
                        i++;
                }
                for(int v=0;v<strlen(p);v++){
                        pr[i]=p[v];
                        i++;
                }
                for(int v=0;v<strlen(pr2)+1;i++,v++){
                        pr[i]=pr2[v];
                }
                perror(pr);
	}
	if(i == 2){
		char pr[1000];
                char pr1[100] = "tail: error reading '";
                char pr2[100] = "'";
                int i=0;
                for(i=0;i<strlen(pr1);){
                        pr[i]=pr1[i];
                        i++;
                }
                for(int v=0;v<strlen(p);){
                        pr[i]=p[v];
                        v++;
                        i++;
                }
                for(int v=0;v<strlen(pr2)+1;i++,v++){
                        pr[i]=pr2[v];
                }
                perror(pr);
	}if(i == 3){
		char pr[1000];
                char pr1[100] = "tail: error reading '";
                char pr2[100] = "'";
                int i=0;
                for(i=0;i<strlen(pr1);){
                        pr[i]=pr1[i];
                        i++;
                }
                for(int v=0;v<strlen(p);){
                        pr[i]=p[v];
                        v++;
                        i++;
                }
                for(int v=0;v<strlen(pr2)+1;i++,v++){
                        pr[i]=pr2[v];
                }
                perror(pr);
	}
}
