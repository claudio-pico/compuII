#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"cliente.h"
int validar(char* usuario, char*contrasena , int desSocket){

	char* tok;	
	char usuCont[42];
        char res[128];
       	 memset(usuCont, '\0', 42);
         memset(res, '\0', 128);

       	 strcat(usuCont,usuario);
         strcat(usuCont,"-");
         strcat(usuCont,contrasena);
      	 if(write(desSocket,usuCont,sizeof usuCont)<0){
                perror("ERROR:pasando Usuario y contra (validar)");
		return -1;

         }
           
         if(read(desSocket ,res, sizeof res)<0){
                perror("ERROR:resp de servidor (validar)");
                return -1;

          }

        if(strcmp(res,"-1")==0){
                write (1,"Revise Usuario y Contraseña" ,32 );
                close(desSocket);
                return -1;
        }
          return 0;
}
