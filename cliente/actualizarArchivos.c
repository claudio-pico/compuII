#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "cliente.h"
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
pthread_mutex_t bloqueoRead;// = PTHREAD_MUTEX_INITIALIZER;
Usuario* usuario;
int termino;
char bufResultado[512]; //almacena los nombres de los archivos que tiene que pedir.

//lee los archivos del servidor y los compara con los que le manda el cliente
//comparando el md5 y luego envia los nuevos archivos del servidor.
void* hilosActualizar(){ 
	printf(" \nhilo %u esto es termino %d\n\n",(unsigned int)pthread_self(),termino);
        char bufMd5[512];
 	char bufDir[512];
 	char outMd5[64];
  	Archivos archivo;
  	memset(archivo.nombre,'\0',64);         
 	memset(archivo.md5,'\0',64);
  	struct stat statusLocal; 
  	int op=0;
  	int encontroArchivo;
 //recibe los md5 y los nomb de los archivos 

  while(1){
//printf(" \nbloqueo antes  %d\n\n",bloqueoRead);

   pthread_mutex_lock(&bloqueoRead);
//printf(" \nbloqueo despues %d\n\n",bloqueoRead);

   if(termino!=0){
 	if((read(usuario->desSocket ,&archivo, sizeof archivo))>0){
        	if((strcmp(archivo.head.head,headM))==0 && (strcmp(archivo.head.accion,"actualizarArchivos"))==0){
                	pthread_mutex_unlock(&bloqueoRead);
                	encontroArchivo=0;// para saber si no esta el archivo en local.
                	struct dirent *dt;
    			while(((dt=readdir(usuario->dirPublico))!= NULL)){

                                memset(bufMd5,'\0',512);
                		memset(bufDir,'\0',512);
                        	// 3 casos
                        	//  md5C != md5S fecha ac>as actualiza local
                        	//  md5C != md5S fecha ac<as actualiza no actualiza local
                        	//  md5 isuales no actuliza nada 
      				if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
         		   		if(strcmp(dt->d_name,archivo.nombre)==0){
                               			encontroArchivo=1;
                                                snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,dt->d_name);
                                		op=0;
                                		op=open(bufDir, O_RDWR,0600);
                                		md5(op,outMd5);
                                		if(strcmp(outMd5,archivo.md5)!=0){
                                    // tmpMod esta en segundo, el mas grande quiere decir q es el ultimo en modificarse
                                        		stat(bufDir,&statusLocal);
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
    		rewinddir(usuario->dirPublico); // vuelve el el puntero de los archivos al principio.   
          }else{
           termino=0; 
           pthread_mutex_unlock(&bloqueoRead);
          // free(&archivo);
           pthread_exit(NULL); 

          }  
   }//read
  }else{
    pthread_mutex_unlock(&bloqueoRead);
    //free(&archivo);
    pthread_exit(NULL);
    }
}
}

int actualizarArchivos(Usuario* usu){
 usuario=usu;
 termino=1;
  pthread_mutex_init(&bloqueo,NULL);
  pthread_mutex_init(&bloqueoRead,NULL);
 printf("voya  entrar aactualizar\n");
 memset(bufResultado,'\0',512);
 #define max_thread 5
 pthread_t tid1[max_thread];
 int numh=0;
       while(termino==1 && (max_thread>numh)){
  	 pthread_create (&tid1[numh], NULL, hilosActualizar, NULL );
         sleep(3);// es para q tambien trabajen los otros hilos
         numh=numh+1;
           printf("cree hilos\n");
       }
        numh=numh-1;
       while(numh >-1 ){
          printf("mato hilos %d \n",numh);
 	  pthread_join(tid1[numh], NULL); 
          numh=numh-1;
	}
  // pthread_exit (NULL);
//   pthread_mutex_lock(&bloqueoRead);
   if(pthread_mutex_destroy(&bloqueo)==0){
    printf("bloqueo es 0 \n");
    }
   if(pthread_mutex_destroy(&bloqueoRead)==0){
     printf("bloqueoRead es 0\n");
      }
    write(1,bufResultado,sizeof bufResultado);
    recibirArchivo(bufResultado,usu);
//   pthread_exit (NULL);   
  printf("salgo \n");
  
  return 0;
  }
