#**********************************************************************#
#                    ----OPCIONES DE COMPILACION--                     #
#**********************************************************************#
CC =gcc
CFLAGS=-g -pthread -Wall
//LDLIBS=-pthread
TARGETS=servidorGyc

#**********************************************************************#
#                    ----REGLAS---                                     #
#**********************************************************************#
all: $(TARGETS)

servidor: servidor.c
	$(CC) $(CFLAGS) -o $@ $^

clean: servidor
	rm $(TARGETS) *.o

