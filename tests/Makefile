PREFIX=../build/local_prefix/home/elsa/Code/hermitux-kernel
HERMIT_DEBUG=0

%.out: %.c
	gcc $< -o $@ -static

run%: %.out
	sudo HERMIT_ISLE=uhyve HERMIT_TUX=1 HERMIT_VERBOSE=1 HERMIT_DEBUG=${HERMIT_DEBUG} \
		../tools/build/proxy \
		../build/local_prefix/home/elsa/Code/hermitux-kernel/prefix/x86_64-hermit/extra/tests/hermitux \
		$<

clean:
	rm *.out
