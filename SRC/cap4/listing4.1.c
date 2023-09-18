#include <pthread.h>
#include <stdio.h>
/*Funcion para imprimir x's en stderr. */
void *print_xs(void *unused)
{
   while (1)
      fputc('x', stderr);
   return NULL;
}
/* Programa Principal. */
int main()
{
   pthread_t thread_id;
   /* Crear un hilo que imprima las x. */
   pthread_create(&thread_id, NULL, &print_xs, NULL);
   /* Imprimir o's continuamente. */
   while (1)
      fputc('o', stderr);
   return 0;
}