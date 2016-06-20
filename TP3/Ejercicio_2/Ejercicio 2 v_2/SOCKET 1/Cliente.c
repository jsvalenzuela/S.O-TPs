#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 5000
#define MAX 5
#define TAMBUF 1024
#define IP "127.0.0.1"


int main()
{
	int socket_cliente,i;
	char mensaje[TAMBUF];
    struct sockaddr_in server_socket;
    // creamos el SOCKET del cliente:
	if((socket_cliente=socket(AF_INET,SOCK_STREAM,0))==-1)
		return 1;

	bzero(&(server_socket.sin_zero),8);

 	server_socket.sin_family		=	AF_INET;    // seteo el dominio.
 	server_socket.sin_port			=	htons(PORT);   //seteo el puerto.
	server_socket.sin_addr.s_addr   =	inet_addr(IP);  //seteo la ip del servidor.


	//Intentamos conectar.
  	if(connect(socket_cliente, (struct sockaddr *) &server_socket ,sizeof(server_socket))==-1)
		{
            printf("No se pudo establecer conexion, INUTIL.\n");
            return 2;
		}

	for(i=0;i<1000;i++)
 	{
        bzero(mensaje,TAMBUF);
        recv(socket_cliente,mensaje,TAMBUF,0); //bloqueante.
        sprintf ( mensaje,"El proceso %d (Cliente), te manda saludos, Mensaje  numero: %d!",getpid() , i+1 );
        send(socket_cliente,mensaje,TAMBUF,0); // le envio l mensaje al Servidor.

	}
    //Cierro el SOCKET (comunicacion):
    printf("\n");
 	close(socket_cliente);

 	return 0;
}
