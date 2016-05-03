#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"servidor.h"
#include<fcntl.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
DIR* openNewDir(char*);

int directorio(Usuario* usuario){

 
  char path [128]="./Directorio/";
  // memset(pathmemset(pathAux, '\0', 128);, '\0', 128);
  char pathAux[128];
  memset(pathAux, '\0', 128);
  DIR *dire,*dirUsuario;
  printf("este es usuario en diretorio %s",usuario->usuario);
  /*openNewDir abre el directorio si no exite lo crea y lo abre.
    erro =NULL
    return DIR */	
  if((dire=openNewDir(path))!=NULL){
    strcat(path,usuario->usuario);
    if((dirUsuario=openNewDir(path))!=NULL){ 
      strcat(pathAux,path);
      strcat(path,"/temporario");             
      if((usuario->dirTemporario=openNewDir(path))!=NULL){
	strcat(pathAux,"/publico");
	if((usuario->dirPublico=openNewDir(pathAux))!=NULL){
	  return 0;
	}else{return -1;}
      }else{return -1;}
    }else{return -1;}
  }else{return -1;
  }
  return 0;

}
