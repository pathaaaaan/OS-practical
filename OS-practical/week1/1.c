// PROGRAM I: Create a child using fork()

#include<stdio.h>
#include <unistd.h>
int main()
{
    int pid = getpid(); // create child

    if(pid < 0){
        printf("fork failed\n");
    }
    else if(pid == 0){
        printf("child\n");
    }
    else {
        printf("parent\n");
    }
    return 0;
}