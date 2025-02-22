#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include "../include/ns_vals.h"
#include "../misc_file_utils/misc_file_utils.c"

// enters the execution environment of the target process
// via manipulating it's vals of ns_proxy.
int container_reaper(const unsigned long ipc_ns_inode, const unsigned int target_pid)
{
    char* target_pid_proc_dir = ;
}

// When called, process is initialised a userland_lifecycle_manger
// process is created for that container
//
// when this userland_lifecycle_manager process receives a SIGTERM
// it forks a reaper process into the target exec environment
// and kills target container.
int userland_lifecycle_manager(const unsigned int target_pid, const NAMESPACE_INODES container_ns_inodes)
{
    signal(SIGTERM, kill_container(container_ns_inodes));
    while (1)
    {
        printf("lifecycle_manager process (PID: %d) waiting for SIGTERM\n", getpid());
    }
}