#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int pipefd[2];

    // Create pipe
    if (pipe(pipefd) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }

    // Fork process
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0)
    {                     // Parent Process
        close(pipefd[0]); // Close read end

        // Redirect input.txt to stdin
        int in_fd = open("input.txt", O_RDONLY);
        if (in_fd < 0)
        {
            perror("Error opening input.txt");
            return 1;
        }

        dup2(in_fd, STDIN_FILENO);
        close(in_fd);

        // Redirect stdout to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Execute unique command
        execlp("sort", "sort", NULL);
        perror("Exec failed"); // If exec fails
        return 1;
    }
    else
    {                     // Child Process
        close(pipefd[1]); // Close write end

        // Redirect pipe input to stdin
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // Redirect stdout to output.txt
        int out_fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (out_fd < 0)
        {
            perror("Error opening output.txt");
            return 1;
        }
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);

        // Execute sort command
        execlp("uniq", "uniq", NULL);
        perror("Exec failed"); // If exec fails
        return 1;
    }

    return 0;
}
