#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void *run;

int main()
{
    int fd = open("./a", O_RDWR);
    printf("open %x\n", fd);
    run = mmap(NULL, sizeof(int) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    *(int *)run = 10;
    printf("open %x\n", fd);
    // run = mmap(NULL, sizeof(int) * 10, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    int ret = fork();
    printf("fork ret = %d\n", ret);

    *(int *)run = 10;
    printf("fork ret = %d\n", ret);
    if (ret != 0)
    {
        printf("Parent: %d\n", *(int *)run);
        getchar();
        printf("Parent: %d\n", *(int *)run);
    }
    else
    {
        printf("Child: %d\n", *(int *)run);
        *(int *)run = 20;
        printf("Child: %d\n", *(int *)run);
    }
}
