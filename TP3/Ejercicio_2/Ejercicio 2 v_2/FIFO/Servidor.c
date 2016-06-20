#include <sys/times.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#include <fcntl.h>
#include <time.h>
#include "../Estadistica.h"
#define TAMBUF 1024


int main()
{
    long time_inicial = get_tiempo() ;

    ///Empieza proceso de tuberia.
    int i = 0;
    char mensaje[TAMBUF];


    unlink("./FIFO_S-C");
    unlink("./FIFO_C-S"); // si los fifos fueron generados pero no borrados los borros por si las moscas.

    mkfifo ("./FIFO_S-C", 0666);//El Servidor escribe al Cliente. El Cliente lee del servidor.
    mkfifo ("./FIFO_C-S", 0666);//El Servidor lee del Cliente. El Cliente le escribe al Servidor.

    int w = open("./FIFO_S-C",O_WRONLY);
    int r = open("./FIFO_C-S",O_RDONLY);


    if( r == -1 || w == -1)
    {
        printf("Alguna tuberia, no se pudo crear.");
        exit(0);
    }
    for( i=0; i<1000; i++){

        sprintf ( mensaje,"Esten es el proceso %d (Servidor)",getpid() );
        write ( w , mensaje , TAMBUF );
        read ( r , mensaje , TAMBUF ); // Espera al que Cliente escriba.
    }
    close(r);
    close(w);

    unlink("./FIFO_S-C");
    unlink("./FIFO_C-S");
    ///Termina Proceso de tuberia.

    imprimir_estadisticas(time_inicial);

    return 0;
}
