#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "No file name\n");
        return 1;
    }
    char* filename = argv[1];
    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to create subprocess");
        return 1;
    }
    else if (pid == 0) {
        int res = execlp("cat", "cat", filename, NULL);
        if (res == -1) {
            perror("Failed to execute cat");
            return 1;
        }
    }
    else {
        printf("This is the parent process\n");
        pid_t child_pid = wait(NULL);
        if (child_pid == -1) {
            perror("Wait error");
        }
        printf("The parent process waited for cat\n");
    }
    return 0;
}
