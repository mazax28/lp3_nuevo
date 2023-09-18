#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Parámetros para la función char_print. */
struct char_print_parms
{
    /* El carácter a imprimir. */
    char caracter;
    /* La cantidad de veces que se imprimirá. */
    int contador;
};

/* Imprime una cantidad de caracteres en stderr, según lo indicado por PARÁMETROS,
que es un puntero a una estructura struct char_print_parms. */
void* char_print(void* parametros)
{
    /* Convierte el puntero de datos a su tipo correcto. */
    struct char_print_parms* p = (struct char_print_parms*)parametros;
    int i;
    for (i = 0; i < p->contador; ++i)
        fputc(p->caracter, stderr);
    return NULL;
}

/* El programa principal. */
int main()
{
    pthread_t thread1_id;
    pthread_t thread2_id;
    struct char_print_parms* thread1_args = malloc(sizeof(struct char_print_parms));
    struct char_print_parms* thread2_args = malloc(sizeof(struct char_print_parms));

    /* Crea un nuevo hilo para imprimir 30,000 'x's. */
    thread1_args->caracter = 'x';
    thread1_args->contador = 30000;
    pthread_create(&thread1_id, NULL, &char_print, thread1_args);

    /* Crea un nuevo hilo para imprimir 20,000 'o's. */
    thread2_args->caracter = 'o';
    thread2_args->contador = 20000;
    pthread_create(&thread2_id, NULL, &char_print, thread2_args);

    /* Espera a que ambos hilos terminen antes de continuar. */
    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);

    /* Libera la memoria asignada dinámicamente. */
    free(thread1_args);
    free(thread2_args);

    return 0;
}
