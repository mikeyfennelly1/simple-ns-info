/**
 * misc_file_utils.c
 * 
 * Miscellaneous utility functions for working with file paths.
 * 
 * Author: Mikey Fennelly
 * */

#include <stddef.h>
#include <sys/stat.h>

// appends a string <to_append> to string <base>
//
// returns pointer to new string on heap
char* append_string(const char* base, const char* to_append)
{
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

// given <char* strings[]> and <total_num_strings>, returns a 
// single string, with all values of <strings[]> concatenated
char* concatenate_strings(char* strings[], int total_num_strings)
{
    char* base = strings[0];
    for (int i = 1; i < total_num_strings; i++)
    {
        append_string(base, strings[i]);
    }
    return base;
}

// gets inode value for file at <path>
//
// returns this inode value as unsigned long
unsigned long get_inode_value(char* path)
{
    struct stat filestat;
    stat(path, &filestat);
    return (unsigned long) filestat.st_ino;
} 
