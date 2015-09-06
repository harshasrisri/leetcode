#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct WordDictionary {
    char *word;
    struct WordDictionary *index;
};

/** Initialize your data structure here. */
struct WordDictionary* wordDictionaryCreate() {
    struct WordDictionary *head = (struct WordDictionary *) calloc (1, sizeof(struct WordDictionary));
    return head;
}

void addToTrie (struct WordDictionary *wd, char *stub, char *word) {
    if (!*stub) {
        wd->word = strdup(word);
        return;
    }
    if (!wd->index) wd->index = (struct WordDictionary*) calloc (26, sizeof(struct WordDictionary));
    addToTrie (&wd->index[*stub - 'a'], stub + 1, word);
}

bool searchTrie (struct WordDictionary *wd, char *stub, char *word) {
    if (!*stub) return (0 == strcmp(wd->word, word));
    if (!wd->index) return false;
    return searchTrie (&wd->index[*stub - 'a'], stub + 1, word);
}

/** Inserts a word into the data structure. */
void addWord(struct WordDictionary* wd, char* word) {
    if (!word || !*word) return;
    addToTrie (wd, word, word);
}

/** Returns if the word is in the data structure. A word could
    contain the dot character '.' to represent any one letter. */
bool search(struct WordDictionary* wd, char* word) {
    if (!word || !*word) return false;
    return searchTrie (wd, word, word);
}

/** Deallocates memory previously allocated for the data structure. */
void wordDictionaryFree(struct WordDictionary* wd) {
    int i;
    if (wd->word) free (wd->word);
    if (!wd->index) return;
    for (i = 0; i < 26; i++)
        wordDictionaryFree(&wd->index[i]);
	free (wd);
}

int main () {
	char *additions[] = {"something"};
	char *searches[] = {"something"};
	struct WordDictionary *wd = wordDictionaryCreate();
	unsigned int i;

	for (i = 0; i < sizeof(additions)/sizeof(char *); i++) {
		printf ("%s\n", additions[i]);
		addWord (wd, additions[i]);
	}

	for (i = 0; i < sizeof(searches)/sizeof(char *); i++) {
		printf ("%s : %s\n", searches[i], search (wd, additions[i]) ? "True" : "False");
	}

	return 0;
}
