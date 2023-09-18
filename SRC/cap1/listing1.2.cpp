/*INCLUYE LA LIBRERIA DE ASERCIONES PARA CONDICIONES*/
#include <cassert>

/*INCLUYE ARCHIVO ENCABEZADO QUE CONTIENE LA DECLARACION DE LA FUNCION reciprocal*/
#include "listing1.3.hpp"

double reciprocal(int i){

    /*VERIFICA SI EL NUMERO ES DISTINTO DE 0*/
    assert(i!=0);

    /*CALCULA Y DEVUELVE EL RECIPROCO DEL NUMERO*/
    return 1.0/i;
    
}