#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include "../Estadistica.h"
#define PORT 5000
#define MAX 5
#define TAMBUF 1024

int main()
{
	
	
    long time_inicial = get_tiempo() ;


    ///CODIGO///
	struct sockaddr_in servidor_info;
	socklen_t cl=sizeof(struct sockaddr_in);
	struct sockaddr_in ca;
 	int server_socket;
	int client_socket;
	int i;
	char mensaje[TAMBUF];

	if( (server_socket=socket(AF_INET,SOCK_STREAM,0)) ==-1 ) //Creo SOCKET y verificio.
            return 1;

	bzero( (char *) &servidor_info, sizeof(struct sockaddr_in));

 	servidor_info.sin_family 		=   AF_INET;                 //Dominio
 	servidor_info.sin_port 		    =   htons(PORT);            // Convertir para que sea compatible el puerto. (i836 != tcp/ip)
	servidor_info.sin_addr.s_addr   =   INADDR_ANY;             // servidor estará escuchando en todas las
                                                                // interfaces de red que tenga nuestro sistema.

 	bind(server_socket,(struct sockaddr *)&servidor_info,sizeof(struct sockaddr_in)); //Asociar una dirección de internet al socket

 	listen(server_socket,MAX);                  // Habilitar el socket para recibir conexiones.


    //  Con accept quedará bloqueada esperando a que lleguen las conexiones desde internet:
    // si llega una peticion, crea un hilo para atender y  sigue esperando...
 	client_socket = accept( server_socket,(struct sockaddr *) &ca, &cl );


    // Lo mismo de siempre:

 	for(i=0;i<1000;i++)
 	{
        sprintf ( mensaje,"El proceso %d (Servidor), te manda saludos, Mensaje  numero: %d!",getpid() , i+1 );
     	send(client_socket,mensaje,TAMBUF,0);

        bzero(mensaje,TAMBUF);
     	recv(client_socket,mensaje,TAMBUF,0);   //Bloqueante, osea que espera al que el Cliente le envie algo.
    }

    printf("\n");
    //Cierro los SOCKETS (comunicacion y escucha):
 	close(client_socket);
 	close(server_socket);

    ///Estadisticas///


    imprimir_estadisticas(time_inicial);
    
 	return 0;
}
