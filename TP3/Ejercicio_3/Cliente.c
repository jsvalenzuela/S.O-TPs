#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#define ESTRUCTURA_FILE "archivo"

int getrusage(int who, struct rusage *usage);
long get_micro();
long get_micro_desde_timeval(const struct timeval tiempo);

int main(void)
{
 long tiempo_arranque = get_micro();
 struct rusage usage;
 long tiempo_sistema,tiempo_total,tiempo_usuario;
 int i=0;
 FILE *fp;
 
 char readbuf[1000]="acávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kbysevaarepetirestetextohastaquellegueacávamicadenarelocaquierotenerunlargode1kby";
;
 /* Crea el FIFO si no existe */
 umask(0);
 mknod(ESTRUCTURA_FILE, S_IFIFO|0666, 0);

 while(i<1000)
 {
     fp = fopen(ESTRUCTURA_FILE, "w");
     fputs(readbuf,fp);
     fclose(fp);

     fp = fopen(ESTRUCTURA_FILE, "r");
     fgets(readbuf, 80, fp);
     fclose(fp);
     printf("Cadena recibida en el proceso 2: %s %d \n", readbuf,i);

     i++;
 }

 getrusage(RUSAGE_SELF,&usage);
 long tiempo_total = get_micro() - tiempo_arranque;
 long tiempo_sistema = get_micro_desde_timeval(usage.ru_stime);
 long tiempo_usuario = get_micro_desde_timeval(usage.ru_utime);
 
 printf ("Tiempo de CPU del proceso A: %ld.%06ld sec reloj, %ld.%06ld sec user, %ld.%06ld sec system bloques entrada %ld bloques salida%ld\n",
          tiempo_total,tiempo_total,
          tiempo_usuario, tiempo_usuario,
          tiempo_sistema, tiempo_sistema, usage.ru_inblock, usage.ru_oublock);


 return(0);
}
 
 
 long get_micro() {
  struct timespec tiempo_inicial;
  clock_gettime(CLOCK_MONOTONIC_RAW, &tiempo_inicial);
  return tiempo_inicial.tv_sec * 1e6 + tiempo_inicial.tv_nsec / 1e3;
}

long get_micro_desde_timeval(const struct timeval tiempo) {
  return tiempo.tv_sec * 1e6 + tiempo.tv_usec;
}
