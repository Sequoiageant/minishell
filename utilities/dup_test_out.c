#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    char *cmd[] = {"ls", NULL};

    // BUT: reproduire le comportement de ls > out.txt

    int fdd = open("out.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    printf("fd: %d\n", fdd);
    dup2(fdd, STDOUT_FILENO);
    close(fdd);
    if (execve("/bin/ls", cmd, NULL) == -1)
        printf("exec failed\n");
    printf("end\n");
}