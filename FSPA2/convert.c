// new main function
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_LINE_LENGTH 1000
#define MAX_CELL_LENGTH 20
int main( int argc, char *argv[]){
	char in_ext[4], out_ext[4];
	char line[MAX_LINE_LENGTH];
	char cell[MAX_CELL_LENGTH];
	char* rest;
	if(argc < 5){
		fprintf(stderr, "convert: too few args\n");
		exit(1);
	}
	else if(argc > 5){
		fprintf(stderr, "convert: too many args\n");
		exit(1);
	}
	if(!strcmp(argv[1], "-i")){
		strncpy(in_ext, argv[2], 3);
		strncpy(out_ext, argv[4], 3);
	}
	else if(!strcmp(argv[1], "-o")){
		strncpy(out_ext, argv[2], 3);
		strncpy(in_ext, argv[4], 3);
	}else{
		fprintf(stderr, "convert: fatal error! usage: -i in_ext -o out_ext\n");
		exit(1);
	}
	fprintf(stderr, "convert: in format is %s, out format is %s\n", in_ext, out_ext);
	if(!strcmp(in_ext, "csv") && !strcmp(out_ext, "txt")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^,],%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
				printf("%s\t", cell);//internal cell followed by tab
			printf("%s\n",cell);//last cell followed by new line
		}
	}else if(!strcmp(in_ext, "txt") && !strcmp(out_ext, "csv")){
		while(fgets(line, MAX_LINE_LENGTH, stdin)){
			while(sscanf(line,"%[^\t]\t%[^\n]\n",cell , line) == 2)//(strchr(rest, ',')){
				printf("%s,", cell);//internal cell followed by tab
			printf("%s\n",cell);//last cell followed by new line
		}
	}else if (!strcmp(in_ext, out_ext)){
		char c;
		while((c=getchar())!= EOF)
			putchar(c);
	}else{
		fprintf(stderr, "convert: fatal error! usage: -i in_ext -o out_ext and only supported extensions are csv and txt\n");
		exit(1);
	}
}
