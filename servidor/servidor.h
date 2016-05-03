#ifndef _SERVIOR_H_
#define _SERVIDOR_H_

#include<dirent.h>
#include <time.h>

#define headM "//GyC****/"
//const char headConst[11]  = "//GyC****//" ;

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
  int dscAccept;
  char usuario[30];
  char contrasena[30];
  DIR* dirPublico;
  DIR* dirTemporario;       
}Usuario ;

/*valida que el servidor logueado exista con la contraseña
  buscando en el archivo usuarios.txt
*/
int validarServidor(Usuario*);

/* Abre los directorios y lso que no existe los crea
   cargando los descriptores en Structur Usuario
*/
int directorio(Usuario*);

/* recibe el nombre y contenido de los archivos, elimina luego creael archivo y le ingresa el contenido
 */
int recibirArchivo(char*,Usuario*);


/*recibe los archivos del cliente [md5/nombrearchivo/fecha de moficacion] y busca los que estan
  en el servidor y compara el md5 y la utima fecha, para luego enviar los archivos que son distintos.
*/
int actualizarArchivos(Usuario*);

/*devuelve el md5
  int (descriptor del archivo)
  unsigned char* (puntero donde almacena el md5)
*/
void md5(int,char*);

/*genera los md5 y los envia al servidor */
int reportar(Usuario*);

void  mandarArchivos(Usuario*);

/*cuenta la cantidad de archivos que hay en un directorio*/
int contarArchivos(DIR*);
#endif
