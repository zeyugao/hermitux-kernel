PREFIX=../build/local_prefix/home/elsa/Code/hermitux-kernel

all: 1.out

1.out: 1.c
	g++ 1.c -o 1.out -static

run: 1.out
	sudo HERMIT_ISLE=uhyve HERMIT_TUX=1 HERMIT_VERBOSE=1 \
		../tools/build/proxy \
		../build/local_prefix/home/elsa/Code/hermitux-kernel/prefix/x86_64-hermit/extra/tests/hermitux \
		1.out

clean:
	rm *.out