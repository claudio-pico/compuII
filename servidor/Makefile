#**********************************************************************#
#                    ----OPCIONES DE COMPILACION--                     #
#**********************************************************************#
CC =gcc
CFLAGS=-g -pthread -Wall
//LDLIBS=-pthread
TARGETS=servidorGyC

#**********************************************************************#
#                    ----REGLAS---                                     #
#**********************************************************************#
all: $(TARGETS)

servidorGyC: servidorGyC.c validarServidor.c directorio.c openNewDir.c actualizarCliente.c
	$(CC) $(CFLAGS) -o $@ $^

clean: servidorGyC
	rm $(TARGETS) *.o *.swp


