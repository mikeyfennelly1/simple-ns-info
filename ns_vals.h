#ifndef NS_VALS_H
#define NS_VALS_H

typedef struct {
    unsigned long ipc;
    unsigned long uts;
    unsigned long mnt;
    unsigned long pid;
    unsigned long cgroup;
    unsigned long net;
} NAMESPACE_INODES;

typedef struct {
    char* ipc;
    char* uts;
    char* mnt;
    char* pid;
    char* cgroup;
    char* net;
} NAMESPACE_PATHS;

NAMESPACE_INODES* get_ns_inodes(void);
void print_ns_inodes(NAMESPACE_INODES* ns_inodes);

#endif
