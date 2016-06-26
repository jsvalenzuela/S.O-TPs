#ifndef ESTADISTICA_INCLUDED
#define ESTADISTICA_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "Estadistica.c"

void imprimir_estadisticas(long timepo_arranque);
long get_tiempo();

#endif // ESTADISTICA_INCLUDED
