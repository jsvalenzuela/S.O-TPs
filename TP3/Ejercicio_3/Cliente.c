#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>
#define ESTRUCTURA_FILE "archivo"

int getrusage(int who, struct rusage *usage);

int main(void)
{
 struct rusage usage;
 long tiempoSistema;
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
 tiempoSistema = usage.ru_stime.tv_sec * 1e6 + usage.ru_stime.tv_usec;
 printf ("Tiempo de CPU del proceso A: %ld.%06ld sec user, %ld.%06ld sec system bloques entrada %ld bloques salida%ld\n",
          usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
          usage.ru_stime.tv_sec, usage.ru_stime.tv_usec, usage.ru_inblock, usage.ru_oublock);


 return(0);
}