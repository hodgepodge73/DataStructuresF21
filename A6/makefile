CC=clang
CFLAGS=-std=c99 -Wall -pedantic
EXECS=a6

all: $(EXECS)

clean:
	rm -i $($EXECS) *.o

%: %.o
%: %.c


a6:  a6.o hash.h hash.o
	$(CC) $(CFLAGS) a6.o hash.o -o a6

# create .o files by compiling the .c files
%.o : %.c hash.h
	$(CC) -c $(CFLAGS) $< -o $@
