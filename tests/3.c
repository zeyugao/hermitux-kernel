int main()
{
    __asm__(
        "mov $57, %rax\n\t"
        "syscall"
    );
}