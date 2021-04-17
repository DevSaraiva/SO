#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

//program redir exerc4

int main(int argc, char ** argv){

    int input;
    int output;
    pid_t pid;
    char ** execArgs;
    int pos;
    setbuf(stdout, NULL); //desativa buffering evitando erros no printf

    if(strcmp(argv[1],"-i") == 0){
        input = open(argv[2],O_RDONLY);
        dup2(input,0);
        if(strcmp(argv[3], "-o") == 0) {
            output = open(argv[4],O_CREAT | O_TRUNC | O_WRONLY,0666);
            dup2(output,1);
            execArgs = argv + 5;
        }else  execArgs = argv + 3;
    }else{
        if(strcmp(argv[1],"-o") == 0) {
            output = open(argv[2],O_CREAT | O_TRUNC | O_WRONLY,0666);
            dup2(output,1);
            execArgs = argv + 3;
        }else return -1;
        
    }

    if((pid = fork()) == 0){
        
        execvp(execArgs[0], execArgs);
        _exit(0);
    
    }else{
    
        wait(NULL);
    
    }






}
