#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/* El nombre de este programa. */
const char* program_name;

/* Imprime información de uso para este programa en STREAM (normalmente
   stdout o stderr) y sale del programa con EXIT_CODE. No retorna. */
void print_usage(FILE* stream, int exit_code)
{
    fprintf(stream, "Usage: %s options [ inputfile ... ]\n", program_name);
    fprintf(stream,
        " -h --help     Muestra esta información de uso.\n"
        " -o --output   Especifica un archivo de salida.\n"
        " -v --verbose  Muestra mensajes detallados.\n");
    exit(exit_code);
}

/* Punto de entrada principal del programa. ARGC contiene el número de elementos en la lista
   de argumentos; ARGV es un array de punteros a ellos. */
int main(int argc, char* argv[])
{
    int next_option;

    /* Una cadena que enumera las letras de las opciones cortas válidas. */
    const char* const short_options = "ho:v";

    /* Un array que describe las opciones largas válidas. */
    const struct option long_options[] = {
        { "help",    0, NULL, 'h' },
        { "output",  1, NULL, 'o' },
        { "verbose", 0, NULL, 'v' },
        { NULL,      0, NULL, 0 }
    };

    /* El nombre del archivo para recibir la salida del programa o NULL
       para la salida estándar. */
    const char* output_filename = NULL;

    /* Si se deben mostrar mensajes detallados. */
    int verbose = 0;

    /* Guarda el nombre del programa para usar en los mensajes.
       El nombre se almacena en argv[0]. */
    program_name = argv[0];

    do {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);

        switch (next_option)
        {
            case 'h': /* -h o --help */
                /* El usuario solicitó información de uso. Imprímela en la salida estándar
                   y salga con el código de salida cero (terminación normal). */
                print_usage(stdout, 0);
                break;
            case 'o': /* -o o --output */
                /* Esta opción toma un argumento, el nombre del archivo de salida. */
                output_filename = optarg;
                break;
            case 'v': /* -v o --verbose */
                verbose = 1;
                break;
            case '?': /* El usuario especificó una opción inválida. */
                /* Imprime información de uso en la salida de error estándar
                   y sale con el código de salida uno (indicando terminación anormal). */
                print_usage(stderr, 1);
                break;
            case -1: /* Terminado con las opciones. */
                break;
            default: /* Algo más: inesperado. */
                abort();
        }
    } while (next_option != -1);

    /* Hecho con las opciones. OPTIND apunta al primer argumento no de opción.
       Por razones de demostración, imprímelos si se especificó la opción verbose. */
    if (verbose) {
        int i;
        for (i = optind; i < argc; ++i)
            printf("Argument: %s\n", argv[i]);
    }

    /* El programa principal continúa aquí. */
    return 0;
}
