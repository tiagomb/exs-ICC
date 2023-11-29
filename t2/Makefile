# PROGRAMA
    PROG = ajustePol

# Compilador
	LIKWID_HOME = /home/soft/likwid
    CC     = gcc
    CFLAGS = -Wall -g -O3 -mavx -march=native -falign-functions=32 -falign-loops=32 -I${LIKWID_HOME}/include -DLIKWID_PERFMON 
    LIBS = -L${LIKWID_HOME}/lib -llikwid -lm

# Lista de arquivos para distribuição
    DISTFILES = *.c *.h LEIAME* Makefile teste*.in script.sh
    DISTDIR = msac22-tmb22

.PHONY: all clean purge dist

all: ajustePol ajustePolOtim gera_entrada

debug: CFLAGS += -D_DEBUG_
debug: ajustePol ajustePolOtim


clean:
	@echo "Limpando tudo ..."
	@rm -f ajustePol ajustePolOtim gera_entrada *.o core a.out $(DISTDIR) $(DISTDIR).tar

ajustePol: ajustePol.o interval.o utils.o sistemas.o
	gcc $(CFLAGS) -o ajustePol ajustePol.o interval.o utils.o sistemas.o $(LIBS)

ajustePolOtim: ajustePolOtim.o utilsOtim.o sistemasOtim.o
	gcc $(CFLAGS) -o ajustePolOtim ajustePolOtim.o utilsOtim.o sistemasOtim.o $(LIBS)

gera_entrada: gera_entrada.c
	gcc gera_entrada.c -o gera_entrada

ajustePol.o: ajustePol.c
	gcc -c $(CFLAGS) ajustePol.c  $(LIBS)

ajustePolOtim.o: ajustePolOtim.c
	gcc -c $(CFLAGS) ajustePolOtim.c  $(LIBS)

interval.o: interval.c interval.h
	gcc -c $(CFLAGS) interval.c $(LIBS)

sistemas.o: sistemas.c sistemas.h
	gcc -c $(CFLAGS) sistemas.c $(LIBS)

sistemasOtim.o: sistemasOtim.c sistemasOtim.h
	gcc -c $(CFLAGS) sistemasOtim.c $(LIBS)

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) utils.c $(LIBS)

utilsOtim.o: utilsOtim.c utilsOtim.h
	gcc -c $(CFLAGS) utilsOtim.c $(LIBS)

removeObjects:
	-rm *.o

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
