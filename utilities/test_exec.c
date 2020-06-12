#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status;
    // int ret;
    char *argv[] = {"echo", "brunet", NULL};
    char *argv1[] = {"ls", "-a", NULL};
    // first argument is supposed to be the name of the executable, but it doesn't matter if it's not
    char *envp[] = {"jim", NULL};
    // char *buf;
    // buf = malloc(101);

    // printf("Welcome, enter your name: \n");
    // ret = read(1, buf, 100);
    // buf[ret] = 0;
    pid_t new_pid = fork();
    if (new_pid == 0)
    {
        printf("new process\n");
        sleep(1);
        if (execve("ms_echo", argv, envp) == -1)
            printf("exec failed\n");
        printf("Can you see me ? \n");
    }
    else
    {
       wait(&status); 
       printf("old process\n");
    }
    printf("End\n");

    
    
}