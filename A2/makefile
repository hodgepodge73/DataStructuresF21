CC = clang
CFLAGS = -Wall -std=c99 -pedantic

ALL:  demo1 a2test1 a2test2 a2test3 a2test4 a2test5 a2test6 a2test7 a2test8

clean:  
	rm -i demo1 a2test1 a2test2 a2test3 a2test4 a2test5 a2test6 a2test7 a2test8 *.o

# override the implicit compilation rules for executables so that we can
# override them with new ones
%: %.o
%: %.c

# create executables by linking %.o file with the two supporting .o files
%: %.o array.o memsys.o
	$(CC) $(CFLAGS) $^ -o $@

# create .o files by compiling the .c files
%.o : %.c memsys.h array.h
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm *.o 