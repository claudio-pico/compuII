#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<fcntl.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

DIR* openNewDir(char* path){
  DIR *dire;       
 
  if((dire=opendir(path))==NULL){
    if(mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)<0){
      perror("Error en la creacion de directorio (servidorGyC.c)");
      return NULL;
    }
    dire=opendir(path);
  }

  return dire;
}
