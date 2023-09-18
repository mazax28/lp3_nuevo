#include <stdio.h>

/*
AL EJECUTAR UN PRORGRAMA EN LA LINEA DE COMANDOS PUEDES DAR MAS INFORMACION,
DESUES DEL NOMBRE DEL PROGRAMA, ESTOS SON LLAMADOS COMMANDS-LINE ARGUMENTS
ARGC: ES UN ENTERO QUE CONTIENE EL NUMERO DE ITEMS QUE CONTIENE ARGV

*/

int main(int argc, char* argv[]){

    /*IMPRIME LA PRIMERA POSICION DEL argv, EL CUAL ES EL NOMBRE DEL PROGRAMA*/
    printf("the name of the program is '%s' .\n",argv[0]);


    /*IMPRIME EL NUMERO DE ARGUMENTOS QUE NO SON EL NOMBRE DEL PROGRAMA*/
    printf("this program was inoked with %d arguments.\n", argc-1);
    

    /*VERIFICA SI SE PASARON ARGUMENTOS*/
    if(argc>1){
        int i;

        printf("the arguments are:\n");

        for ( i = 1; i < argc; ++i)
        {
            printf("%s\n",argv[i]);
        }
        
    }


    return 0;
}