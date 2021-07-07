
#include <stdio.h>

int main()
{
    // outportl(0x123, 0);
    __asm__(
        "mov $57, %rax\n\t"
        "syscall"
    );
    printf("asdfadfasdf\n");
}