#include"find.h"
#define MAX_LINES 1000
#define MAX_LEN 1000

char*lineptr[MAX_LINES];

int results[MAX_LINES];

char* strstr_fully_matched(char* haystack, char* needle){
	char* rv;
	
	char padded_needle[strlen(needle) + 3];
	
	padded_needle[0] = ' ';
	
	strcpy(padded_needle + 1, needle);
	
	padded_needle[strlen(needle) + 1] = ' ';
	
	padded_needle[strlen(needle) + 2] = '\0';
	
	if(!strncmp(haystack, padded_needle + 1, strlen(needle) + 1))
		return haystack;//needle is at the beginning
	
	if((rv = strstr(haystack, padded_needle)) != NULL)
		return rv + 1;//needle is at the middle.
	
	padded_needle[strlen(needle) + 1] = '\0';
	
	if((rv = strstr(haystack, padded_needle)) != NULL)
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

int getline2(char s[], int lim){
	int c, i;
	
	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n';i++)
		s[i] = c;
	
	if(c == '\n'){
		s[i] = c;
	
		i++;
	}
	
	s[i] = '\0';
	
	return i;
}

int readlines(char** lineptr, int maxlines){
	int len, nlines;

	char*p, line[MAX_LEN];
	
	nlines = 0;

	while((len = getline2(line, MAX_LEN)) > 0)
		if(nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;

		else{
			if(line[len - 1] == '\n')
				line[len - 1] = '\0';

			strcpy(p, line);

			lineptr[nlines++] = p;
		}
	return nlines;
}

int main(int argc, char** argv)
{
	int c;

	int except = 0;//done

	int sorted = 0;//done *

	int reversed = 0;//done *

	int partial = 0;//done *

	int numbered = 0;//done

	int first_occurrence = 0;//done

	int matched = 0;//done

	int case_sense = 0;//done *

	char* pattern = "in";

	int nlines;

	//printf("%s\n", pattern);

	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
				
			case 'c':
				
				printf("case_sense\n");

				case_sense = 1;

				break;

			case 'x':
				printf("except\n");

				except = 1;

				if (partial == 1 && except == 1) {
					printf("-p and -x can't be used together.\n");
					
					argc = 0;
					
					break;
				}

				break;

			case 'n':
				printf("numbered\n");

				numbered = 1;

				break;

			case 's':
				printf("sorted\n");

				sorted = 1;

				if (sorted == 1 && reversed == 1) {
					printf("-r and -s can't be used together.\n");
					
					argc = 0;
					
					break;
				}

				break;

			case 'r':
				printf("revered\n");

				reversed = 1;

				if (sorted == 1 && reversed == 1) {
					printf("-r and -s can't be used together.\n");
					
					argc = 0;
					
					break;
				}

				break;

			case 'm':
				printf("matched\n");

				matched = 1;

				break;

			case 'f':
				printf("first\n");

				first_occurrence = 1;

				if (first_occurrence == 1 && except == 1) {
					printf("-f and -x can't be used together.\n");
					
					argc = 0;
					
					break;
				}

				if (first_occurrence == 1 && except == 1) {
					printf("-f and -x can't be used together.\n");
					
					argc = 0;
					
					break;
				}
				break;

			case 'p':
				printf("partial\n");

				partial = 1;

				if (partial == 1 && except == 1) {
					printf("-p and -x can't be used together.\n");
					
					argc = 0;
					
					break;
				}

				break;

			default:
				printf("find: illeal option. \n");
				argc = 0;
				break;
			}
		}
	}

	if (argc != 1)
		printf("Usage: find pattern\n");

	else {
		pattern = *argv;

		nlines = readlines(lineptr, MAX_LINES);

		int no_of_results = 0;

		printf("\n\nINPUT:\n");

		for (int i = 0; i < nlines; i++)
			printf("%s\n", lineptr[i]);

		printf("\nOUTPUT:\n");

		for (int i = 0; i < nlines; i++) {
			if (matched) {
				if (case_sense) {
					if ((strcasestr_fully_matched(lineptr[i], pattern) != NULL) != except)
						results[no_of_results++] = i;
				}
				else {
					if ((strstr_fully_matched(lineptr[i], pattern) != NULL) != except)
						results[no_of_results++] = i;
				}
			}

			else {
				if (case_sense) {
					if ((strcasestr(lineptr[i], pattern) != NULL) != except)
						results[no_of_results++] = i;
				}
				else {
					if ((strstr(lineptr[i], pattern) != NULL) != except)
						results[no_of_results++] = i;
				}
			}
		}

		print_results(pattern, case_sense, matched, first_occurrence, numbered, sorted, partial, reversed, no_of_results);

		return 0;
	}
}