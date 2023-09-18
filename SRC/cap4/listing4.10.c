#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct job {
    /* Link field for linked list. */
    struct job* next;
    /* Description of the job. */
    char* description;
    /* Other fields describing work to be done... */
};

/* A linked list of pending jobs. */
struct job* job_queue = NULL; // Initialize job_queue to be empty

/* Mutex to protect the job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Process a job. This function should be implemented according to your requirements. */
void process_job(struct job* job)
{
    /* Implement the logic to process the job here. */
    printf("Processing job...\n");
    // Example: Print the job description
    printf("Job Description: %s\n", job->description);
    // You can add your specific processing logic here.
}

/* Thread function to process jobs. */
void* thread_function(void* arg)
{
    while (1) {
        struct job* next_job = NULL;

        /* Lock the mutex to access the job_queue safely. */
        pthread_mutex_lock(&job_queue_mutex);

        if (job_queue != NULL) {
            /* Get the next available job. */
            next_job = job_queue;
            /* Remove this job from the list. */
            job_queue = job_queue->next;
        }

        /* Unlock the mutex to allow other threads to access the queue. */
        pthread_mutex_unlock(&job_queue_mutex);

        if (next_job != NULL) {
            /* Carry out the work. */
            process_job(next_job);
            /* Clean up. */
            free(next_job->description); // Free the description
            free(next_job);
        } else {
            /* No jobs left in the queue, exit the thread. */
            break;
        }
    }

    return NULL;
}

int main()
{
    pthread_t threads[2]; // Create two threads for this example

    // Add 10 jobs to the job queue
    for (int i = 0; i < 10; i++) {
        struct job* new_job = (struct job*)malloc(sizeof(struct job));
        new_job->next = job_queue;
        job_queue = new_job;

        // Set job description (you can modify this as needed)
        char description[20];
        snprintf(description, sizeof(description), "Job %d", i + 1);
        new_job->description = strdup(description);
    }

    // Create threads to process jobs
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    // Cleanup and exit
    return 0;
}
