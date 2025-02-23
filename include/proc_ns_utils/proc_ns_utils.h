#include "../types/ns_types.h"

// get namespace inode values for this process
//
// returns as NAMESPACE_INODES*
NAMESPACE_INODES* get_ns_inodes(void);

// print namespace indoes for this process to STDOUT
void print_ns_inodes();