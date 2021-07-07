
#include <unistd.h>
#include <stdio.h>

int main()
{
    int ret;
    __asm__(
        "mov $57, %%rax\n\t"
        "syscall\n\t"
        "mov %%eax, %0"
        : "=r" (ret)
    );

    if (ret != 0)
    {
        printf("prog: Parent, pid = %d\n", ret);
    }
    else
    {
        printf("prog: Child\n");
    }
}