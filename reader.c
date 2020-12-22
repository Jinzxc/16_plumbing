#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <unistd.h> 

#include <sys/stat.h> 
#include <sys/types.h> 

// function to get info from stdin
void readin(char * buffer, int len) {
    fgets(buffer, len, stdin);
    if(strchr(buffer, '\n'))
        *strchr(buffer, '\n') = 0;
}

int main() {
    int buffer_size = 100; 
    int fd0, fd1;
    char buffer[buffer_size];

    mkfifo("mario", 0644);

    // open write end of mario
    fd0 = open("mario", O_WRONLY);

    // open read end of luigi
    fd1 = open("luigi", O_RDONLY);

    unlink("mario");

    while(1) {
        // get info from stdin
        printf("Input a value to process: ");
        readin(buffer, buffer_size - 1);

        // write to processor
        write(fd0, buffer, strlen(buffer) + 1);

        // read from processor
        read(fd1, buffer, buffer_size - 1);

        // display processed info
        printf("Processed value: [%s]\n\n", buffer);
    }
    
    return 0;
}