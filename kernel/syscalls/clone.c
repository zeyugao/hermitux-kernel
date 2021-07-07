#include <asm/uhyve.h>
#include <hermit/logging.h>
#include <hermit/spinlock.h>
#include <hermit/syscall.h>
#include <hermit/tasks.h>
#include <hermit/time.h>

typedef struct {
	int ret;
} __attribute__ ((packed)) uhyve_fork_t;

/* From Linux sources: */
#define CLONE_VM				0x00000100
#define CLONE_CHILD_CLEARTID	0x00200000
#define CLONE_CHILD_SETTID		0x01000000

extern void __clone_entry(struct state *s);
extern void isyscall(void);

int sys_clone(unsigned long clone_flags, void *stack, int *ptid, int *ctid,
        void *tls, struct state *state)
{
	tid_t id;

	/* fork */
	if(!(clone_flags & CLONE_VM)) {
		LOG_INFO("fork\n");
		uhyve_fork_t uhyve_args = {-1};

		uhyve_send(UHYVE_PORT_FORK, (unsigned)virt_to_phys((size_t)&uhyve_args));
		LOG_INFO("fork end ret = %d\n", uhyve_args.ret);

		if (uhyve_args.ret == 0) // Child
		{
			wrmsr(MSR_EFER, rdmsr(MSR_EFER) | EFER_LMA | EFER_LME | EFER_SCE);
			wrmsr(MSR_STAR, (/*0x1BULL*/ 0x08ULL << 48) | (0x08ULL << 32));
			wrmsr(MSR_LSTAR, (size_t) &isyscall);
			//  clear IF flag during an interrupt
			wrmsr(MSR_SYSCALL_MASK, EFLAGS_TF|EFLAGS_DF|EFLAGS_IF|EFLAGS_AC|EFLAGS_NT);
		}
		
		return uhyve_args.ret;
	}

	/* To understand how set/clear_child_tidwork, see the man page for
	 * set_tid_address */
	void *set_child_tid = (clone_flags & CLONE_CHILD_SETTID) ? ctid : NULL;
	void *clear_child_tid = (clone_flags & CLONE_CHILD_CLEARTID) ? ctid : NULL;

    /* We will restore fs to the right value when returning in the child */
    state->fs = (uint64_t)tls;

	/* clone_task will take care of copyign state on the stack of the created
     * thread and pass it as the parameter of __clone_entry so that we can be
     * reetrant */
    int ret = clone_task(&id, (int(*)(void *))__clone_entry, NULL,
            per_core(current_task)->prio, set_child_tid, clear_child_tid,
            state);

	if(ret)
		return ret;

	if(ptid)
		*(unsigned int *)ptid = id;

	/* TODO this is probably not the responsibility of the kernel */
	if(clone_flags & CLONE_CHILD_SETTID)
		if (ctid)
			*(int *)ctid = id;

	return id;
}

