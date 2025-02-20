#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "./ns_vals.h"

int main(void)
{
    NAMESPACE_INODES* ns_inodes = get_ns_inodes();
    print_ns_inodes(ns_inodes);
    sleep(1000);
}