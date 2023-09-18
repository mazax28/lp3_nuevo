#include <pthread.h>
#include <iostream>
#include <unistd.h>

class ThreadExitException
{
public:
    /* Crea una excepción que señala la salida del hilo con VALOR_DE_RETORNO. */
    ThreadExitException(void* valor_de_retorno)
        : valor_de_retorno_del_hilo_(valor_de_retorno)
    {
    }

    /* Realmente sale del hilo usando el valor de retorno proporcionado en el constructor. */
    void* RealizarSalidaDelHilo()
    {
        pthread_exit(valor_de_retorno_del_hilo_);
    }

private:
    /* El valor de retorno que se usará al salir del hilo. */
    void* valor_de_retorno_del_hilo_;
};

bool deberia_salir_del_hilo_inmediatamente()
{
    // Simula una condición en la que el hilo debería salir inmediatamente.
    return false;
}

void realizar_algun_trabajo()
{
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++)
    {
        /* Realiza algún trabajo útil aquí, como procesar elementos del arreglo. */
        std::cout << "Hilo: Procesando elemento " << array[i] << std::endl;

        // Comprueba si el hilo debería salir
        if (deberia_salir_del_hilo_inmediatamente())
        {
            throw ThreadExitException(/* valor de retorno del hilo = */ NULL);
        }
    }
}

void* funcion_del_hilo(void*)
{
    try
    {
        realizar_algun_trabajo();
    }
    catch (ThreadExitException ex)
    {
        /* Alguna función indicó que deberíamos salir del hilo. */
        ex.RealizarSalidaDelHilo();
    }
    return NULL;
}

int main()
{
    pthread_t hilo;

    /* Crea un hilo para realizar algún trabajo. */
    if (pthread_create(&hilo, NULL, funcion_del_hilo, NULL) != 0)
    {
        perror("pthread_create");
        return 1;
    }

    /* Deja que el hilo se ejecute durante un tiempo. */
    sleep(2);

    /* Cancela el hilo. */
    if (pthread_cancel(hilo) != 0)
    {
        perror("pthread_cancel");
        return 1;
    }

    /* Espera a que el hilo termine. */
    if (pthread_join(hilo, NULL) != 0)
    {
        perror("pthread_join");
        return 1;
    }

    std::cout << "Principal: El hilo ha terminado o ha sido cancelado." << std::endl;

    return 0;
}
