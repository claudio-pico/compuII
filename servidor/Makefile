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

servidorGyC: servidorGyC.c
	$(CC) $(CFLAGS) -o $@ $^

clean: servidorGyC
	rm $(TARGETS) *.o

