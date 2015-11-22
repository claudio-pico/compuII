#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include"cliente.h"
#include <unistd.h>


int validar(Cliente* cliente){
	
	char usuCont[42];
        char res[128];
       	 memset(usuCont, '\0', 42);
         memset(res, '\0', 128);

       	 strcat(usuCont,cliente->usuario);
         strcat(usuCont,"-");
         strcat(usuCont,cliente->contrasena);
      	 if(write(cliente->desSocket,usuCont,sizeof usuCont)<0){
                perror("ERROR:pasando Usuario y contra (validar)");
		return -1;

         }
           
         if(read(cliente->desSocket ,res, sizeof res)<0){
                perror("ERROR:resp de servidor (validar)");
                return -1;

          }

        if(strcmp(res,"-1")==0){
                write (1,"Revise Usuario y Contraseña" ,32 );
                close(cliente->desSocket);
                return -1;
        }
          return 0;
}
