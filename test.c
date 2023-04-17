#include "shell.h"

#define BUFFER_SIZE 1024

int main(void) {
    char *command;
    char buffer[BUFFER_SIZE];
    pid_t pid;
    int status;

    while (1) {
        printf("#cisfun$ ");
        fgets(buffer, BUFFER_SIZE, stdin);
        
        if (feof(stdin)) {
            printf("\n");
            break;
        }
        
        buffer[strcspn(buffer, "\n")] = '\0';

        pid = fork();

        if (pid == 0) {
                command = strtok(buffer, " ");

            if (execve(command, &command, NULL) == -1) {
                printf("./hsh: No such file or directory\n");
                exit(1);
            }
        }else {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
