#ifndef _CLIENTE_H_
#define _CLIENTE_H_

 #include<dirent.h>

int conectado(int);


typedef struct Usuario{
 int desSocket;
 char usuario[30];
 char contrasena[30];
 DIR* dirPublico;
 DIR* dirPrivado;
        
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
#endif
