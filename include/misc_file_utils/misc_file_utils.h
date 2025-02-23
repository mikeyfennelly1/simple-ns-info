// appends a string <to_append> to string <base>
//
// returns pointer to new string on heap
char* append_string(const char* base, const char* to_append);

// given <char* strings[]> and <total_num_strings>, returns a 
// single string, with all values of <strings[]> concatenated
char* concatenate_strings(char* strings[], int total_num_strings);

// gets inode value for file at <path>
//
// returns this inode value as unsigned long
unsigned long get_inode_value(char* path);