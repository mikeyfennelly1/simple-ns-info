/**
 * ns_vals.c
 * 
 * Compare the namespaces that a process is in by reading inode values.
 * 
 * Author: Mikey Fennelly
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/ns_vals.h"

// gets paths for hardlinks to namespace inodes
// in /proc directory for this process
//
// returns as type NAMESPACE_PATHS*
char* get_proc_self_ns_path(void)
{
    // allocate mem for final val
    char* proc_self_ns = malloc(40);
    if (!proc_self_ns) return NULL; 
 
    // append '/proc/' to final string area
    char* proc_self_ns_string = "/proc/";
    sprintf(proc_self_ns, "%s", proc_self_ns_string);

    // get pid as string
    char pid[10];
    int pid_int = getpid();
    sprintf(pid, "%d", pid_int);

    // append pid to final mem area
    strcat(proc_self_ns, pid);
    strcat(proc_self_ns, "/ns");

    return proc_self_ns;
}

char* append_string(const char* base, const char* to_append) {
    size_t new_len = strlen(base) + strlen(to_append) + 1;
    char* new_str = malloc(new_len);
    if (!new_str) {
        printf("Failed to allocate memory\n");
        exit(1);
    }
    strcpy(new_str, base);
    strcat(new_str, to_append);
    return new_str;
}

NAMESPACE_PATHS* get_namespace_paths(void) {
    NAMESPACE_PATHS* ns_paths = (NAMESPACE_PATHS*) malloc(sizeof(NAMESPACE_PATHS));
    char* base_path = get_proc_self_ns_path();

    ns_paths->ipc = append_string(base_path, "/ipc");
    ns_paths->pid = append_string(base_path, "/pid");
    ns_paths->cgroup = append_string(base_path, "/cgroup");
    ns_paths->mnt = append_string(base_path, "/mnt");
    ns_paths->uts = append_string(base_path, "/uts");
    ns_paths->net = append_string(base_path, "/net");

    free(base_path);  // Clean up base path

    return ns_paths;
}

// gets inode value for file at <path>
unsigned long get_inode_value(char* path)
{
    struct stat filestat;
    stat(path, &filestat);
    return (unsigned long)filestat.st_ino;
} 

// returns NAMESPACE_INODES for current process
NAMESPACE_INODES* get_ns_inodes(void)
{
    NAMESPACE_PATHS* ns_paths = get_namespace_paths();
    NAMESPACE_INODES* ns_inodes = (NAMESPACE_INODES*) malloc(sizeof(NAMESPACE_INODES));

    ns_inodes->cgroup = get_inode_value(ns_paths->cgroup);
    ns_inodes->ipc = get_inode_value(ns_paths->ipc);
    ns_inodes->net = get_inode_value(ns_paths->net);
    ns_inodes->mnt = get_inode_value(ns_paths->mnt);
    ns_inodes->uts = get_inode_value(ns_paths->uts);    
    ns_inodes->pid = get_inode_value(ns_paths->pid);

    return ns_inodes;
}

void print_ns_inodes()
{
    NAMESPACE_INODES* ns_inodes = get_ns_inodes();

    printf("IPC namespace inode: %ld\n", ns_inodes->ipc);
    printf("MNT namespace inode: %ld\n", ns_inodes->mnt);
    printf("PID namespace inode: %ld\n", ns_inodes->pid);
    printf("UTS namespace inode: %ld\n", ns_inodes->uts);
    printf("CGROUP namespace inode: %ld\n", ns_inodes->cgroup);
    printf("NET namespace inode: %ld\n", ns_inodes->net);
}