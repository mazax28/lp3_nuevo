#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PRIMES 1000000 // Maximum number of prime numbers to compute

/* Define a mutex to protect access to shared data */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Global variable to store prime numbers */
int* primes = NULL;
int prime_count = 0;

/* Function to generate prime numbers using Sieve of Eratosthenes */
void* generate_primes(void* arg) {
    int limit = *((int*)arg);

    // Initialize an array to mark numbers as prime or not
    int is_prime[limit + 1];
    for (int i = 0; i <= limit; i++) {
        is_prime[i] = 1; // Initialize all numbers as prime
    }

    for (int p = 2; p * p <= limit; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = 0; // Mark multiples of p as non-prime
            }
        }
    }

    // Allocate memory for the prime numbers
    primes = (int*)malloc(sizeof(int) * (limit + 1));
    if (primes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Store the prime numbers in the shared array
    for (int p = 2; p <= limit; p++) {
        if (is_prime[p]) {
            pthread_mutex_lock(&mutex);
            primes[prime_count++] = p;
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}

int main() {
    pthread_t thread;
    int limit = 20000; // Adjust this limit to compute enough prime numbers
    int which_prime = 5000; // Requested prime number

    /* Start the computing thread */
    if (pthread_create(&thread, NULL, generate_primes, &limit) != 0) {
        fprintf(stderr, "Thread creation failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Wait for the prime number thread to complete */
    pthread_join(thread, NULL);

    /* Print the requested prime number */
    if (which_prime <= prime_count) {
        printf("The %dth prime number is %d.\n", which_prime, primes[which_prime - 1]);
    } else {
        printf("The requested prime number is beyond the computed range.\n");
    }

    // Free dynamically allocated memory
    free(primes);

    return 0;
}
