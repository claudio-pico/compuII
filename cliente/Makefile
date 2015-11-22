CC = gcc
CFLAGS = -g -Wall 
#-pthread -Wall
TARGETS = clienteGyC

all: $(TARGETS)

clienteGyC: clienteGyC.c conexion.c validar.c directorio.c openNewDir.c conectado.c actualizarDirectorio.c
	$(CC) $(CFLAGS) -o $@ $^ -lssl -lcrypto

clean: clienteGyC
	rm $(TARGETS) *.o

