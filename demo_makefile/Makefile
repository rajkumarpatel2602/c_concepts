# Final executable
main.exe : 	main.o libfoo1.a libfoo2.a
			gcc main.o -L . -lfoo1 -lfoo2 -o main.exe

# Build main file
main.o : main.c
		gcc -c main.c -o main.o -I lib1/headers -I lib2/headers # No need to share makefile, one can add header paths

# Generate static library :: libfoo1.a
libfoo1.a : libfoo1.o
		 	ar rs -o libfoo1.a libfoo1.o
libfoo1.o : lib1/foo1.c
			gcc -c lib1/foo1.c -o libfoo1.o

# Generate static library :: libfoo2.a
libfoo2.a : libfoo2.o
		 	ar rs -o libfoo2.a libfoo2.o
libfoo2.o : lib2/foo2.c
		 	gcc -c lib2/foo2.c -o libfoo2.o

# Clean up built files
clean:
	rm -rf *.o *.a *.gch *.exe
