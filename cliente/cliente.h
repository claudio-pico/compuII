#ifndef _CLIENTE_H_
#define _CLIENTE_H_

 #include<dirent.h>

int conectado(int);


typedef struct Cliente{
 int desSocket;
 char* usuario;
 char* contrasena;
 DIR* dirPublico;
 DIR* dirPrivado;
        
}Cliente ;


int conexion(char*,Cliente*);
int validar(Cliente*);
int directorio(Cliente*);
int actualizarDirectorio(Cliente*);
#endif
