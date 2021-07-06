#include <hermit/logging.h>
#include <hermit/syscall.h>

int sys_fork(void)
{
    LOG_INFO("fork");
    return 1;
}
