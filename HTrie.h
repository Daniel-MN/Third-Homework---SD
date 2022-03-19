/* Mușuroi Daniel-Nicușor - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRIE
#define TRIE

#define ALPHABET_SIZE 68
#define NR_WORDS 3
#define MAX_LEN_WORD 51

typedef void (*TElib)(void *);
typedef void (*TPrint)(FILE *, void *);

typedef struct trieNode
{
    struct trieNode *children[ALPHABET_SIZE];
    //in c is the node char:   
    char c;

    //info != NULL if the node is a leaf
    void *info;
} TrieNode, *Trie;

Trie getNode(char c); //alloc a TrieNode
int char_to_index(char c); //tranform char c into a index for a node
void insert(Trie t, void *info, char *key); //insert info in Trie using key
void *search_info(Trie t, char *key);//search if a info is in the Trie and
//returns that info
char **search_words(Trie t, char *key, int *nr);
void printTrie(FILE *out, Trie t, TPrint fp);
Trie deletekey(Trie t, char *key, int level, TElib fe);
void destroy(Trie t, TElib fe);
void DestroyTrie(Trie *t, TElib fe);

#endif
