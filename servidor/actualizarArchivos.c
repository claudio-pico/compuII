#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "servidor.h"
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct Archivos{
  struct Head head;
  char nombre[32];
  char md5[64];   
  time_t tmpMod;
}Archivos ;
pthread_mutex_t bloqueo;// = PTHREAD_MUTEX_INITIALIZER;
Usuario* usuario;
char bufResultado[512]; //almacena los nombres de los archivos que tiene que pedir.

//lee los archivos del servidor y los compara con los que le manda el cliente
//comparando el md5 y luego envia los nuevos archivos del servidor.
void* hilosActualizar(){ 
  DIR *dire;
  char bufDir[512];
  char outMd5[64];
  Archivos archivo;
  memset(&archivo,'\0',sizeof archivo );         
  struct stat statusLocal; 
  int op=0;
  int encontroArchivo;
  //recibe los md5 y los nomb de los archivos
  if((read(usuario->dscAccept ,&archivo, sizeof archivo))>0){
    if((strcmp(archivo.head.head,headM))==0 && (strcmp(archivo.head.accion,"actualizarArchivos"))==0){
      encontroArchivo=0;// para saber si no esta el archivo en local.
      struct dirent *dt;
      memset(bufDir,'\0',sizeof bufDir);
      snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/",usuario->usuario);
      dire=opendir(bufDir);
      char bufDirAux[512];
      while(((dt=readdir(dire))!= NULL)){
 	memset(bufDirAux,'\0',sizeof bufDirAux);
	
        // 3 casos
	//  md5C != md5S fecha ac>as actualiza local
	//  md5C != md5S fecha ac<as actualiza no actualiza local
	//  md5 isuales no actuliza nada 
	if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
	  if(strcmp(dt->d_name,archivo.nombre)==0){
	    encontroArchivo=1;
	    strcat(bufDirAux,bufDir);
            strcat(bufDirAux,dt->d_name);
            op=0;
	    //op=open(bufDirAux,O_RDWR,0600);
            op=open(bufDirAux,O_RDONLY,0600);
            memset(outMd5,'\0',sizeof outMd5);
            md5(op,outMd5);
            close(op);
	    printf(" \nnombre %s md5local %s md %s \n", dt->d_name ,outMd5 ,archivo.md5);
	    if(strcmp(outMd5,archivo.md5)!=0){
	      // tmpMod esta en segundo, el mas grande quiere decir q es el ultimo en modificarse
	      stat(bufDirAux,&statusLocal);
	      if(archivo.tmpMod>statusLocal.st_mtime){
		pthread_mutex_lock(&bloqueo);
		strcat(bufResultado,archivo.nombre);
		strcat(bufResultado,"\n");
		pthread_mutex_unlock(&bloqueo);
	      }
	    }
	  }
	}          
      }
      //los archivos que no estan en local 
      if(encontroArchivo==0){
	pthread_mutex_lock(&bloqueo);
	strcat(bufResultado,archivo.nombre);
	strcat(bufResultado,"\n");
	pthread_mutex_unlock(&bloqueo);
      }
      closedir(dire);   
    }else{	   
      perror("Error de flujo actualizar.c-hilos");
           
    }  
  }//read
  pthread_exit(NULL);
}

int actualizarArchivos(Usuario* usu){
  usuario=usu;
  pthread_mutex_init(&bloqueo,NULL);
  memset(bufResultado,'\0',sizeof bufResultado);
  Info info;
  if((read(usuario->dscAccept ,&info, sizeof info))<0){
    perror("Leer el Info(actualizarArchivo.c)");
    return -1;
  }
  int cantHilos=info.cantidad-1; 
  pthread_t tid1[cantHilos];
  int numh=0;
  while(info.cantidad>numh){
    pthread_create (&tid1[numh], NULL, hilosActualizar, NULL );
    numh=numh+1;
  }
  numh=numh-1;
  while(numh >-1 ){
    pthread_join(tid1[numh], NULL); 
    numh=numh-1;
  }
  pthread_mutex_destroy(&bloqueo);
  recibirArchivo(bufResultado,usu);
  return 0;
}
