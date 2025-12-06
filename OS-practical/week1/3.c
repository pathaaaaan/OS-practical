// PROGRAM III: Child lists all files, parent waits
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int pid = fork();

    if(pid == 0){
        execl("/bin/ls", "ls", NULL);
        // exit(0);
    }
    else{
        wait(NULL);
        printf("Child Complete\n");
    }
    return 0;
}