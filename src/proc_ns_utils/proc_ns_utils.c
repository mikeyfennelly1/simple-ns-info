/**
 * proc_ns_utils.c
 * 
 * Utilities for interacting with the /proc/<pid>/ns directory.
 * 
 * Author: Mikey Fennelly
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../include/proc_ns_utils/proc_ns_utils.h"
#include "../misc_file_utils/misc_file_utils.h"

// gets paths to hardlinks to namespace inodes for process of PID <pid>
//
// returns as type NAMESPACE_PATHS*
char* get_proc_ns_path(__pid_t pid)
{
    // allocate mem for final val
    char* proc_self_ns = malloc(40);
    if (!proc_self_ns)
    {
        return NULL;
    }
 
    // append '/proc/' to final string
    char* proc_self_ns_string = "/proc/";
    sprintf(proc_self_ns, "%s", proc_self_ns_string);

    // get pid as string
    char pid_str[10];
    sprintf(pid, "%d", pid);

    // append pid to final mem area
    strcat(proc_self_ns, pid_str);
    strcat(proc_self_ns, "/ns");

    return proc_self_ns;
}

NAMESPACE_PATHS* get_proc_ns_paths(__pid_t target_pid) {
    __pid_t this_proc_pid = getpid();
    char* proc_ns_path = get_proc_ns_path(this_proc_pid);

    NAMESPACE_PATHS* ns_paths = (NAMESPACE_PATHS*) malloc(sizeof(NAMESPACE_PATHS));

    ns_paths->ipc = append_string(proc_ns_path, "/ipc");
    ns_paths->pid = append_string(proc_ns_path, "/pid");
    ns_paths->cgroup = append_string(proc_ns_path, "/cgroup");
    ns_paths->mnt = append_string(proc_ns_path, "/mnt");
    ns_paths->uts = append_string(proc_ns_path, "/uts");
    ns_paths->net = append_string(proc_ns_path, "/net");

    return ns_paths;
}

// returns NAMESPACE_INODES for current process
NAMESPACE_INODES* get_ns_inodes(void)
{
    int this_pid = getpid();
    NAMESPACE_PATHS* ns_paths = get_proc_ns_paths(this_pid);
    NAMESPACE_INODES* ns_inodes = (NAMESPACE_INODES*) malloc(sizeof(NAMESPACE_INODES));

    ns_inodes->cgroup = get_inode_value(ns_paths->cgroup);
    ns_inodes->ipc = get_inode_value(ns_paths->ipc);
    ns_inodes->net = get_inode_value(ns_paths->net);
    ns_inodes->mnt = get_inode_value(ns_paths->mnt);
    ns_inodes->uts = get_inode_value(ns_paths->uts);    
    ns_inodes->pid = get_inode_value(ns_paths->pid);

    return ns_inodes;
}

void print_ns_inodes(void)
{
    NAMESPACE_INODES* ns_inodes = get_ns_inodes();

    printf("IPC namespace inode: %ld\n", ns_inodes->ipc);
    printf("MNT namespace inode: %ld\n", ns_inodes->mnt);
    printf("PID namespace inode: %ld\n", ns_inodes->pid);
    printf("UTS namespace inode: %ld\n", ns_inodes->uts);
    printf("CGROUP namespace inode: %ld\n", ns_inodes->cgroup);
    printf("NET namespace inode: %ld\n", ns_inodes->net);
}