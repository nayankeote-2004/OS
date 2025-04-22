#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>

using namespace std;

sem_t x, y;
pthread_t readerThreads[100], writerThreads[100];
int readerCount = 0;

bool use_sync = true;

void *reader_sync(void *param)
{
    int id = *((int *)param);

    sem_wait(&x);
    readerCount++;
    if (readerCount == 1)
    {
        sem_wait(&y); // Block writer if a reader is inside
    }
    sem_post(&x);

    cout << "\nReader " << id << " has entered the critical section." << endl;
    usleep(1000); // Simulating reading

    sem_wait(&x);
    readerCount--;
    if (readerCount == 0)
    {
        sem_post(&y); // Allow writer when last reader leaves
    }
    sem_post(&x);

    cout << "\nReader " << id << " has left the critical section." << endl;

    return nullptr;
}

void *writer_sync(void *param)
{
    int id = *((int *)param);

    cout << "\nWriter " << id << " is trying to enter the critical section..." << endl;
    sem_wait(&y); // Wait for readers to finish
    cout << "\nWriter " << id << " has entered the critical section." << endl;
    usleep(1000); // Simulating writing
    sem_post(&y); // Release writer lock
    cout << "\nWriter " << id << " has left the critical section." << endl;

    return nullptr;
}

void *reader_nsync(void *param)
{
    int id = *((int *)param);

    cout << "\nReader " << id << " has entered the critical section." << endl;
    usleep(1000); // Simulating reading
    cout << "\nReader " << id << " has left the critical section." << endl;

    return nullptr;
}

void *writer_nsync(void *param)
{
    int id = *((int *)param);

    cout << "\nWriter " << id << " is trying to enter the critical section..." << endl;
    cout << "\nWriter " << id << " has entered the critical section." << endl;
    usleep(1000); // Simulating writing
    cout << "\nWriter " << id << " has left the critical section." << endl;

    return nullptr;
}

int main()
{
    int n2, i;
    int readerIDs[100], writerIDs[100];

    cout << "\nEnter the number of reader-writer pairs: ";
    cin >> n2;
    cout << "\nRunning " << (use_sync ? "synchronized" : "non-synchronized") << " version\n";

    // Initialize thread IDs
    for (i = 0; i < n2; i++)
    {
        readerIDs[i] = i + 1;
        writerIDs[i] = i + 1;
    }

    if (use_sync)
    {
        sem_init(&x, 0, 1);
        sem_init(&y, 0, 1);

        for (i = 0; i < n2; i++)
        {
            pthread_create(&readerThreads[i], NULL, reader_sync, &readerIDs[i]);
            pthread_create(&writerThreads[i], NULL, writer_sync, &writerIDs[i]);
        }

        for (i = 0; i < n2; i++)
        {
            pthread_join(readerThreads[i], NULL);
            pthread_join(writerThreads[i], NULL);
        }
    }
    else
    {
        for (i = 0; i < n2; i++)
        {
            pthread_create(&readerThreads[i], NULL, reader_nsync, &readerIDs[i]);
            pthread_create(&writerThreads[i], NULL, writer_nsync, &writerIDs[i]);
        }

        for (i = 0; i < n2; i++)
        {
            pthread_join(readerThreads[i], NULL);
            pthread_join(writerThreads[i], NULL);
        }
    }

    cout << "\nAll reader and writer threads have finished." << endl;

    return 0;
}
