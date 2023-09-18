#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *server_name;

    // Intenta obtener el nombre del servidor de la variable de entorno SERVER_NAME
    server_name = getenv("SERVER_NAME");
    /*se ha mofificado para que puede agregar un nombre*/
    if (server_name == NULL && argc == 2) {
        // Si la variable de entorno no está definida y se proporciona un argumento,
        // utiliza el argumento como el nombre del servidor.
        server_name = argv[1];
    } else if (server_name == NULL) {
        // Si la variable de entorno no está definida y no se proporciona un argumento,
        // utiliza un valor predeterminado.
        server_name = "server.my-company.com";
    }

    printf("Accediendo al servidor %s\n", server_name);
    /* Accede al servidor aquí... */
    return 0;
}
