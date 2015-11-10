#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"head.h"
#include<fcntl.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
DIR* openNewDir(char*);

int directorio(char* usuario){

 
 char path [128]="./Directorio/";
 char pathAux[128];
 memset(pathAux, '\0', 128);
 DIR *dire,*dirUsuario,*dirPrivado,*dirPublico;
 struct dirent *dt;
 struct stat estru;

        /*openNewDir abre el directorio si no exite lo crea y lo abre.
        erro =NULL
        return DIR */	
	if((dire=openNewDir(path))!=NULL){
            strcat(path,usuario);
            if((dirUsuario=openNewDir(path))!=NULL){ 
	      strcat(pathAux,path);
              strcat(path,"/privado");
              if((dirPrivado=openNewDir(path))!=NULL){
                  strcat(pathAux,"/publico");
                  if((dirPublico=openNewDir(pathAux))!=NULL){
         		while((dt=readdir(dire)) != NULL){
			//Con la función stat podemos ver el estado de los ficheros
			// se muestra los permisos, nombre, y tamaño               
                 	stat(dt->d_name, &estru);
			// imprimir(estru);
			printf("%-20s \n",dt->d_name);
                        }
                 }
             }
           }
       }else{
         return -1;
       }
 printf("estoy saliendo>Direc");
   return 0;

}
