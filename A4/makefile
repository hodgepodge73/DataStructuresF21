CC=clang
CFLAGS=-std=c99 -Wall -pedantic
EXECS=a4ttest a4test2

all: $(EXECS)


# override the implicit compilation rules for executables so that we can
# override them with new ones
%: %.o
%: %.c



# compile a3test2.c using the ARRAY flag to use array operations
a4ttest.o:  a4ttest.c tree.h memsys.h
	$(CC) $(CFLAGS) -c a4ttest.c -o a4ttest.o
a4test2.o:  a4test2.c tree.h memsys.h
	$(CC) $(CFLAGS) -c a4test2.c -o a4test2.o

# create .o files by compiling the .c files
%.o : %.c memsys.h tree.h
	$(CC) -c $(CFLAGS) $< -o $@

a4ttest: a4ttest.o tree.o memsys.o memsys.h tree.h
	$(CC) $(CFLAGS) memsys.o tree.o a4ttest.o -o a4ttest
a4test2: a4test2.o tree.o memsys.o memsys.h tree.h
	$(CC) $(CFLAGS) memsys.o tree.o a4test2.o -o a4test2


clean:
	rm -i *.o $(EXECS)