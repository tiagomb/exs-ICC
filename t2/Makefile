# PROGRAMA
    PROG = ajustePol

# Compilador
	LIKWID_HOME = /home/soft/likwid
    CC     = gcc
    CFLAGS = -Wall -g -O3 -mavx -march=native -I${LIKWID_HOME}/include -DLIKWID_PERFMON 
    LIBS = -L${LIKWID_HOME}/lib -llikwid -lm

# Lista de arquivos para distribuição
    DISTFILES = *.c *.h LEIAME* Makefile teste*.in script.sh
    DISTDIR = msac22-tmb22

.PHONY: all clean purge dist

all: ajustePol

clean:
	@echo "Limpando tudo ..."
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

ajustePol: ajustePol.o interval.o utils.o sistemas.o
	gcc $(CFLAGS) -o ajustePol ajustePol.o interval.o utils.o sistemas.o $(LIBS)

ajustePol.o: ajustePol.c
	gcc -c $(CFLAGS) ajustePol.c  $(LIBS)

interval.o: interval.c interval.h
	gcc -c $(CFLAGS) interval.c $(LIBS)

sistemas.o: sistemas.c sistemas.h
	gcc -c $(CFLAGS) sistemas.c $(LIBS)

utils.o: utils.c utils.h
	gcc -c $(CFLAGS) utils.c $(LIBS)

removeObjects:
	-rm *.o

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
