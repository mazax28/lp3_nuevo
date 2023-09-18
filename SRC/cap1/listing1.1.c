

/*INCLUYE LA BIBLIOTECA ESTANDAR DE ENTRADA Y SALIDA*/
#include <stdio.h>

/*INCLUYE ARCHIVO ENCABEZADO QUE CONTIENE LA DECLARACION DE LA FUNCION reciprocal*/
#include "listing1.3.hpp"

/*ESTA LIBRERIA SE TUVO QUE AGREGAR PARA UTILIZAR LA FUNCION atoi*/
#include<stdlib.h>

int main (int argc, char **argv){

    int i;

    /*CONVIERTE EL PRIMER ARGUMENTO DE LA LINEA DE COMANDOS EN UN ENTERO*/
    i = atoi(argv[1]);


    /*IMPRIME EL RESULTADO DEL CALCULO DEL RECIPROCO DEL NUMERO*/
    printf("the reciprocal of %d is %g\n ",i, reciprocal(i));


    return 0;
}
