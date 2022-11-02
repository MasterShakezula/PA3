#include<stdlib.h>
#include<string.h>
#include<stdio.h> 
#define _GNU_SOURCE        

char* strcasestr(const char* haystack, const char* needle);

int strncasecmp(const char* string1, const char* string2, size_t count);

char* strstr_fully_matched(char* haystack, char* needle);

char* strcasestr_fully_matched(char* haystack, char* needle);

void print_results(char* pattern, int case_sense, int matched, int first_occurrence, int numbered, int sorted, int partial, int reversed, int no_of_results);

extern char*lineptr[];

extern int results[];
