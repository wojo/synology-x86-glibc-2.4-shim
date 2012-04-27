#include <stdint.h>
#include <linux/inotify.h>
#include <asm/unistd.h>

extern long int syscall (long int __sysno, ...) __THROW;

const char *gnu_get_libc_version(void)
{
	return "2.4";
}

int inotify_init(void)
{
	return syscall(__NR_inotify_init);
}
	
int inotify_add_watch(int fd, const char *name, uint32_t mask)
{
	return syscall(__NR_inotify_add_watch, fd, name, mask);
}

int inotify_rm_watch (int fd, uint32_t wd)
{
	return syscall(__NR_inotify_rm_watch, fd, wd);
}
