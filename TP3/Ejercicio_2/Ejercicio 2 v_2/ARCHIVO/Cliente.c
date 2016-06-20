//CASO ARCHIVO Cliente
#include <stdio.h> //la de siempre.
#include <stdlib.h> //la de siempre.
#include <sys/stat.h> //mknod();
#include <semaphore.h> //Semaforos
#include <unistd.h> //getpid();
#define TAMBUF 1024

int main(void)
{
    int i=0;
    FILE *w;
    FILE *r;
    sem_t *x=sem_open("/x",0);
    sem_t *y=sem_open("/y",0);
    char mensaje[TAMBUF];
    
    w = fopen("Archivo(Cliente-Servidor)", "w");
	r = fopen("Archivo(Servidor-Cliente)", "r");

	if( w == NULL || r == NULL )
	{
		printf("No se pudo abrir algun archivo\n");
		exit(0);
	}
    for(i=0;i<1000;i++)
    {
		sem_wait(y); //espera al que el proceso le envie el mensaje
		fgets(mensaje, TAMBUF, r);    
		sprintf(mensaje,"\nEl proceso %d (Cliente) te dice hola!",getpid() );
        fputs(mensaje,w);
        sem_post(x); // libero al otro proceso asi puede leer el mensaje que le envie
    }
    fclose(w);
    fclose(r);
    sem_close(x);
    sem_close(y);
    
    return(0);
}
