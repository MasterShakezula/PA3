#include "find.h"
#include <string.h>

void swap(char* v[], int i, int j) {
	char* temp;

	temp = v[i];

	v[i] = v[j];

	v[j] = temp;
}

void qsort2(char* v[], int left, int right) {
	int i, last;

	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	
	swap(v, left, (left + right) / 2);

	last = left;

	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);

	qsort2(v, left, last - 1);

	qsort2(v, last + 1, right);
}

void reverse(char* str[], int len) {
	for (int first = 0, last = len - 1; first < last; first++, last--) {
		char* temp = str[first];
		str[first] = str[last];
		str[last] = temp;
	}
}

void print_results(char* pattern, int case_sense,int matched, int first_occurrence, int numbered, int sorted, int partial, int reversed, int no_of_results){
	char** sentences = (char**) malloc(no_of_results*sizeof(char*));
	
	for(int i = 0; i < no_of_results;i++){
		sentences[i] = strdup(lineptr[results[i]]);
	}
	
	if(sorted){
		qsort2(sentences, 0, no_of_results - 1);
	}
	
	else if (reversed){
		reverse(sentences, no_of_results);
	}
	
	for(int i = 0; i < no_of_results; i++){
		if(numbered)
			printf("%d. ", results[i] + 1); 
	
		if (first_occurrence) {
			if (matched)
				if (case_sense)
					printf("@%d: ", strcasestr_fully_matched(sentences[i], pattern) - sentences[i]);

				else
					printf("@%d: ", strstr_fully_matched(sentences[i], pattern) - sentences[i]);

			else
				if (case_sense)
					printf("@%d: ", strcasestr(sentences[i], pattern) - sentences[i]);
				
				else
					printf("@%d: ", strstr(sentences[i], pattern) - sentences[i]);
		}
		
		if (partial) {
			if (matched)
				if (case_sense) {
					if (strlen(sentences[i]) > 15) {
						if ((strcasestr_fully_matched(sentences[i], pattern) - sentences[i]) < 10 && sentences[i] - (strcasestr_fully_matched(sentences[i], pattern)) > -5)
							printf("%.*s...%s\n", (strcasestr_fully_matched(sentences[i], pattern) - sentences[i]) + strlen(pattern), sentences[i], sentences[i] + strlen(sentences[i]) - 5);

						else {
							int a = strlen(sentences[i]);
							
							int b = (strcasestr_fully_matched(sentences[i], pattern) - sentences[i] + strlen(pattern));

							int c = a - b;

							if (c <= 5) {
								printf("%.10s...%s\n", sentences[i], sentences[i] + strlen(sentences[i]) - strlen(pattern) - c);
								//printf("%.*s...%s\n", (strcasestr_fully_matched(sentences[i], pattern) - sentences[i]) + strlen(pattern), sentences[i], sentences[i] + strlen(sentences[i]) - 5);
							}

							else {
								printf("%.10s...%s...%s\n", sentences[i], pattern, sentences[i] + strlen(sentences[i]) - 5);
							}
						}
					}

					else {
						printf("%s\n", sentences[i]);
					}
				}

				else {
					if (strlen(sentences[i]) > 15) {
						if ((strstr_fully_matched(sentences[i], pattern) - sentences[i]) < 10 && sentences[i] - (strstr_fully_matched(sentences[i], pattern)) > -5)
							printf("%.*s...%s\n", (strstr_fully_matched(sentences[i], pattern) - sentences[i]) + strlen(pattern), sentences[i], sentences[i] + strlen(sentences[i]) - 5);

						else {
							int a = strlen(sentences[i]);

							int b = (strstr_fully_matched(sentences[i], pattern) - sentences[i] + strlen(pattern));

							int c = a - b;

							if (c <= 5) {
								printf("%.10s...%s\n", sentences[i], sentences[i] + strlen(sentences[i]) - strlen(pattern) - c);
							}

							else {
								printf("%.10s...%s...%s\n", sentences[i], pattern, sentences[i] + strlen(sentences[i]) - 5);
							}
						}
					}

					else {
						printf("%s\n", sentences[i]);
					}
				}

			else
				if (case_sense) {
					if (strlen(sentences[i]) > 15) {
						if ((strcasestr(sentences[i], pattern) - sentences[i]) < 10 && sentences[i] - (strcasestr(sentences[i], pattern)) > -5)
							printf("%.*s...%s\n", (strcasestr(sentences[i], pattern) - sentences[i]) + strlen(pattern), sentences[i], sentences[i] + strlen(sentences[i]) - 5);

						else {
							int a = strlen(sentences[i]);

							int b = (strcasestr(sentences[i], pattern) - sentences[i] + strlen(pattern));

							int c = a - b;

							if (c <= 5) {
								printf("%.10s...%s\n", sentences[i], sentences[i] + strlen(sentences[i]) - strlen(pattern) - c);
								//printf("%.*s...%s\n", (strcasestr_fully_matched(sentences[i], pattern) - sentences[i]) + strlen(pattern), sentences[i], sentences[i] + strlen(sentences[i]) - 5);
							}

							else {
								printf("%.10s...%s...%s\n", sentences[i], pattern, sentences[i] + strlen(sentences[i]) - 5);
							}
						}
					}

					else {
						printf("%s\n", sentences[i]);
					}
				}

				else {
					if (strlen(sentences[i]) > 15) {
						if ((strstr(sentences[i], pattern) - sentences[i]) < 10 && sentences[i] - (strstr(sentences[i], pattern)) > -5)
							printf("%.*s...%s\n", (strstr(sentences[i], pattern) - sentences[i]) + strlen(pattern), sentences[i], sentences[i] + strlen(sentences[i]) - 5);

						else {
							int a = strlen(sentences[i]);

							int b = (strstr(sentences[i], pattern) - sentences[i] + strlen(pattern));

							int c = a - b;

							if (c <= 5) {
								printf("%.10s...%s\n", sentences[i], sentences[i] + strlen(sentences[i]) - strlen(pattern) - c);
								//printf("%.*s...%s\n", (strcasestr_fully_matched(sentences[i], pattern) - sentences[i]) + strlen(pattern), sentences[i], sentences[i] + strlen(sentences[i]) - 5);
							}

							else {
								printf("%.10s...%s...%s\n", sentences[i], pattern, sentences[i] + strlen(sentences[i]) - 5);
							}
						}
					}

					else {
						printf("%s\n", sentences[i]);
					}
				}
			
		}

		else {
			printf("%s\n", sentences[i]);
		}	
	}
}