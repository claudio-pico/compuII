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

typedef struct Usuario{
 struct Head head;
 int dscAccept;
 char usuario[30];
 char contrasena[30];
 DIR* dirPublico;
 DIR* dirPrivado;       
}Usuario ;

/*valida que el servidor logueado exista con la contraseña
  buscando en el archivo usuarios.txt
 */
int validarServidor(Usuario*);

/* Abre los directorios y lso que no existe los crea
   cargando los descriptores en Structur Usuario
 */
int directorio(Usuario*);

/* manda los nombre de los archivos para actualizar
   y actualiza los archivos locales
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


#endif
