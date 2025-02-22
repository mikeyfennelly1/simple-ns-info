#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/ns_vals.h"
#include "../include/isolate_ns.h"

int main(int argc, char *argv[])
{
    isolate_ns();    
}