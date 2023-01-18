all: mathdemo_dynamic mathdemo_static mathdemo_nopie aslrcheck_pie aslrcheck_nopie

mathdemo_dynamic: mathdemo.c
	gcc mathdemo.c -o mathdemo_dynamic -lm

mathdemo_static: mathdemo.c
	gcc mathdemo.c -o mathdemo_static -static -lm

aslrcheck_pie: aslrcheck.c
	gcc aslrcheck.c -o aslrcheck_pie

aslrcheck_nopie: aslrcheck.c
	gcc aslrcheck.c -o aslrcheck_nopie -no-pie

clean:
	rm -f mathdemo_static mathdemo_dynamic aslrcheck_pie aslrcheck_nopie

