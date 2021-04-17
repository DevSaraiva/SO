#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>


int exerc1(){
    char buffer;
    char line[1024];
    int i = 0;
    int read_res = 0;
    setbuf(stdout, NULL); //desativa buffering evitando erros no printf


    int fsi = open("/etc/passwd",O_RDONLY,0444);
    int fso = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY,0666);
    int fse = open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY,0666);
    

    dup2(fsi,0);
    dup2(fso,1);
    dup2(fse,2);

   while ((read_res = read(0, &buffer, 1)) != 0){

		line[i] = buffer;

		i++;

		if(buffer == '\n') {

			write(1, line, i);

			write(2, line, i);

			printf("after write line\n");

			i = 0;

		}

	}
   
    return 0;
}


int exerc2(){
    
    setbuf(stdout, NULL); //desativa buffering evitando erros no printf
    char buffer;
    char line[1024];
    int i = 0;
    int read_res = 0;
    pid_t pid;


    int fsi = open("/etc/passwd",O_RDONLY,0444);
    int fso = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY,0666);
    int fse = open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY,0666);
    

    dup2(fsi,0);
    dup2(fso,1);
    dup2(fse,2);

    close(fsi);
    close(fso);
    close(fse);

   if((pid = fork()) == 0){

       
       while ((read_res = read(0, &buffer, 1)) != 0){

		line[i] = buffer;

		i++;

		if(buffer == '\n') {

			write(1, line, i);

			write(2, line, i);

			printf("after write line\n");

			i = 0;
		}
	}
   
    _exit(0);

   } else{
       wait(NULL);
   }
   
   
   return 0;
    
}

int exerc3(){
    
    int fsi = open("/etc/passwd",O_RDONLY,0444);
    int fso = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY,0666);
    int fse = open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY,0666);

    dup2(fsi,0);
    dup2(fso,1);
    dup2(fse,2);

    close(fsi);
    close(fso);
    close(fse);

    system("wc");

}


int main(){

    exerc3();

    return 0;
}