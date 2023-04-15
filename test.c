#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char *command;
    char buffer[BUFFER_SIZE];
    pid_t pid;
    int status;

    while (1) {
        printf("$ ");
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
                printf("simple_shell: %s: command not found\n", command);
                exit(1);
            }
        } else if (pid < 0) {
            printf("simple_shell: fork failed\n");
            exit(1);
        } else {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
