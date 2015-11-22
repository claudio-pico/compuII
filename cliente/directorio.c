#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"cliente.h"
#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
DIR* openNewDir(char*);

int directorio(Cliente* cliente){

 
 char path [128]="./Directorio/";
 char pathAux[128];
 memset(pathAux, '\0', 128);
 DIR *dire,*dirUsuario;
        /*openNewDir abre el directorio si no exite lo crea y lo abre.
        erro =NULL
        return DIR */	
	if((dire=openNewDir(path))!=NULL){
            strcat(path,cliente->usuario);
            if((dirUsuario=openNewDir(path))!=NULL){ 
	      strcat(pathAux,path);
              strcat(path,"/privado");
              if((cliente->dirPrivado=openNewDir(path))!=NULL){
                  strcat(pathAux,"/publico");
                  if((cliente->dirPublico=openNewDir(pathAux))!=NULL){
         	  return 0;
                 }else{return -1;}
             }else{return -1;}
           }else{return -1;}
       }else{return -1;}

   return 0;

}
