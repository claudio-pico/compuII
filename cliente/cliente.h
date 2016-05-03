#ifndef _CLIENTE_H_
#define _CLIENTE_H_

#include<dirent.h>

int conectado(int);
#define headM "//GyC****/"

typedef struct Head{
  char head[11];
  char accion[30];
}Head;

typedef struct Info{
  Head head;
  int cantidad;
}Info;

typedef struct Usuario{
  struct Head head;
  int desSocket;
  char usuario[30];
  char contrasena[30];
  DIR* dirTemporario;
  DIR* dirPublico;
        
}Usuario ;


/*crea el enlace con el servidor*/
int conexion(char*,Usuario*);

/*envio usuario y contraseña al servidor y espero la validacion */
int validar(Usuario*);

/*abre los directorios y almacena los pnteros en struct Cliente (si no existe los crea)*/
int directorio(Usuario*);

/*genera los md5 y los envia al servidor */
int reportar(Usuario*);
/*devuelve el md5
  int (descriptor del archivo)
  unsigned char* (puntero donde almacena el md5)
*/
void md5(int,char*);

void  mandarArchivos(Usuario*);

/* recibe el nombre y contenido de los archivos, elimina luego creael archivo y le ingresa el contenido
 */
int recibirArchivo(char*,Usuario*,int);

/*recibe los archivos del cliente [md5/nombrearchivo/fecha de moficacion] y busca los que estan
  en el servidor y compara el md5 y la utima fecha, para luego enviar los archivos que son distintos.
*/
int actualizarArchivos(Usuario*);

/*cuenta la cantidad de archivos que hay en un directorio*/
int contarArchivos(DIR*);

/*Verifica que la actualizacion del archivo fue correcta, si no lo fue 
vulve el archivo al estado anterior*/
void verificarMd5(char*,char*,char*);

#endif
