# PROGRAMA
    PROG = perfEG

# Compilador
	LIKWID_HOME = /home/soft/likwid
    CC     = gcc
    CFLAGS = -Wall -g -O3 -mavx -march=native -DLIKWID_PERFMON -I${LIKWID_HOME}/include 
    LIBS = -L${LIKWID_HOME}/lib -llikwid -lm

# Lista de arquivos para distribuição
    DISTFILES = *.c *.h LEIAME* Makefile teste*.in script.sh
    DISTDIR = msac22-tmb22

.PHONY: all clean purge dist

all: perfEG

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

perfEG: perfEG.o metodos.o utils.o
	gcc -o perfEG perfEG.o metodos.o utils.o $(LIBS)

perfEG.o: perfEG.c
	gcc -c $(CFLAGS) perfEG.c  $(LIBS)

metodos.o: metodos.c metodos.h
	gcc -c $(CFLAGS) metodos.c $(LIBS)

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) utils.c $(LIBS)

removeObjects:
	-rm *.o

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)