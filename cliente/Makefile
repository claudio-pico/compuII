CC = gcc
CFLAGS = -g -pthread -Wall 
#-pthread -Wall
TARGETS = clienteGyC

all: $(TARGETS)

clienteGyC: clienteGyC.c conexion.c validar.c directorio.c openNewDir.c conectado.c reportar.c mandarArchivos.c  actualizarArchivos.c recibirArchivo.c contarArchivos.c verificarMd5.c md5.c
	$(CC) $(CFLAGS) -o $@ $^ -lcrypto

clean: clienteGyC
	rm $(TARGETS) *.o

