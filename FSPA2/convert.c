
//	}else{
//		fprintf(stderr, "convert: fatal error! usage: -i in_ext -o out_ext\n");
//		exit(1);
//	}
//	fprintf(stderr, "convert: in format is %s, out format is %s\n", in_ext, out_ext);
//	if(!strcmp(in_ext, "csv") && !strcmp(out_ext, "txt")){
//		while(fgets(line, MAX_LINE_LENGTH, stdin)){
//			while(sscanf(line,"%[^,],%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
//				printf("%s\t", cell);//internal cell followed by tab
//			printf("%s\n",cell);//last cell followed by new line
//		}
//	}else if(!strcmp(in_ext, "txt") && !strcmp(out_ext, "csv")){
//		while(fgets(line, MAX_LINE_LENGTH, stdin)){
//			while(sscanf(line,"%[^\t]\t%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
//				printf("%s,", cell);//internal cell followed by tab
//			printf("%s\n",cell);//last cell followed by new line
//		}
//	}else if (!strcmp(in_ext, out_ext)){
//		char c;
//		while((c=getchar())!= EOF)
//			putchar(c);
//	}else{
//		fprintf(stderr, "convert: fatal error! usage: -i in_ext -o out_ext and only supported extensions are csv and txt\n");
//		exit(1);
//	}
//
//
//
//}


#define MAX_LINES 1000
#define MAX_LEN 1000
#include<stdio.h>
#include "convert.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_LINE_LENGTH 1000
#define MAX_CELL_LENGTH 20

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
	
	char line[MAX_LINE_LENGTH];
	char cell[MAX_CELL_LENGTH];
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
	/*if (argc != 1)
		printf("Usage: find pattern\n");*/
	
	
		/*fprintf(stderr, "convert: fatal error! usage: -i in_ext -o out_ext\n");
		exit(1);*/
	
	
	if (!(input) && !(output)) {
		while (fgets(line, MAX_LINE_LENGTH, stdin)) {
			while (sscanf(line, "%[^\t]\t%[^\n]\n", cell, line) == 2)//(strchr(rest, ',')){
				printf("%s,", cell);//internal cell followed by tab
			printf("%s\n", cell);//last cell followed by new line
		}
		
	}
	else if ((input) && (output)) {
		while (fgets(line, MAX_LINE_LENGTH, stdin)) {
			while (sscanf(line, "%[^,],%[^\n]\n", cell, line) == 2)//(strchr(rest, ',')){
				printf("%s\t", cell);//internal cell followed by tab
			printf("%s\n", cell);//last cell followed by new line
		}
		
	}
	else  {
		char c;
		while ((c = getchar()) != EOF)
			putchar(c);
	}
	


	
}
