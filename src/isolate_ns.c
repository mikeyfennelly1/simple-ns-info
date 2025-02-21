/**
 * unshare.c
 * 
 * Use unshare(2) syscall to enter new namespaces.
 *      see https://man7.org/linux/man-pages/man2/unshare.2.html
 * 
 *
 * By default, a new namespace is cleaned up if no processes reside in it.
 * Whether you use fork/exec or just unshare(), result is the same.
 *
 * Author: Mikey Fennelly
 */

 #ifndef _GNU_SOURCE
 #define _GNU_SOURCE
 #endif

#include <sched.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include "../include/ns_vals.h"

#ifndef STACK_SIZE
#define  STACK_SIZE (1024 * 1024)
#endif

int child_function(void *arg)
{
    printf("\n\n");
    printf("Child process (PID: %d) namespace inode values: \n", getpid());
    print_ns_inodes();
    
    char *argv[] = {"/bin/bash", NULL};
    char *envp[] = {NULL};
    if (execve("/bin/bash", argv, envp) == -1) {
        perror("execve");
        return 1;
    };
    
    sleep(2000);
}

// Creates a new process and enters a new namespace based on character passed. 
// Character is representative of desired namespace type.
// 
// The namespace flags are as specified in https://man7.org/linux/man-pages/man2/unshare.2.html
//
//  returns -1 if failure, 0 if success

void isolate_ns(void)
{
    // malloc stack for child process
    char *stack = malloc(STACK_SIZE);
    if (!stack)
    {
        perror("Attempted malloc for stack of child proc failed.");
        exit(1);
    }
    char *stack_top = stack + STACK_SIZE;

    // Create a child process, using unshare(2) flags to create and enter new namespaces 
    pid_t child_pid = clone(
        child_function, 
        stack_top,
        SIGCHLD |
        CLONE_NEWNS | CLONE_NEWCGROUP | CLONE_NEWNET | CLONE_NEWPID | CLONE_NEWUSER | CLONE_NEWUTS, NULL);
    if (child_pid == -1)
    {
        perror("Error cloning.");
        free(stack);
        exit(EXIT_FAILURE);
    }

    printf("Parent process (PID %d) exiting...\n", getpid());
    exit(EXIT_SUCCESS);  // parent exits to orphan child
}