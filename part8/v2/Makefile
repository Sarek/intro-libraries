all: libfoo.so

foo.o: foo.c
	gcc -c -fPIC foo.c

libfoo.so: foo.o
	gcc -shared -o libfoo.so foo.o -Wl,--version-script,foo.map

clean:
	rm -f foo.o libfoo.so