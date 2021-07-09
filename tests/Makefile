PREFIX=../build/local_prefix/home/elsa/Code/hermitux-kernel/prefix
HERMIT_DEBUG=0
PROXY=${PREFIX}/bin/proxy
KERNEL=${PREFIX}/x86_64-hermit/extra/tests/hermitux

%.out: %.c
	gcc $< -o $@ -static

run%: %.out
	sudo -E HERMIT_ISLE=uhyve HERMIT_TUX=1 HERMIT_VERBOSE=1 HERMIT_DEBUG=${HERMIT_DEBUG} \
		${PROXY} \
		${KERNEL} \
		$<

run_test:
	sudo -E HERMIT_ISLE=uhyve HERMIT_TUX=1 HERMIT_VERBOSE=1 HERMIT_DEBUG=${HERMIT_DEBUG} \
		${PROXY} \
		${KERNEL} \
		/home/elsa/Code/hermitux-rewrite/syscall_rewriter/src/test

clean:
	rm *.out
