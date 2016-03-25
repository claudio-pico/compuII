#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include"servidor.h"
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct Archivos{
   char nombre[32];
   char md5[64];   
   time_t tmpMod;
      }Archivos ;
pthread_mutex_t bloqueo = PTHREAD_MUTEX_INITIALIZER;
Usuario* usuario;
int i=-1;// es para ver quine es el hilo q trabaja
int termino;
int leido;
char bufResultado[512]; //almacena los nombres de los archivos que tiene que pedir.

//lee los archivos del servidor y los compara con los que le manda el cliente
//comparando el md5 y luego envia los nuevos archivos del servidor.
void* hilosActualizar(){ 
  i=i+1;
  printf(" \nhilo %d \n\n",i);
 char bufMd5[512];
 char bufDir[512];
 char outMd5[64];
 
  Archivos archivo;
  memset(archivo.nombre,'\0',64);         
  memset(archivo.md5,'\0',64);
  struct stat statusLocal; 
  int op=0;
  int encontroArchivo=0;
 //recibe los md5 y los nomb de los archivos 
 while((leido=read(usuario->dscAccept ,&archivo, sizeof archivo))){

                encontroArchivo=0;// para que corte el while si encuentra el archivo.
                struct dirent *dt;
    		while(((dt=readdir(usuario->dirPublico))!= NULL) && encontroArchivo==0){
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
                                         printf("los q estan y tiene el md5 distintos : %s hilo: %d \n",archivo.nombre,i);             
                                        }
              			 }else{ //solo para ver que hilos atiende cada archivo.
                                   printf("SON IGUALES: %s hilo: %d \n",archivo.nombre,i);
                                 }
                            }
       			}          
      		}
               //los archivos que no estan en local 
              if(encontroArchivo==0){
                  printf("los que no estan en el servidor : %s hilo: %d \n",archivo.nombre,i);
                  pthread_mutex_lock(&bloqueo);
                    strcat(bufResultado,archivo.nombre);
                    strcat(bufResultado,"\n");
                  pthread_mutex_unlock(&bloqueo);
   
               } 
      		rewinddir(usuario->dirPublico); // vuelve el el puntero de los archivos al principio.   
  }
  if(leido==0){
    termino=0;// es para que no cree hilos si ya termino de leer.
   }
   pthread_exit (NULL);
}

int actualizarArchivos(Usuario* usu){
 usuario=usu;
 i=0;
 termino=1;
 memset(bufResultado,'\0',512);
 #define max_thread 10
 pthread_t tid1[max_thread];
 int numh=0;
       while(termino==1 && (max_thread>numh)){
  	 pthread_create (&tid1[numh], NULL, hilosActualizar, NULL );
         sleep(2);// es para q tambien trabajen los otros hilos
         numh=numh+1;
       }
        numh=numh-1;
        while(numh >-1 ){
 	 pthread_join(tid1[numh], NULL);
         printf("mato hilos %d \n",numh);
         numh=numh-1;
	}
   write(1,bufResultado,sizeof(bufResultado)); // imprime el resultado.
  return 0;
  }
