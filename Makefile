Demo: kernel.c runtest.c
	gcc -o runtest kernel.c runtest.c -Wall -g3

clean:
	rm runtest
