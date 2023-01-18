all: exec

exec: exec.c
	gcc -Wl,-wrap=malloc exec.c my_malloc.c -o exec

clean:
	rm -f exec
