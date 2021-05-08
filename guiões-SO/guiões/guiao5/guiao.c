#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

//exerc1

int pai2filho(){
    int p[2];
    char line[] = "linha1";
    char buffer[20];
    int res;
    int status;

    if(pipe(p) == -1){
        perror("pipe");
        return -1;
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        return -1;

    case 0:
        close(p[1]);
        res = read(p[0],buffer,sizeof(buffer));
        printf("Filho leu\n");
        close(p[0]);
        return res;

    
    default:
        close(p[0]);
        res = write(p[0], buffer,sizeof(buffer));
        printf("Pai escreveu \n");
        close(p[1]);
        
        return res;
    }


}


int filho2pai(){
  int p[2];
    char line[] = "linha1";
    char buffer[20];
    int res;
    int status;

    if(pipe(p) == -1){
        perror("pipe");
        return -1;
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        return -1;

    case 0:
         close(p[0]);
        res = write(p[1], line,sizeof(line));
        printf("Pai escreveu \n");
        close(p[1]);

    
    default:
        close(p[1]);
        res = read(p[0],buffer,sizeof(buffer));
        printf("Filho leu\n");
        close(p[0]);
        return res;
    }


}
   
// exerc 2

int untilEOF(){
    
    int p[2];
    char lines[5][20] = {"linha1\n","linha2\n","linha3\n","linha4\n"};
    char buffer[20];
    int res;
    int status;
    int i = 0;

    if(pipe(p) == -1){
        perror("pipe");
        return -1;
    }

    switch (fork())
    {
    case -1:
        perror("fork");
        return -1;

    case 0:
        close(p[1]);
        while((res = read(p[0],buffer,sizeof(buffer))) > 0);
        printf("Filho leu\n");
        printf("[FILHO] : leu -> %s",buffer);
        close(p[0]);

    
    default:
        close(p[0]);
        while(write(p[1], lines[i],sizeof(lines[i]))) i++;
        printf("Pai escreveu \n");
        close(p[1]);

    }


}


//exerc3
int exerc3(){
    int p[2];
    pid_t pid;
    pipe(p);
    char * buffer = malloc(sizeof(char)*100);
    char * s = malloc(sizeof(char)*100);
    if((pid = fork()) == 0){
        close(p[1]);
        dup2(p[0],0);
        read(0,s,100);
        write(1,s,100);
        

    }else{
    close(p[0]);
    read(0,buffer,100);
    dup2(p[1],1);
    write(1,buffer,100);
    }
}

//exerc4

int exerc4(){

    int p[2];
    pid_t pid;
    pipe(p);
    if((pid = fork()) == 0){
        dup2(p[1],1);
        close(p[0]);
        execlp("ls", "ls", "/etc", NULL);
    
    }else{
        wait(NULL);
    }

    close(p[1]);

    if((pid = fork()) == 0){
    
        dup2(p[0],0);
        close(p[1]);
        execlp("wc", "wc", "-l", NULL);
    }else{
        wait(NULL);
    }

    close(p[0]);

}

//exerc5

//Escreva um programa que emule o funcionamento do interpretador de comandos na execução encadeada
//de grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l.

int countWords(char * str){

    int words = 0;
    for(int i = 0; str[i] != '\0'; i++){

        if(str[i] == ' ') words++;


    }

return words + 1;
}


char ** toWords (char * s){

    char * str = strdup(s);
    int i = 0;
    int nWords = countWords(str);
   
    char ** words = malloc(sizeof(char *) * nWords);
    
    words[0] = strdup(strtok(str," "));

    
    for(i = 1; i < nWords; i++){
        words[i] = strdup(strtok(NULL," "));
    }

   
    return words;

}

int exerc5(){
     
    int nComandos = 2;
    int p[2][2];
    pid_t pid;
    
            pipe(p[0]);
            
            if((pid = fork()) == 0){
                
                dup2(p[0][1], 1);
                close(p[0][0]);
                close(p[0][1]);
                execlp("grep","grep","-v","ˆ#", "/etc/passwd",NULL);
                exit(0);
            }else{

                wait(NULL);
            }
            
            close(p[0][1]);
            
            pipe(p[1]);
            
            if((pid = fork()) == 0){
                
                dup2(p[0][0],0);
                dup2(p[1][1],1);
                close(p[0][0]);
                close(p[1][1]);
                execlp("cut","cut","-f7","-d:",NULL);
                exit(0);
             }else{

                wait(NULL);
            }

            close(p[0][0]);
            close(p[1][1]);
        
            pipe(p[0]);

            if((pid = fork()) == 0){

                dup2(p[1][0],0);
                close(p[1][0]);
                dup2(p[0][1],1);
                close(p[0][1]);
                close(p[0][0]);
                execlp("uniq","uniq",NULL);
                exit(0);
                
             }else{

                wait(NULL);
            }

            close(p[1][0]);
            close(p[0][1]);

            if((pid = fork()) == 0){

                dup2(p[0][0],0);
                close(p[0][0]);
                execlp("wc","wc", "-l",NULL);
                exit(0);
                
             }else{

                wait(NULL);
            }

            close(p[0][0]);

        
        


     return 0;
}


   
    
   
         
    





int main(){
   
   exerc5();

}