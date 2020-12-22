#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <ctype.h>

#include <sys/stat.h> 
#include <sys/types.h> 


// Caesar cipher
void cipher(char * str, int shift) {
    int i;
    while(*str) {
        if(isupper(*str)) {
            // shift for uppercase letters
            *str = (((*str + shift) - 'A') % 26) + 'A';
        } else if(islower(*str)) {
            // shift for lowercase letters
            *str = (((*str + shift) - 'a') % 26) + 'a';
        }
        str++;
    }
}

int main() {
    int buffer_size = 100; 
    int fd0, fd1;
    char buffer[buffer_size];

    mkfifo("luigi", 0644);

    // open read end of mario pipe
    fd0 = open("mario", O_RDONLY);

    // wait for mario to be created
    while(fd0 == -1) {
        fd0 = open("mario", O_RDONLY);
        sleep(1);
        continue;
    }

    // open write end of luigi pipe
    fd1 = open("luigi", O_WRONLY);

    unlink("luigi");

    while(1) {
        // get info from reader
        read(fd0, buffer, buffer_size - 1);

        // Process information
        cipher(buffer, 13);

        // send info to reader
        write(fd1, buffer, strlen(buffer) + 1);
    }
    
    return 0;
}