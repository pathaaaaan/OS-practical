//  PROGRAM II: Print PIDs of parent and child

// PROGRAM I: Create a child using fork()

#include <stdio.h>
#include <unistd.h>
int main()
{
    int pid = getpid(); // create child

    if (pid < 0)
    {
        printf("fork failed\n");
    }
    else if (pid == 0)
    {
        printf("child\n");
        printf("child PID : %d\n", getpid());
        printf("parent PID : %d\n", getppid());

    }
    else
    {
        printf("parent\n");
        printf("parent PID : %d\n", getpid());
        printf("child PID : %d\n", getppid());
    }
    return 0;
}