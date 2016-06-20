#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "../Estadistica.h"
#define MAX 1024

int main()
{

    long time_inicial = get_tiempo() ;

	int i;    
    
    int shmid;
    shmid = shmget( (key_t)678 , MAX*sizeof(char),IPC_CREAT | IPC_EXCL | 0666 );
    if( shmid == -1 )
    {    
		shmctl(shmid,IPC_RMID,NULL); // Elimino ;)		
		shmid = shmget( (key_t)678 , MAX*sizeof(char),IPC_CREAT | IPC_EXCL | 0666 );
	}
    
    char *mensaje = (char*)shmat(shmid,NULL,0);
	
    sem_t *x = sem_open("/x",O_CREAT|O_EXCL,0666,1);
    sem_t *y = sem_open("/y",O_CREAT|O_EXCL,0666,0);

    for( i=0; i<1000; i++ )
    {
        sem_wait(x);
        sprintf ( mensaje,"El proceso %d (A), te manda saludos, Mensaje  numero: %d!",getpid() , i );
        sem_post(y);
    }

    sem_close(x);
    sem_close(y);
    sem_unlink("/x");
    sem_unlink("/y");
	
	shmctl(shmid,IPC_RMID,NULL); // Elimino ;) 

    imprimir_estadisticas(time_inicial);
	
	return 0;
}
