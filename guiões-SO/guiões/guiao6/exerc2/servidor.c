#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    
    if(mkfifo("/tmp/fifo", 0666) == -1){
            perror("mkfifo");
    
    }

    int log = open("log.txt",O_RDWR|O_CREAT|O_APPEND, 0666);
    int fd = open("/tmp/fifo", O_RDONLY);
    int bytesRead = 0;
    char buffer[1024];
    while(1){

        while((bytesRead = read(fd, buffer, 1024)) > 0) {
            write(1, buffer, bytesRead);
            write(log, buffer, bytesRead);
        }

    }
   
    close(fd);
    return 0;
    
}