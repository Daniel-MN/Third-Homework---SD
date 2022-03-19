/* Mușuroi Daniel-Nicușor - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTrie.h"

#ifndef UTILS
#define UTILS

#define MAX_LEN_TITLE 51
#define MAX_LEN_AUTHOR 41
#define MAX_LEN_LINE 140

typedef struct book{
    int nr_pages, rating;
    char *title, *author;
} Book;

Book *allocBook(char *title, char *author, int rating, int nr_pages);
void DestroyBook(void *b);
void DestroyTrieAuthor(void *t);
void print_booktitle(FILE *out, void *book);
char *title_book(void *book);
char *author_trie(void *Tauthor);
void Donothing(void *t);

#endif