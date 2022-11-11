


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



char* lineptr[MAX_LINES];

int results[MAX_LINES];


char* normalizerHexo(char* input) {
	char output = (char)malloc(26);
	double double_value;
	int int_value;
	type input_type = INT;
	int i = 0;
	if (input[0] == '-' || input[0] == '+')
		i++;
	for (; i < strlen(input); i++)
		if (!isdigit(input[i])) {
			input_type = DOUBLE;
			break;
		}
	if (input_type == INT)
		sscanf(input, "%d", &int_value);
	else {
		if (sscanf(input, "%lf", &double_value))
			input_type = DOUBLE;
		else
			input_type = STRING;
	}
	if (input_type == INT)
		sprintf(output, "%25x", int_value);
	else if (input_type == DOUBLE)
		sprintf(output, "%lf", double_value);
	else
		sprintf(output, "%s", input);
	return output;
}


char* normalizerTrunc(char* input) {
	char output = (char)malloc(26);
	double double_value;
	int int_value;
	type input_type = INT;
	int i = 0;
	if (input[0] == '-' || input[0] == '+')
		i++;
	for (; i < strlen(input); i++)
		if (!isdigit(input[i])) {
			input_type = DOUBLE;
			break;
		}
	if (input_type == INT)
		sscanf(input, "%d", &int_value);
	else {
		if (sscanf(input, "%lf", &double_value))
			input_type = DOUBLE;
		else
			input_type = STRING;
	}
	if (input_type == INT)
		sprintf(output, "%d", int_value);
	else if (input_type == DOUBLE)
		sprintf(output, "%lf", double_value);
	else
		sprintf(output, "%25.5s", input);
	return output;
}




char* normalizerScientific(char* input) {
	char output = (char)malloc(26);
	double double_value;
	int int_value;
	type input_type = INT;
	int i = 0;
	if (input[0] == '-' || input[0] == '+')
		i++;
	for (; i < strlen(input); i++)
		if (!isdigit(input[i])) {
			input_type = DOUBLE;
			break;
		}
	if (input_type == INT)
		sscanf(input, "%d", &int_value);
	else {
		if (sscanf(input, "%lf", &double_value))
			input_type = DOUBLE;
		else
			input_type = STRING;
	}
	if (input_type == INT)
		sprintf(output, "%d", int_value);
	else if (input_type == DOUBLE)
		sprintf(output, "%25e", double_value);
	else
		sprintf(output, "%s", input);
	return output;
}

int main(int argc, char** argv)
{
	
	char* line[MAX_LINE_LENGTH];
	char* cell[MAX_CELL_LENGTH];
	//char* rest;
	int c; 
	int hexadecimal, remove_white_space, scientific_notation, trunc = 0;
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
				trunc = 1;
				break;
				
			case 'i':
			{
				
				char* input_format = *++argv;
				printf("Input Format: %s\n", input_format);
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
	
	if (argc == -2)
		printf("Usage: convert pattern\n");


	
	
	if ((input) && (output)) { // txt to csv
		while (fgets(line, MAX_LINE_LENGTH, stdin)) {
			
			strcpy(cell, "");
			char tabs[100];
			strcpy(tabs, "");

			while (sscanf(line, "%[^\t]\t%[^\n]\n", tabs, line) == 2 || sscanf(line, "%[^\t\n]%[\t]%[^\n]\n", cell, tabs, line) == 3)
			{
				if (hexadecimal)
				{																
					strcpy(cell, normalizerHexo(cell));					
				} 
				if (trunc)
				{
					strcpy(cell, normalizerTrunc(cell));
				}
				if (scientific_notation)
				{
					strcpy(cell, normalizerTrunc(cell));
				}
				printf("%s,", cell);

				
				printf("%s,", cell);
				

				if (strcmp(tabs, "\t") != 0) 
				{
					while (sscanf(line, "\t%[\t]", tabs) > 0) 
					{
						printf(",");
					}					
				}
			}
			

			

			if (trunc)
			{
				strcpy(cell, trunc(cell));
			}
				
			if (scientific_notation)
			{
				strcpy(cell, scientific_notation(cell));
			}
				
			if (hexadecimal)
			{
				strcpy(cell, hexadecimal(cell));
			}
				
				
			printf("%s\n", cell);

		}
		
	}
	else if (!(input) && !(output)) { // csv to txt
		while (fgets(line, MAX_LINE_LENGTH, stdin)) {
			char commas[100];
			strcpy(cell, "");
			strcpy(commas, "");


			while (sscanf(line, "%[^,],%[^\n]\n", commas, line) == 2 || sscanf(line, "%[^,\n]%[,]%[^\n]\n", cell, commas, line) == 3)
			{
				if (hexadecimal) strcpy(cell, hexadecimal(cell));
				if (trunc) strcpy(cell, trunc(cell));
				if (scientific_notation)strcpy(cell, scientific_notation(cell));														
									
				printf("%s\t", cell);

				if (strcmp(commas, ",") != 0) 
				{
					while (sscanf(line, ",%[,]", commas) > 0) 
					{
						printf("\t");
					}

					printf("\t");
				}
			}
			if (trunc)strcpy(cell, trunc(cell));
			if (hexadecimal)strcpy(cell, hexadecimal(cell));
			if (scientific_notation)strcpy(cell, scientific_notation(cell));											
														
			printf("%s\n", cell);
		}
		
	}
	else  { // if both are the same file format, txt and txt or csv and csv
		printf("Input and output are equivalent");
		char c;
		while ((c = getchar()) != EOF)
			putchar(c);
	}		
}
