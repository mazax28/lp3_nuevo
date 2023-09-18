#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> // Include this header for usleep

void* thread_function(void* thread_arg)
{
    int i;
    for (i = 0; i < 5; i++) {
        printf("Detached Thread: Doing some work... (Iteration %d)\n", i);
        // Simulate some work
        usleep(1000000); // Sleep for 1 second
    }
    printf("Detached Thread: Work complete.\n");
    return NULL;
}

int main()
{
    pthread_attr_t attr;
    pthread_t thread;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread, &attr, &thread_function, NULL);
    pthread_attr_destroy(&attr);

    // Do some work in the main thread
    int j;
    for (j = 0; j < 3; j++) {
        printf("Main Thread: Doing some work... (Iteration %d)\n", j);
        // Simulate some work
        usleep(500000); // Sleep for 0.5 seconds
    }
    printf("Main Thread: Work complete.\n");

    // The main thread does not need to join the detached thread,
    // as it runs independently and will clean up itself.

    return 0;
}
