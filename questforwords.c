/* 
 * Quest For Words
 * by Alistair Carscadden
 * 2018-01-27
 *
 * See readme.md
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Maximum word length -- search times are O(n!)
// Note: In the sweep(...) function, printed words are padded to W=20
#define MAX_WORD (16)

/* Result
 * Store the characteristics of a word that has been
 * found in the infinite strings
 */
typedef struct {
	char* word;
	int seed;
	int index;
} Result;

/* search
 * Searches the string formed by the seed up to the
 * character maximum (max) for the word 'word'.
 * Returns an index on success, or -1 if not found.
 */
int search(char* word, int seed, int max) {
	srand(seed);
	int length = strlen(word);
	int index = -1; // of the found word
	int local = 0; // index within the word we're currently searching
	
	for(int i = 0; i < max; ++i) {
		char c = rand() % 26 + 'A';
		
		if(word[local] == c) {
			local++;
		} else {
			local = 0;
		}
		
		if(local == length) {
			index = i - length + 1;
		}
	}
	
	return index;
}

/* print
 * Prints the entire string up until the index
 * Every 40 characters a \r is appended to reset the line
 */
int print(int seed, int index) {
	srand(seed);
	int reset = 40;
	
	for(int i = 0; i < index; ++i) {
		if(!--reset) {
			printf("\r");
			reset = 40;
		}
		printf("%c", rand() % 26 + 'A');
	}
	
	while(--reset) printf(" ");
	printf("\n");
}

/* sweep
 * Searches for the word up to the maximum for every seed
 * 0 < seed < +Infinity
 * Could run forever if provided with a string that cannot
 * exist in a string, (e.g. "a"). Could run for the rest of your
 * life and a few other lives if given a really long valid string.
 */
void sweep(char* word, int max) {
	Result r;
	
	int i = 0;
	while(++i) {
		int result = search(word, i, max);
		if(result > -1) {
			r.word = word;
			r.seed = i;
			r.index = result;
			break;
		}
	}
	
	printf("%-20s %8d %8d\n", r->word, r->seed, r->index);
}

int main(int argc, char** argv) {
	char header[] = "WORD                     SEED    INDEX\n";
	if (argc == 3) {
		printf(header);
		sweep(argv[1], atoi(argv[2]));
	} else if(argc == 4) {
		FILE* file = fopen(argv[3], "r");
		
		printf(header);
		char word[MAX_WORD];
		while(fgets(word, MAX_WORD, file)) {
			// Replace the first non A-Z character with NULL
			char* c = word;
			while(*c >= 'A' && *c <= 'Z') c++;
			*c = '\0';
			
			// Sweep this word
			sweep(word, atoi(argv[2]));
		}
		
		fclose(file);
	} else {
		printf("Usage: Arguments:\n    <WORD IN CAPS> <MAXIMUM DISTANCE PER SEED>\n    f <MAXIMUM DISTANCE PER SEED> <FILE OF WORDS IN CAPS>\n");
	}
}
