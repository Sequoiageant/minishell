#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    pid_t child_pid;
    pid_t pid;
    int stat_loc;
    pid_t wait_result;
    
    printf("Hello\n");
    child_pid = fork();
    
    // //**normal
    // printf("-----Start\n");
    // pid = getpid();
    // printf("pid: %d\n", pid);
    // printf("child_pid: %d\n", child_pid);
    // sleep(1);

    // //**if else with waint
    // if (child_pid == 0)
    // {
    //     sleep(2);
    //     printf("Child process\n");
    //     pid = getpid();
    //     printf("pid: %d\n", pid);
    //     printf("child_pid: %d\n", child_pid);
    // }
    // else
    // {
    //     // sleep(2);
    //     printf("Parent process\n");
    //     pid = getpid();
    //     printf("pid: %d\n", pid);
    //     printf("child_pid: %d\n", child_pid);
    // }
    
    //**if else with wait
    if (child_pid == 0)
    {
        sleep(2);
        printf("Child process\n");
        pid = getpid();
        printf("pid: %d\n", pid);
        printf("child_pid: %d\n", child_pid);
    }
    else
    {
        wait_result = wait(&stat_loc);
        //wait_result = waitpid(child_pid, &stat_loc, WUNTRACED);
        printf("Parent process\n");
        pid = getpid();
        printf("pid: %d\n", pid);
        printf("child_pid: %d\n", child_pid);
    }

    printf("-----End\n");
}