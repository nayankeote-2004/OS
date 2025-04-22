#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int choice;
    printf("1. Copy file (cp)\n");
    printf("2. Search text (grep)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Child PID: %d\n", getpid());

        if (choice == 1)
        {
            execlp("cp", "cp", "source.txt", "dest.txt", NULL);
        }
        else if (choice == 2)
        {

            execlp("grep", "grep", "--color=always", "am", "source.txt", NULL);
        }
        else
        {
            printf("Invalid choice\n");
            exit(1);
        }

        // If exec fails
        printf("exec failed\n");
        exit(1);
    }
    else
    {
        printf("Parent PID: %d\n", getpid());
        wait(NULL);
        printf("Child finished.\n");
    }

    return 0;
}
