// CASO ARCHIVOS SERIDOR.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "../Estadistica.h"
#define TAMBUF 1024

int main(void)
{

    long time_inicial = get_tiempo() ;

    ///CODIGO.    
    int i;
    FILE *w;
    FILE *r;
	sem_t *x = sem_open("/x",O_CREAT|O_EXCL,0666,0);
    sem_t *y = sem_open("/y",O_CREAT|O_EXCL,0666,0);


    char mensaje[1024];
    /* Crea el archivo si no existe */
	
    mknod("Archivo(Servidor-Cliente)", 0666, 0);
    mknod("Archivo(Cliente-Servidor)", 0666, 0);
    
	w = fopen("Archivo(Servidor-Cliente)", "w");
	r = fopen("Archivo(Cliente-Servidor)", "r");
	if( w == NULL || r == NULL )
	{
		printf("No se pudo abrir algun archivo\n");
		exit(0);
	}
	
	for(i=0;i<1000;i++)
    {
		sprintf(mensaje,"\nEl proceso %d (Servidor) te dice hola!",getpid() );
        fputs(mensaje,w);
        sem_post(y); //le doy el recurso al otro proceso, asi escribe
        sem_wait(x);      // espero que escriba.
        fgets(mensaje, TAMBUF, r);
    }
    
    fclose(w);
    fclose(r);
    sem_close(x);
    sem_close(y);
    sem_unlink("/x");
    sem_unlink("/y");
    
    imprimir_estadisticas(time_inicial);
    
    
    return(0);
}
