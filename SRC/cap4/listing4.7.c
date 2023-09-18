#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* La clave utilizada para asociar un puntero de archivo de registro con cada hilo. */
static pthread_key_t thread_log_key;

/* Escribe MENSAJE en el archivo de registro del hilo actual. */
void write_to_thread_log(const char *message)
{
    FILE *thread_log = (FILE *)pthread_getspecific(thread_log_key);
    fprintf(thread_log, "%s\n", message);
}

/* Cierra el puntero de archivo de registro THREAD_LOG. */
void close_thread_log(void *thread_log)
{
    fclose((FILE *)thread_log);
}

void *thread_function(void *args)
{
    char thread_log_filename[20];
    FILE *thread_log;

    /* Genera el nombre de archivo para el archivo de registro de este hilo. */
    sprintf(thread_log_filename, "hilo%d.log", (int)pthread_self());

    /* Abre el archivo de registro. */
    thread_log = fopen(thread_log_filename, "w");

    /* Almacena el puntero de archivo en datos específicos del hilo bajo thread_log_key. */
    pthread_setspecific(thread_log_key, thread_log);

    write_to_thread_log("Hilo iniciando.");

    /* Realizar trabajo aquí... */
    for (int i = 1; i <= 5; i++) {
        char log_message[50];
        sprintf(log_message, "El hilo está realizando trabajo, iteración %d", i);
        write_to_thread_log(log_message);
        usleep(500000); // Dormir durante 0.5 segundos para simular trabajo
    }

    write_to_thread_log("Hilo finalizado.");

    return NULL;
}

int main()
{
    int i;
    pthread_t threads[5];

    /* Crea una clave para asociar punteros de archivo de registro de hilo en
       datos específicos del hilo. Utiliza close_thread_log para limpiar los punteros de archivo. */
    pthread_key_create(&thread_log_key, close_thread_log);

    /* Crea hilos para realizar el trabajo. */
    for (i = 0; i < 5; ++i)
        pthread_create(&(threads[i]), NULL, thread_function, NULL);

    /* Espera a que todos los hilos terminen. */
    for (i = 0; i < 5; ++i)
        pthread_join(threads[i], NULL);

    return 0;
}
