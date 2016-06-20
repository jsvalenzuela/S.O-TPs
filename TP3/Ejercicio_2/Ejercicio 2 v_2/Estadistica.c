#include "Estadistica.h"

long get_tiempo()
{
    struct timespec tiempo;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tiempo);
    return tiempo.tv_sec * 1000000 + tiempo.tv_nsec / 1000;
};


void imprimir_estadisticas(long tiempo_inicio)
{
    struct rusage datos_estadisticas_fin;

	long int tiempoCPU_S ;
    long int tiempoCPU_U ;

    long int time;

    printf("\n\n ESTADISTICAS \n");

    getrusage( RUSAGE_SELF , &datos_estadisticas_fin );

    time = get_tiempo() - tiempo_inicio;
    printf("\nTiempo Reloj:..........................%ld µs",time);

    tiempoCPU_S = datos_estadisticas_fin.ru_stime.tv_sec * 1000000 + datos_estadisticas_fin.ru_stime.tv_usec;
    printf("\nEl Tiempo de CPU del Sistema es de:....%ld µs",tiempoCPU_S);

    tiempoCPU_U = ( datos_estadisticas_fin.ru_utime.tv_sec *1000000 + datos_estadisticas_fin.ru_utime.tv_usec );
    printf("\nEl Tiempo de CPU del Usuario es de:....%ld µs",tiempoCPU_U);

    printf("\nPeticiones de pagina(soft page faults):%ld",datos_estadisticas_fin.ru_minflt );

    printf("\nFallo  de pagina ( hard page faults):..%ld",datos_estadisticas_fin.ru_majflt);
    printf("\nOperaciones de Entrada (en bloques):...%ld",datos_estadisticas_fin.ru_inblock);
    printf("\nOperaciones de Salida (en bloques):....%ld",datos_estadisticas_fin.ru_oublock);
    printf("\nMensajes IPC enviados:.................%ld",datos_estadisticas_fin.ru_msgsnd);
    printf("\nMensajes IPC recibido:.................%ld",datos_estadisticas_fin.ru_msgrcv);

    printf( "\n\n FIN ESTADISTICAS \n" );
}
