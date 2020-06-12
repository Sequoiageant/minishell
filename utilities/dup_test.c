#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    char *cmd[] = {"wc", NULL};
    char buf[1001];

    // wc, en l'absence d'argument, lit stdin
    // BUT: reproduire le comportement de wc < ressources.txt
    // pour cela on remplace le fd du fichier par STDIN

    int fdd = open("../ressources.txt", O_RDONLY);
    
    close(0);
    // The new fd will be the lowest, unused fd. We close fd=0 so that 0 is unused, and can be returned by dup 
    dup(fdd);
    close(fdd);
    if (execve("../executables/wc", cmd, NULL) == -1)
        printf("exec failed\n");
    printf("end\n");
}