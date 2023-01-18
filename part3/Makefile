all: exec_static_foobar exec_static_barfoo exec_dynamic_foobar exec_dynamic_barfoo

exec_static_foobar: exec.c foobar.h libfoo_static.a libbar_static.a
	gcc exec.c -o exec_static_foobar -L. -lfoo_static -lbar_static

exec_static_barfoo: exec.c foobar.h libfoo_static.a libbar_static.a
	gcc exec.c -o exec_static_barfoo -L. -lbar_static -lfoo_static

libfoo_static.a: foo.c
	gcc -c foo.c -o foo_static.o
	ar rcs libfoo_static.a foo_static.o

libbar_static.a: bar.c
	gcc -c bar.c -o bar_static.o
	ar rcf libbar_static.a bar_static.o


exec_dynamic_foobar: exec.c foobar.h libfoo_dynamic.so libbar_dynamic.so
	gcc exec.c -o exec_dynamic_foobar -L. -lfoo_dynamic -lbar_dynamic -Wl,-rpath,.

exec_dynamic_barfoo: exec.c foobar.h libfoo_dynamic.so libbar_dynamic.so
	gcc exec.c -o exec_dynamic_barfoo -L. -lbar_dynamic -lfoo_dynamic -Wl,-rpath,.

libfoo_dynamic.so: foo.c
	gcc -shared foo.c -o libfoo_dynamic.so

libbar_dynamic.so: bar.c
	gcc -shared bar.c -o libbar_dynamic.so

clean:
	rm -f exec_static_foobar exec_static_barfoo libfoo_static.a libbar_static.a exec_dynamic_foobar exec_dynamic_barfoo libfoo_dynamic.so libbar_dynamic.so
