#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        // fd[0] is for input
        // fd[1] is for input
        // both are now open: fd[0] for reading and fd[1] for writing
        // [PROCESS : write(fd[0])] -> KERNEL -> [PROCESS : read(fd[1])]
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        // after fork, fd[0] and fd[1] are also opened in child process
        // Here we chose to communicate from child to parent:
        // [CHILD: write(fd[0])] -> KERNEL -> [PARENT: read(fd[1])]
        // as we communicate from child to parent, fd[1] in CHILD and fd[0] in PARENT are no longer needed, and should be closed
        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}