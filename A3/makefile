CC=clang
CFLAGS=-std=c99 -Wall -pedantic
EXECS=a3test1 a3test2l #a3test2a #a3test3

all: $(EXECS)

clean:
	rm -i $($EXECS) *.o

# override the implicit compilation rules for executables so that we can
# override them with new ones
%: %.o
%: %.c



# compile a3test2.c using the ARRAY flag to use array operations
#a3test2a.o:  a3test2.c array.h memsys.h
#	$(CC) $(CFLAGS) -DARRAY -c a3test2.c -o a3test2a.o

# compile a3test2.c using the LIST flag to use array operations
a3test2l.o:  a3test2.c list.h memsys.h
	$(CC) $(CFLAGS) -DLIST -c a3test2.c -o a3test2l.o

# create .o files by compiling the .c files
%.o : %.c memsys.h array.h list.h
	$(CC) -c $(CFLAGS) $< -o $@

a3test1: a3test1.o list.o memsys.o memsys.h list.h
	$(CC) $(CFLAGS) memsys.o list.o a3test1.o -o a3test1

a3test2a: a3test2a.o array.o memsys.o memsys.h array.h
	$(CC) $(CFLAGS) memsys.o array.o a3test2a.o -o a3test2a

a3test2l: a3test2l.o list.o memsys.o memsys.h list.h
	$(CC) $(CFLAGS) memsys.o list.o a3test2l.o -o a3test2l
