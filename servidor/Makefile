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

servidorGyC: servidorGyC.c validarServidor.c directorio.c openNewDir.c actualizarArchivos.c md5.c recibirArchivo.c reportar.c mandarArchivos.c
	$(CC) $(CFLAGS) -o $@ $^ -lcrypto

clean: servidorGyC
	rm $(TARGETS) *.o *.swp


