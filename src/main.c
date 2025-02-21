#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/ns_vals.h"
#include "../include/isolate_ns.h"

int main(void)
{
    NAMESPACE_INODES* ns_inodes = get_ns_inodes();
    printf("Namespace inode values before: \n");
    print_ns_inodes(ns_inodes);

    isolate_ns();    

    sleep(1000);
}