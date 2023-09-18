#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Allocate a temporary buffer. */
void* allocate_buffer(size_t size)
{
    return malloc(size);
}

/* Deallocate a temporary buffer. */
void deallocate_buffer(void* buffer)
{
    free(buffer);
}

void* do_some_work(void* arg)
{
    /* Allocate a temporary buffer. */
    void* temp_buffer = allocate_buffer(1024);

    /* Register a cleanup handler for this buffer, to deallocate it in
       case the thread exits or is cancelled. */
    pthread_cleanup_push(deallocate_buffer, temp_buffer);

    /* Do some work here that might call pthread_exit or might be
       cancelled... */
    for (int i = 0; i < 5; i++) {
        printf("Thread working: %d\n", i);
        /* Simulate some work */
        sleep(2);

        /* Check for cancellation every so often */
        pthread_testcancel();
    }

    /* Unregister the cleanup handler. Because we pass a nonzero value,
       this actually performs the cleanup by calling deallocate_buffer. */
    pthread_cleanup_pop(1);

    return NULL;
}

int main()
{
    pthread_t thread;

    /* Create a thread to do some work. */
    if (pthread_create(&thread, NULL, (void* (*)(void*))do_some_work, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    /* Wait for the thread to finish. */
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("Main: Thread has finished or has been canceled.\n");

    return 0;
    return 0;
}
