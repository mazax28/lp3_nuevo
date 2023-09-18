#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> // Librería para usleep

void* thread_function(void* thread_arg)
{
    int i;
    for (i = 0; i < 5; i++) {
        printf("Hilo Desvinculado: Realizando un trabajo... (Iteración %d)\n", i);
        // Simular un trabajo
        usleep(1000000); // Dormir durante 1 segundo
    }
    printf("Hilo Desvinculado: Trabajo completo.\n");
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

    // Realizar un trabajo en el hilo principal
    int j;
    for (j = 0; j < 5; j++) {
        printf("Hilo Principal: Realizando un trabajo... (Iteración %d)\n", j);
        // Simular un trabajo
        usleep(500000); // Dormir durante 0.5 segundos
    }
    printf("Hilo Principal: Trabajo completo.\n");

    // El hilo principal no necesita unirse al hilo desvinculado,
    // ya que se ejecuta de forma independiente y se limpiará por sí mismo.

    return 0;
}
