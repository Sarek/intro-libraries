all: exec libmemleak.so

exec: exec.cpp
	g++ exec.cpp -o exec

libmemleak.so: libmemleak.cpp
	g++ -shared -fPIC -o libmemleak.so libmemleak.cpp

clean:
	rm -f libmemleak.so
