#ifndef _HEAD_H_
#define _HEAD_H_



typedef struct Usuario{
 int dscAccept;
 char usuario[30];
 char contrasena[30];
        
}Usuario ;

int validarServidor(Usuario*);
 int directorio(char*);

#endif
