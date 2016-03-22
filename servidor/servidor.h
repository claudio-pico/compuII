#ifndef _SERVIOR_H_
#define _SERVIDOR_H_

#include<dirent.h>
#include <time.h>
typedef struct Usuario{
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

/*recibe los archivos del cliente [md5/nombrearchivo/fecha de moficacion] y busca los que estan
  en el servidor y compara el md5 y la utima fecha, para luego enviar los archivos que son distintos.
*/
int actualizarAchivos(Usuario*);

/*devuelve el md5
int (descriptor del archivo)
unsigned char* (puntero donde almacena el md5)
 */
void md5(int,char*);


#endif
