#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/syscall.h"

// Gets the process list for the current CPU.
void
main(int argc, char *argv[])
{
	getpinfo();
}