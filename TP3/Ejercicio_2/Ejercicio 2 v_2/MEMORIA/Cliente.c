//CASO MEMORIA Cliente. 
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/sem.h>

#define MAX 1024

int main()
{
    int i;
    int shmid = shmget( (key_t)678 , MAX*sizeof(char),IPC_CREAT | 0666 );
    char *mensaje = (char*)shmat(shmid,NULL,0);
    sem_t *x=sem_open("/x",0);
    sem_t *y=sem_open("/y",0);

    for( i=0; i<1000; i++ )
    {
        sem_wait(y);
        sprintf ( mensaje,"El proceso %d (B), te manda saludos, Mensaje  numero: %d!",getpid() , i );
        sem_post(x);
    }


    sem_close(x);
    sem_close(y);

    return 0;
}
