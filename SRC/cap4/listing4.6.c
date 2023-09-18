#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_CUENTAS 10

float saldos_cuenta[NUM_CUENTAS];
pthread_mutex_t mutex_cuenta[NUM_CUENTAS];

/* Transfiere DÓLARES desde la cuenta DESDE_CUENTA a la cuenta A_CUENTA. Retorna
   0 si la transacción fue exitosa, o 1 si el saldo de DESDE_CUENTA es
   insuficiente. */
int procesar_transaccion(int desde_cuenta, int a_cuenta, float dolares) {
    if (saldos_cuenta[desde_cuenta] < dolares) {
        return 1; // Saldo insuficiente
    }

    // Bloquea ambas cuentas
    pthread_mutex_lock(&mutex_cuenta[desde_cuenta]);
    pthread_mutex_lock(&mutex_cuenta[a_cuenta]);

    // Transfiere el dinero
    saldos_cuenta[desde_cuenta] -= dolares;
    saldos_cuenta[a_cuenta] += dolares;

    // Desbloquea ambas cuentas
    pthread_mutex_unlock(&mutex_cuenta[a_cuenta]);
    pthread_mutex_unlock(&mutex_cuenta[desde_cuenta]);

    return 0; // Transacción exitosa
}

void* hilo_transaccion(void* arg) {
    int desde_cuenta, a_cuenta;
    float cantidad;

    while (1) {
        desde_cuenta = rand() % NUM_CUENTAS;
        a_cuenta = rand() % NUM_CUENTAS;
        cantidad = (float)(rand() % 1000) / 100.0; // Cantidad aleatoria entre 0 y 10

        printf("Hilo: Transferir %.2f desde la Cuenta %d a la Cuenta %d\n", cantidad, desde_cuenta, a_cuenta);

        if (procesar_transaccion(desde_cuenta, a_cuenta, cantidad) == 0) {
            printf("Hilo: Transacción exitosa.\n");
        } else {
            printf("Hilo: Transacción fallida debido a saldo insuficiente.\n");
        }

        usleep(100000); // Dormir durante 0.1 segundos
    }

    return NULL;
}

int main() {
    pthread_t hilos[NUM_CUENTAS];
    int i;

    // Inicializa los saldos de las cuentas con valores aleatorios
    for (i = 0; i < NUM_CUENTAS; i++) {
        saldos_cuenta[i] = (float)(rand() % 10000);
        pthread_mutex_init(&mutex_cuenta[i], NULL);
    }

    // Crea hilos para realizar transacciones
    for (i = 0; i < NUM_CUENTAS; i++) {
        pthread_create(&hilos[i], NULL, hilo_transaccion, NULL);
    }

    // Deja que los hilos se ejecuten durante un tiempo
    sleep(10);

    // Limpia y muestra los saldos finales de las cuentas
    for (i = 0; i < NUM_CUENTAS; i++) {
        pthread_mutex_destroy(&mutex_cuenta[i]);
        printf("Cuenta %d: %.2f\n", i, saldos_cuenta[i]);
    }

    return 0;
}
