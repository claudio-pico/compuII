#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"cliente.h"
#include <unistd.h>
int contarArchivos(DIR* directorio){			 
  int cont=0;
  struct dirent *dt;
  while((dt=readdir(directorio)) != NULL){
    if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
      cont++;
    }
  }
  rewinddir(directorio);
  return cont;
}
