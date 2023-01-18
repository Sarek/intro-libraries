all: exec_v1 exec_v2 exec_flex_v1 exec_flex_v2

libfoo_v1:
	pushd v1 && $(MAKE) all && popd

libfoo_v2:
	pushd v2 && $(MAKE) all && popd

exec_v1: libfoo_v1 exec.c
	gcc -o exec_v1 exec.c -Wl,-rpath,./v1 -I./v1 -L./v1 -lfoo

exec_v2: libfoo_v2 exec.c
	gcc -o exec_v2 exec.c -Wl,-rpath,./v2 -I./v2 -L./v2 -lfoo

exec_flex_v1: libfoo_v1 exec.c
	gcc -o exec_flex_v1 exec.c -I./v1 -L./v1 -lfoo

exec_flex_v2: libfoo_v2 exec.c
	gcc -o exec_flex_v2 exec.c -I./v2 -L./v2 -lfoo

clean:
	pushd v1 && $(MAKE) clean && popd
	pushd v2 && $(MAKE) clean && popd
	rm -f exec_v1 exec_v2 exec_flex_v1 exec_flex_v2