
#include <stdio.h>
#include <unistd.h>

int myfork()
{
    int ret;
    __asm__(
        "mov $57, %%rax\n\t"
        "syscall\n\t"
        "mov %%eax, %0"
        : "=r" (ret)
    );
    return ret;
}

int main()
{
    int ret = myfork();

    if (ret != 0)
    {
        printf("prog: Parent, pid = %d\n", ret);
    }
    else
    {
        printf("prog: Child\n");
    }
}