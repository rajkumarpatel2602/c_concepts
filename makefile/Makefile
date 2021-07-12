

main.exe : 	main.o libfoo1.a libfoo2.a
			gcc main.o -o main.exe -L . -lfoo1 -L . -lfoo2

main.o : main.c foo.h
		gcc -c main.c foo.h

libfoo1.a : lib1/foo1.c 
		 	ar rs -o libfoo1.a lib1/foo1.c

libfoo2.a : lib2/foo2.c
		 	ar rs -o libfoo2.a lib2/foo2.c
			
clean:
		rm -rf *.o *.a *.gch *.exe
