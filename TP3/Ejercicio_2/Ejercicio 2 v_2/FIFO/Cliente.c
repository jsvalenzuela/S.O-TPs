//Caso FIFO. Cliente
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <linux/stat.h>
#include <fcntl.h>
#define TAMBUF 1024

int main()
{
    int i = 0;
    char mensaje[TAMBUF];

    int r = open("./FIFO_S-C",O_RDONLY ); //El Cliente le lee al Servidor. El Servidor Escirbe al Cliente.
    int w = open("./FIFO_C-S",O_WRONLY ); //El cliente le escribe al Servidor. El Servidor lee del Cliente.

    if( r == -1 || w == -1 )
    {
        r = open("./FIFO_S-C",O_RDONLY );
        printf("Primero ejecuta el Servidor...\n(esto se debe, a que debo tomar estadistica sino lo hacia un while con sleep hasta que el servidor lo abre.)\n");
        exit(0);
    }
    for(  i=0; i<1000; i++){
        read(r,mensaje,TAMBUF); // Espero al que Servidor escriba. (bloquente) 
        sprintf ( mensaje,"Esten es el proceso %d (Cliente)",getpid());
        write(w,mensaje,TAMBUF);
    }
    close(r);
    close(w);
    return 0;
}
