#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct job {
    /* Link field for linked list. */
    struct job* next;
    /* Descripción del trabajo. */
    char* descripcion;
};

/* Una lista enlazada de trabajos pendientes. */
struct job* job_queue = NULL; // Inicializar cola_trabajos como vacía

/* Mutex para proteger la cola_trabajos. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Procesar un trabajo. Esta función debe implementarse según sus requisitos. */
void process_job(struct job* job)
{
    printf("Procesando trabajo...\n");
    printf("Descripcion de trabajo: %s\n", job->descripcion);
}

/* Función de hilo para procesar trabajos. */
void* thread_function(void* arg)
{
    while (1) {
        struct job* next_job = NULL;

        /* Bloquear el mutex para acceder a la cola_trabajos de manera segura. */
        pthread_mutex_lock(&job_queue_mutex);

        if (job_queue != NULL) {
            /* Obtener el próximo trabajo disponible. */
            next_job = job_queue;
            /* Eliminar este trabajo de la lista. */
            job_queue = job_queue->next;
        }

        /* Desbloquear el mutex para permitir que otros hilos accedan a la cola. */
        pthread_mutex_unlock(&job_queue_mutex);

        if (next_job != NULL) {
            /* Realizar el trabajo. */
            process_job(next_job);
            /* Limpiar. */
            free(next_job->descripcion); // Liberar la descripción
            free(next_job);
        } else {
            /* No quedan trabajos en la cola, salir del hilo. */
            break;
        }
    }

    return NULL;
}

int main()
{
    pthread_t threads[2]; // Crear dos hilos para este ejemplo

    // Agregar 10 trabajos a la cola de trabajos
    for (int i = 0; i < 10; i++) {
        struct job* new_job = (struct job*)malloc(sizeof(struct job));
        new_job->descripcion = (char*)malloc(20); // Reservar memoria para la descripcion
        snprintf(new_job->descripcion, 20, "Trabajo %d", i + 1);
        new_job->next = NULL;

        // Bloquea el mutex para acceder a job_queue de forma segura.
        pthread_mutex_lock(&job_queue_mutex);

        // Poner en cola el trabajo
        new_job->next = job_queue;
        job_queue = new_job;

        // Desbloquea el mutex para permitir que otros subprocesos accedan a la cola.
        pthread_mutex_unlock(&job_queue_mutex);
    }

    // Crear hilos para procesar trabajos
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < 2; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    // Cleanup and exit
    return 0;
}
