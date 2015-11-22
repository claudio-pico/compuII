#ifndef _HEAD_H_
#define _HEAD_H_

#include<dirent.h>

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

/*recibe los archivos del cliente [md5/nombrearchivo] y busca los que estan
  en el servidor y compara el md5, para luego enviar los archivos que son distintos.
*/
int actualizarCliente(Usuario*);

#endif
