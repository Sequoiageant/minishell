#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
char	*ft_strdup(const char *src);

// BUT: reproduire echo "test pipe" | wc
// STDOUT of echo must be piped to STDIN of wc
// 1. pipe to connect both commands, 
// 2. duplicate (dup) output fd in echo to stdout 
// 3. duplicate input fd in wc to stdin

int main(void)
{
        int     fd[2];
        pid_t   childpid;

        pipe(fd);
        // fd[0] is for input
        // fd[1] is for output
        // both are now open: fd[0] for reading and fd[1] for writing
        // [PROCESS : write(fd[1])] -> KERNEL -> [PROCESS : read(fd[0])]
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }
        // prepare execve of echo
        char **argv;
        argv = malloc(3 * sizeof(char*));
        argv[0] = ft_strdup("ms_echo");
        argv[1] = ft_strdup("test dup");
        argv[2] = NULL;

        // after fork, fd[0] and fd[1] are also opened in child process
        // Here we chose to communicate from child to parent:
        // [CHILD: write(fd[1])] -> KERNEL -> [PARENT: read(fd[0])]
        // as we communicate from child to parent, fd[0] in CHILD and fd[1] in PARENT are no longer needed, and should be closed
        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                // STDOUT is now the output fd of the pipe. We dont need fd[1] anymore
                close(fd[1]);
                execve("../executables/ms_echo", argv, NULL);
        }
        else
        {
                // prepare execve of wc
                argv = malloc(2 * sizeof(char*));
                argv[0] = ft_strdup("wc");
                argv[1] = NULL;
        
                /* Parent process closes up output side of pipe */
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                execve("../executables/wc", argv, NULL);
        }
        
        return(0);
}