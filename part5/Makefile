all: exec_link exec_nolink

libfoo.so: foo.c
	gcc -shared foo.c -o libfoo.so

exec_link: exec.cpp libfoo.so
	g++ exec.cpp -o exec_link -L. -lfoo -Wl,-rpath,.

exec_nolink: exec.cpp
	g++ exec.cpp -o exec_nolink

clean:
	rm -f exec_nolink exec_link libfoo.so
