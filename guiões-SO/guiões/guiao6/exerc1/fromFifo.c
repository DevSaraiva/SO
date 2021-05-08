#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*1 
Escreva três programas. O primeiro cria apenas um pipe com nome “fifo”. O segundo repete para este
pipe todas as linhas de texto lidas a partir do seu standard input. O terceiro programa deverá repetir
para o seu standard output todas as linhas de texto lidas a partir deste pipe. Repare que ao contrário dos
pipes anónimos, o pipe corresponde a uma entrada no sistema de ficheiros, sujeito ao mesmo controlo de
acesso dos ficheiros normais, e não obriga à criação do pipe por um processo ascendente dos processos
em comunicação. Aliás, a comunicação pode mesmo realizar-se entre processos de utilizadores distintos.
Note ainda. que tal como nos pipes anónimos, as operações de leitura e escrita no pipe oferecem um
canal unidireccional sob uma polı́tica FIFO e diluição da eventual fronteira das escritas. No entanto,
ao contrário dos pipes anónimos, a abertura para escrita de um pipe como nome bloqueia até que um
processo o abra para leitura, e vice-versa*/


int main(){

    char  buffer[1024];
    int fd = open("fifo",O_RDONLY);
    int bytes_read = 0;
    while((bytes_read = read(fd,buffer,1024)) > 0){

        write(0,buffer, bytes_read);
    }
    

    close(fd);

    return 0;
}

