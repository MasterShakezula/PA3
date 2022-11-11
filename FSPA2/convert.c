


#define MAX_LINES 1000
#define MAX_LEN 1000
#include<stdio.h>
#include "convert.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_LINE_LENGTH 1000
#define MAX_CELL_LENGTH 20
typedef enum { INT, DOUBLE, STRING } type;

char* normalizerInt(char* input) {
	char* output = (char*)malloc(26);
	double double_value;
	int int_value;
	type input_type = INT;
	int i = 0;
	
	if (input_type == INT)
		sscanf(input, "%d", &int_value);
	
	if (input_type == INT)
		sprintf(output, "%25x", int_value);
	
	
	return output;
}

char* lineptr[MAX_LINES];

int results[MAX_LINES];

char* strstr_fully_matched(char* haystack, char* needle) {
	char* rv;

	char padded_needle[strlen(needle) + 3];

	padded_needle[0] = ' ';

	strcpy(padded_needle + 1, needle);

	padded_needle[strlen(needle) + 1] = ' ';

	padded_needle[strlen(needle) + 2] = '\0';

	if (!strncmp(haystack, padded_needle + 1, strlen(needle) + 1))
		return haystack;//needle is at the beginning

	if ((rv = strstr(haystack, padded_needle)) != NULL)
		return rv + 1;//needle is at the middle.

	padded_needle[strlen(needle) + 1] = '\0';

	if ((rv = strstr(haystack, padded_needle)) != NULL)
		return rv + 1;//needle is at the end.
}

char* strcasestr_fully_matched(char* haystack, char* needle) {
	char* rv;

	char padded_needle[strlen(needle) + 3];

	padded_needle[0] = ' ';

	strcpy(padded_needle + 1, needle);

	padded_needle[strlen(needle) + 1] = ' ';

	padded_needle[strlen(needle) + 2] = '\0';

	if (!strncasecmp(haystack, padded_needle + 1, strlen(needle) + 1))
		return haystack;//needle is at the beginning

	if ((rv = strcasestr(haystack, padded_needle)) != NULL)
		return rv + 1;//needle is at the middle.

	padded_needle[strlen(needle) + 1] = '\0';

	if ((rv = strcasestr(haystack, padded_needle)) != NULL)
		return rv + 1;//needle is at the end.
}

int getline2(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;

		i++;
	}

	s[i] = '\0';

	return i;
}

int readlines(char** lineptr, int maxlines) {
	int len, nlines;

	char* p, line[MAX_LEN];

	nlines = 0;

	while ((len = getline2(line, MAX_LEN)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;

		else {
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';

			strcpy(p, line);

			lineptr[nlines++] = p;
		}
	return nlines;
}

int main(int argc, char** argv)
{
	
	char* line[MAX_LINE_LENGTH];
	char* cell[MAX_CELL_LENGTH];
	//char* rest;
	int c;
	int hexadecimal, remove_white_space, scientific_notation, non_numerical_trunc = 0;
	// x, c, e, s
	int input, output = 0; //i, o

	

	//printf("%s\n", pattern);

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
			case 'c':
				remove_white_space = 1;
				break;
			case 'x':
				hexadecimal = 1;				
				break;
			case 'e':				
				scientific_notation = 1;
				break;
			case 's':				
				non_numerical_trunc = 1;
				break;
				
			case 'i':
			{
				printf("peepee");
				char* input_format = *++argv;
				if (strcmp(input_format, "txt") == 0)
				{
					argc -= 2;
					if (argc > 0) *++argv;
				}
				else if (strcmp(input_format, "csv") == 0)
				{
					input = 1;
					argc -= 2;
					if (argc > 0) ++argv;
				}
				else printf("Invalid Input \n");
				break; // test
			}
				
			case 'o':								
			{
				char* output_format = *++argv; //change name				

				if (strcmp(output_format, "txt") == 0) {

					output = 1;

					argc -= 2;

					if (argc > 0) *++argv;
				}

				else if (strcmp(output_format, "csv") == 0) {

					argc -= 2;

					if (argc > 0) *++argv;

				}

				else printf("Invalid Input\n");

				break;
			default:
				printf("find: illeal option. \n");
				argc = 0;
				break;
			}
				
			}
		}
	}
	


	
	
	if (!(input) && !(output)) { // txt to csv
		while (fgets(line, MAX_LINE_LENGTH, stdin)) {
			while (sscanf(line, "%[^\t]\t%[^\n]\n", cell, line) == 2)//(strchr(rest, ',')){
			{
				if (hexadecimal)
				{
					if (isdigit(cell))
					{
						cell = normalizerInt(cell);

					}

				} // this whole body is experimental
				printf("%s,", cell);//internal cell followed by tab
			}
				
			printf("%s\n", cell);//last cell followed by new line
		}
		
	}
	else if ((input) && (output)) { // csv to txt
		while (fgets(line, MAX_LINE_LENGTH, stdin)) {
			while (sscanf(line, "%[^,],%[^\n]\n", cell, line) == 2)//(strchr(rest, ',')){
				printf("%s\t", cell);//internal cell followed by tab
			printf("%s\n", cell);//last cell followed by new line
		}
		
	}
	else  { // if both are the same file format, txt and txt or csv and csv
		char c;
		while ((c = getchar()) != EOF)
			putchar(c);
	}
	


	
}
