
CC = gcc
CFLAGS = -Wall -j4
LDFLAGS = 

SRCDIR = src
OBJDIR = obj
BINDIR = bin


$(BINDIR)/encodeInput: $(OBJDIR)/sadA2.o 
	${CC} ${LDFLAGS} $^ -o $@

$(OBJDIR)/sadA2.o : $(SRCDIR)/sadA2.c $(SRCDIR)/sadA2.h
	${CC} ${CFLAGS} -c $< -o $@

.PHONY : clean tar
clean:
	rm -r obj/*.o
	rm -r bin/*

tar:
	tar -cvzf sadA2.tar.gz .
