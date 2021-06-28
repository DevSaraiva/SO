#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int ctrl_c_counter = 0;
int seconds = 0;

void ctrl_c_handler(int signum) {
    
    printf("Passaram %d segundos desde o começo do programa.\n", seconds);
    ctrl_c_counter++;
}

void ctrl_slash_handler(int signum){

    printf("Carregou %d",(ctrl_c_counter));
    exit(0);

}

void sigalarm_handler(int signum){

    seconds++;
    alarm(1);
    pause();

}


int main(int argc, char const *argv[]) {

    signal(SIGALRM, sigalarm_handler);

    signal(SIGINT,ctrl_c_handler);

    signal(SIGQUIT, ctrl_slash_handler);


        alarm(1);
        while(1);


    
    return 0;
}








