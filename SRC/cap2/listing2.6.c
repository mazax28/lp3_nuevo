#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// Función para leer datos desde un archivo y almacenarlos en un búfer.
char* read_from_file(const char* filename, size_t length) {
    char* buffer = NULL;
    int fd;
    ssize_t bytes_read;

    // Asigna memoria para el búfer.
    buffer = (char*)malloc(length);
    if (buffer == NULL)
        return NULL;

    // Abre el archivo en modo lectura.
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        // Fallo al abrir el archivo. Libera la memoria del búfer antes de retornar.
        free(buffer);
        return NULL;
    }

    // Lee los datos desde el archivo al búfer.
    bytes_read = read(fd, buffer, length);
    if (bytes_read == -1) {
        // Error de lectura. Libera la memoria del búfer y cierra el archivo antes de retornar.
        free(buffer);
        close(fd);
        return NULL;
    }

    // Cierra el archivo y retorna el búfer.
    close(fd);
    return buffer;
}

int main() {
    const char* filename = "hola.txt"; // Reemplaza con el nombre de tu archivo
    size_t length = 100000; // Reemplaza con la longitud deseada

    // Llama a la función read_from_file
    char* buffer = read_from_file(filename, length);

    if (buffer != NULL) {
        // Imprime los datos leídos desde el archivo
        printf("Datos leídos desde el archivo:\n%s\n", buffer);

        // Libera la memoria del búfer cuando ya no se necesite
        free(buffer);
    } else {
        printf("Error al leer el archivo.\n");
    }

    return 0;
}
