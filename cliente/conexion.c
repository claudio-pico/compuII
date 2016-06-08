#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include"cliente.h"
#include <netinet/tcp.h>
#include <netdb.h>
int conexion(char* ip, char* puerto,Usuario* usuario){
  
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int desSocket, s;
  /* Obtain address(es) matching host/port */

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_flags = 0;
  hints.ai_protocol = 0;          /* Any protocol */

  s = getaddrinfo(ip,puerto, &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
  }
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    desSocket = socket(rp->ai_family, rp->ai_socktype,
		       rp->ai_protocol);
    if (desSocket == -1){
      continue; 
    }
    else{
      break;
    }
  }

  /* mustra estado  keepalive ----------------------------------------------------------*/
  int optval;
  socklen_t optlen = sizeof(optval);
  if(getsockopt(desSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
    perror("getsockopt()");
    close(desSocket);
  }
  printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

  /*activa thdesSockete  */
   

  optval = 1;
  optlen = sizeof(optval);
  if(setsockopt(desSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
    perror("setsockopt()");
    close(desSocket);
  }
   
  /*   int keepcnt = 5;  //maximo de pruebas que manda antes de terminar la conexion.
       int keepidle = 30;  //El tiempo (en segundos) que la conexión tiene que permanecer inactiva antes de que TCP inicia el envío.
       int keepintvl = 120; //El tiempo (en segundos) entre peubas de actividad individuales.

       setsockopt(desSocket, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt, sizeof(int));
       setsockopt(desSocket, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle, sizeof(int));
       setsockopt(desSocket, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(int));
  */
  /* mustra otra ves el estado de keepalive */
  if(getsockopt(desSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
    perror("getsockopt()");
    close(desSocket);
  }
  printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
  //-------------------------------------------------------------

  if (connect(desSocket, rp->ai_addr, rp->ai_addrlen) < 0){
    perror("no conecto connect (servidorGyC)");
    return -1;
  }
        
  usuario->desSocket=desSocket;
  if(validar(usuario)<0){
    return -1;
  } 
         
  return 0;
}
