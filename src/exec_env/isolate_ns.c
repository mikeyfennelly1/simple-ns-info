/**
 * isolate_ns.c
 * 
 * Create orphan bash process in new namesapce.
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <semaphore.h>

#define  CHILD_STACK_SIZE (1024 * 1024)
#define PARENT_ORPHAN_FIFO "parent_child_fifo"

sem_t semFuel;

// this is the orphan that runs in a namespace of its own
int isolated_proc_function(void *arg)
{
    sem_wait(&semFuel);
    
    printf("\n\nChild process (PID: %d) namespace inode values: \n", getpid());
    print_ns_inodes();
    
    char *argv[] = {"/bin/bash", NULL};
    char *envp[] = {NULL};
    if (execve("/bin/bash", argv, envp) == -1) {
        perror("execve");
        return 1;
    };

    sem_post(&semFuel);

    sleep(2000);
}

// Creates a new process and enters a new namespace based on character passed. 
// Character is representative of desired namespace type.
// 
// The namespace flags are as specified in https://man7.org/linux/man-pages/man2/unshare.2.html
void isolate_ns(void)
{
    // malloc stack for child process
    char *stack = malloc(CHILD_STACK_SIZE);
    if (!stack)
    {
        perror("Attempted malloc for stack of child proc failed.");
        exit(1);
    }
    char *stack_top = stack + CHILD_STACK_SIZE;

    sem_init(&semFuel, 1, 0);

    // Create a child process, using unshare(2) flags to create and enter new namespaces 
    pid_t child_pid = clone(
        isolated_proc_function, 
        stack_top,
        SIGCHLD | CLONE_NEWNS | CLONE_NEWCGROUP | CLONE_NEWNET | CLONE_NEWPID | CLONE_NEWUSER | CLONE_NEWUTS | CLONE_NEWIPC,
        NULL
    );
 
    if (child_pid == -1)
    {
        perror("Error cloning.");
        free(stack);
        sem_destroy(&semFuel);
        exit(EXIT_FAILURE);
    }

    sem_post(&semFuel);

    sem_destroy(&semFuel);
    printf("Parent process (PID %d) exiting...\n", getpid());
    exit(EXIT_SUCCESS);  // parent exits to orphan child
}