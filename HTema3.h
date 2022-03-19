/* Mușuroi Daniel-Nicușor - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTrie.h"
#include "HUtils.h"

#ifndef TEMA3
#define TEMA3


void add_book(char *line, Trie T1, Trie T2);
void search_book(char *line, FILE *out, Trie T1);
void list_author(char *line, FILE *out, Trie T2);
void search_by_author(char *line, FILE *out, Trie T2);
//key has ~, typekey is "carte" or "autor"
void prefix(FILE *out, Trie t, char *key, char *typekey);
void delete_book(char *line, FILE *out, Trie T1, Trie T2);

#endif