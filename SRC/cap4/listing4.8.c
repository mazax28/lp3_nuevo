#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Asignar un búfer temporal. */
void* allocate_buffer(size_t size)
{
    return malloc(size);
}

/* Desasignar un búfer temporal. */
void deallocate_buffer(void* buffer)
{
    free(buffer);
}

void* do_some_work(void* arg)
{
    /* Asignar un búfer temporal. */
    void* temp_buffer = allocate_buffer(1024);

    /* Registrar un controlador de limpieza para este búfer, para desasignarlo en
       caso de que el hilo salga o sea cancelado. */
    pthread_cleanup_push(deallocate_buffer, temp_buffer);

    /* Realizar algún trabajo aquí que podría llamar a pthread_exit o podría ser
       cancelado... */
    for (int i = 0; i < 5; i++) {
        printf("Hilo trabajando: %d\n", i);
        /* Simular algún trabajo */
        sleep(2);

        /* Comprobar la cancelación de vez en cuando */
        pthread_testcancel();
    }

    /* Desregistrar el controlador de limpieza. Debido a que pasamos un valor distinto de cero,
       esto realiza realmente la limpieza llamando a deallocate_buffer. */
    pthread_cleanup_pop(1);

    return NULL;
}

int main()
{
    pthread_t thread;

    /* Crear un hilo para realizar algún trabajo. */
    if (pthread_create(&thread, NULL, (void* (*)(void*))do_some_work, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    /* Esperar a que el hilo termine. */
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("Principal: El hilo ha terminado o ha sido cancelado.\n");

    return 0;
}
