all: exec libmemleak.so

libmemleak.so: libmemleak.cpp
	g++ -shared -fPIC -o libmemleak.so libmemleak.cpp

exec: exec.c
	gcc exec.c -o exec

clean:
	rm -f libmemleak.so exec
