/* Mușuroi Daniel-Nicușor - 313CB */
#include "HUtils.h"

Book *allocBook(char *title, char *author, int rating, int nr_pages){
    Book *b = (Book *)malloc(sizeof(Book));
    if (!b)
        exit(101);

    b->title = (char *)malloc((1 + strlen(title)) * sizeof(char));
    if (!b->title){
        free(b);
        exit(101);
    }

    b->author = (char *)malloc((1 + strlen(author)) * sizeof(char));
    if (!b->author){
        free(b->author);
        free(b);
        exit(101);
    }

    strcpy(b->title, title);
    strcpy(b->author, author);
    b->rating = rating;
    b->nr_pages = nr_pages;

    return b;
}

void DestroyBook(void *b){
    free(((Book *)b)->author);
    free(((Book *)b)->title);
    free((Book *)b);
    b = NULL;
}

void Donothing(void *t){
    return;
}

void DestroyTrieAuthor(void *t){
    DestroyTrie((Trie *)t, Donothing);
    free((Trie *)t);
}

void print_booktitle(FILE *out, void *book){
    fprintf(out, "%s\n", ((Book *)book)->title);
}

