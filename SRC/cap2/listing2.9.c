#include <stdio.h>
#include <tiffio.h>


/*
 este programa es un ejemplo mínimo que demuestra
cómo abrir y cerrar un archivo TIFF utilizando la biblioteca LibTIFF. 

*/

int main(int argc, char** argv) {
    TIFF* tiff;
    tiff = TIFFOpen(argv[1], "r");
    TIFFClose(tiff);
    return 0;
}
