
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct job {
  struct job *next;
  int job_id;
} job;

// imprimir el id del trabajo y despues dormir entre 2 y 4 segundos
void process_job(int id_hilo, int id_trabajo) {
  printf("HILO %d, trabajo %d\n", id_hilo, id_trabajo);
  int random_number = 6 + rand() % (6 - 5 + 1);
  sleep(random_number);
  return;
}

/* A linked list of pending jobs.  */
struct job *job_queue;
int global_counter = 0;
int job_counter = 0;

// To protect job_queue
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t job_queue_count; /* A semaphore counting the number of jobs. */

void initialize_job_queue() {
  job_queue = NULL;
  sem_init(&job_queue_count, 0, 0);
}

/* Process  queued  jobs  until  the  queue  is  empty.  */
void *thread_function(void *args) {
  int *id = (int *)(args);
  while (1) {
    struct job *next_job;

    // Wait on the job queue semaphore.
    sem_wait(&job_queue_count);

    /* Lock the mutex on the job queue.  */
    pthread_mutex_lock(&job_queue_mutex);
    /* Remove a job from the list.*/
    next_job = job_queue;
    job_queue = job_queue->next;
    job_counter--;
    pthread_mutex_unlock(&job_queue_mutex);

    /* Carry out the work and Clean up.*/
    process_job(*id, next_job->job_id);
    free(next_job);
  }
  return NULL;
}

// Fabrica que anade un nuevo trabajo a la lista de trabajos cada 1 segundo
void *enqueue_job(void *_) {
  while (1) {
    // un maximo de 99 trabajos y salir
    if (global_counter == 99) {
      return NULL;
    }
    struct job *new_job;
    /* Allocate a new job object.  */
    new_job = (struct job *)malloc(sizeof(struct job));
    new_job->job_id = ++global_counter;
    job_counter++;

    /* Lock the mutex and add a new job.  */
    pthread_mutex_lock(&job_queue_mutex);
    new_job->next = job_queue;
    job_queue = new_job;
    // Post to the semaphore to indicate that another job is available.
    sem_post(&job_queue_count);

    /* Unlock the job queue mutex.  */
    printf("New Job created. Available %d\n", job_counter);
    pthread_mutex_unlock(&job_queue_mutex);
    sleep(1);
  }
}

// listing 4.12: Semaphore
int main(int argc, char *argv[]) {
  printf("\nUna fabrica anade trabajos cada 1 segundo para demostrar el uso de semaforos.\n");
  sleep(2);
  // inicializar la cola
  initialize_job_queue();

  // crear la fabrica de trabajos
  pthread_t fabrica;
  pthread_create(&fabrica, NULL, &enqueue_job, NULL);

  // crear los hilos
  pthread_t hilos[4];
  int ids[10] = {1, 2, 3, 4};
  for (int i = 0; i < 4; i++)
    pthread_create(&hilos[i], NULL, &thread_function, &ids[i]);

  for (int i = 0; i < 4; i++)
    pthread_join(hilos[i], NULL);

  pthread_join(fabrica, NULL);

  return 0;
}