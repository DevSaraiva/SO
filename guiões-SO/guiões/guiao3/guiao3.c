#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


void execls(){

    int ret;
    char *exec_args[] = {"/bin/ls","-l","NULL"};
    
    ret = execl("/bin/ls","/bin/ls","-l",NULL);
    
    //ret = execlp("ls","ls","-l","NULL");
    
    //ret = execv("/bin/ls",exec_args);

    //ret = execvp("ls", exec_args);
}


void child_execls(){

    int stats;
    pid_t pid ;
    if((pid = fork()) == 0){

       int ret = execlp("ls","ls","-l",NULL);
        _exit(ret);
    }
    wait(&stats);
    printf("O filho retornou %d\n",WEXITSTATUS(stats));
    printf("Agora já executa a parte final do código\n");
}

void execls_args(char **argv){
    int stats;
    pid_t pid ;
    if((pid = fork()) == 0){

       int ret = execvp("ls",argv);
        _exit(ret);
    }
    wait(&stats);
    printf("O filho retornou %d\n",WEXITSTATUS(stats));
    
}

void execCommandList(char **comandos, int q){

    int i, stats;
    pid_t pid;
    for(i = 0; i < q; i++){
        
        if((pid = fork()) == 0){
            printf("Este é o filho\n");
            execlp(comandos[i],comandos[i],NULL);
            _exit(0);
        }
    }

    for(i = 0; i < 1; i++){
        wait(&stats);
    }

    printf("Todos os filhos executaram");

}

int mysystem(char *command){

    int i = 0, stats;
    pid_t pid;
    char* args[1024];
	char* token;
	char s[] = " ";
    int exec_ret;
    token = strtok(command,s);
	while((token != NULL)){
        args[i] = malloc(sizeof(char)*10);
        strcpy(args[i],token);
        i++;
        token = strtok(NULL,s);
    }
    args[i] = NULL;
    
    if((pid = fork()) == 0){
        execvp(args[0],args);
        _exit(exec_ret);
    }else{
        wait(&stats);
        return WEXITSTATUS(stats);
    }
}


int main(int argc, char** argv){
    
    int i;
    char command1[] = "ls -l -a -h";
    char command2[] = "sleep 10";
    if(argc < 2) printf("Insira o numero do exercicio");
    else{
        

        switch (atoi(argv[1])) {
        case 1:
            execls();
            break;
        case 2:
            child_execls();
            break;
        case 3:
            for(i = 0; i < argc; i++){
                write(1,argv[i],strlen(argv[i]));
            }
            write(1,"\n",1);
        case 4:
            argv[1] = "ls";           
            execls_args(argv+1);
            break;
        case 5:
            execCommandList(argv+2,argc-2);
            break;

        case 6:
                mysystem(command1);
                mysystem(command2);
            
            break;
        
        default:
            break;
    
    }   
    }
}