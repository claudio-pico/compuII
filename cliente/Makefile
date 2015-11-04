CC = gcc
CFLAGS = -g 
#-pthread -Wall
TARGETS = clienteGyC

all: $(TARGETS)

clienteGyC: clienteGyC.c conexion.c validar.c directorio.c openNewDir.c conectado.c
	$(CC) $(CFLAGS) -o $@ $^

clean: clienteGyC
	rm $(TARGETS) *.o

