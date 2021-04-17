#include <unistd.h>/* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h>/* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>


#define rows 10
#define cols 100

int exerc1(){
    
    pid_t pid;
    pid = getpid();
    printf("Id do processo: %d\n",pid);
    pid = getppid();
    printf("Id do processo pai: %d\n",pid);

    return 0;
}

int exerc2(){
    
    pid_t pid;
    
    if((pid = fork()) == 0){
        
        printf("Identificador do processo filho %d\n", getpid());

    }else{

         printf("Identificador do processo pai %d\n", getpid());
         printf("Identificador do processo do seu filho %d\n",pid);

    }
    
    return 0;
}

int exerc3(){
    
    int i,b;
    int pid;
    int status;
  
    for( i=0;i<10;i++ ){
        pid = fork();
        if(pid == 0){
                       
                printf("PID -> %d | Processo Filho em execução | Pai --> %d\n",getpid(), getppid());
                _exit(0);
        }
        else{
            wait(&status);
        }
    }
}

int exerc4(){

    int i, j, status;
    
    pid_t teste;
    for(i = 0; i < 10; i++){
        
        pid_t pid = fork();
        //if(i == 2) teste = getpid();
        if(pid == 0){

            
            printf("Filho --> Processo Pid %d\n", getpid());
            //if(getpid() == teste) {sleep(10);}          
            _exit(i);
        }
    }

    for(j = 0; j < 10; j++){
        pid_t terminated = wait(&status);
        printf(" O processo %d terminou\n", terminated);
    }

}

int exerc5(){
    
    int nivel = 1,stats;
    while(nivel <= 10){
        if(fork() == 0){
            
            printf("NIVEL %d -- PID: %d --PID do pai %d\n",nivel,getpid(), getppid());
        
        } else {
            
            wait(&stats);
            _exit(nivel);
        }
        nivel++;
    }
    
    return 0;
}

int exerc6_7(int x){

    int pids[rows];
    int rand_Max = 100, i, j;
    pid_t pid;
    int stats;

    srand((int)time(NULL));
    int matrix[rows][cols];
	puts("Random Matrix...");
	for(i = 0; i < rows; i++)
		for(size_t j = 0; j < cols; j++)
			matrix[i][j] = rand() % rand_Max;


    for(i = 0; i < rows; i++){
        if((pid = fork()) == 0){
            for(j = 0; j < cols; j++){
                
                if(matrix[i][j] == x) {
                    _exit(i);
                }
            }
            printf("Procura na linha %d terminada",i);
            _exit(-1);
        } else pids[i] = pid;
    }
    int founds = 0;
    for(i = 0; i < rows; i++){
        waitpid(pids[i],&stats, 0);
        int line = WEXITSTATUS(stats);
        if(line != 255) {
            founds++;
            printf("Valor encontrado na linha %d\n",i);
        }
    }

	printf("Foram encontradas %d vezes o número %d nas linhas \n:",founds,x);
    
    return 0;
    }
    

int adicional(int x){
    
    int rand_Max = 100, i, j;
    pid_t pid;
    int stats;

    //gera matriz aleatoria
    srand((int)time(NULL));
    int matrix[rows][cols];
	puts("Random Matrix...");
	for(i = 0; i < rows; i++)
		for(size_t j = 0; j < cols; j++)
			matrix[i][j] = rand() % rand_Max;

    //Abre o ficheiro

    int fd = open("matrix.txt",O_CREAT | O_TRUNC | O_RDWR, 0600);
    
    //Escreve a matriz no ficheiro
    
    int write_bytes;
    write_bytes = write(fd,matrix,sizeof(int)*cols*rows);
    printf("Write bytes %d\n",write_bytes);
    
    //Coloca o apontador do ficheiro no inicio
    lseek(fd,SEEK_SET,0);

    //Limpa a matriz
    for(i = 0; i < rows; i++)
		for(size_t j = 0; j < cols; j++)
			matrix[i][j] = 0;

    //Lê novamente a matriz
    
    int bytes = read(fd,matrix,sizeof(int)*cols*rows);
	printf("Read bytes %d\n",bytes);
    
    
    //Procura o inteiro selecionado  guardado no parametro x e cria os processos

    for(i = 0; i < rows; i++){
        if((pid = fork()) == 0){
            for(j = 0; j < cols; j++){
                
                if(matrix[i][j] == x) {
                    _exit(i);
                }
            }
            printf("Procura na linha %d terminada",i);
            _exit(-1);
        }
    }

    //Recolhe os resultados dos processos

    int line;
    for(i = 0; i < rows; i++){
        wait(&stats);
        line = WEXITSTATUS(stats);
        if(line != 255) printf("Número encontrado na linha %d \n",line); // 255 é o return -1
        
        }
    }


int main(){

     exerc6_7(14);
    

    return 0;
}