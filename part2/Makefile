all: exec_static exec_dynamic exec_dynamic_rpath

alpha_fpic.o: alpha.c alpha.h
	gcc -c -fPIC alpha.c -o alpha_fpic.o

alpha_static.o: alpha.c alpha.h
	gcc -c alpha.c -o alpha_static.o


beta_fpic.o: beta.c beta.h
	gcc -c -fPIC beta.c -o beta_fpic.o

beta_static.o: beta.c beta.h
	gcc -c beta.c -o beta_static.o


libfoo.so: alpha_fpic.o beta_fpic.o
	gcc -shared alpha_fpic.o beta_fpic.o -o libfoo.so

libbar.a: alpha_static.o beta_static.o
	ar rcs libbar.a alpha_static.o beta_static.o

exec_dynamic: exec.c alpha.h beta.h libfoo.so
	gcc exec.c -o exec_dynamic -L. -lfoo

exec_dynamic_rpath: exec.c alpha.h beta.h libfoo.so
	gcc exec.c -o exec_dynamic_rpath -L. -lfoo -Wl,-rpath,.

exec_static: exec.c alpha.h beta.h libbar.a
	gcc exec.c -o exec_static -L. -lbar

clean:
	rm -f exec_dynamic_rpath exec_dynamic exec_static libfoo.so libbar.a alpha_fpic.o beta_fpic.o alpha_static.o beta_static.o
