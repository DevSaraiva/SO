#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


/*2. Escreva um programa “servidor”, que fique a correr em background, e acrescente a um ficheiro de “log”
todas as mensagens que sejam enviadas por “clientes”. Escreva um programa cliente que envia para o
servidor o seu argumento. Cliente e servidor devem comunicar via pipes com nome.*/


int main(){

    char buffer[1024];
    int bytesRead = 0;
    int fd = open("/tmp/fifo", O_WRONLY);

    while((bytesRead = read(STDIN_FILENO, buffer, 1024)) > 0) {
        write(fd, buffer, bytesRead);
    }
    close(fd);
    return 0;
}

