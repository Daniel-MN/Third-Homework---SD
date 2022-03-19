/* Mușuroi Daniel-Nicușor - 313CB */
#include "HTema3.h"

void add_book(char *line, Trie T1, Trie T2){
    char *title;
    char *author;

    int rating, nr_pages;
    title = strtok(line, ":");
    author = strtok(NULL, ":");
    rating = atoi(strtok(NULL, ":"));
    nr_pages = atoi(strtok(NULL, ":"));

    //check if this book in T1:
    void *book = search_info(T1, title);
    if (!book){
        Book *b = allocBook(title, author, rating, nr_pages);
        insert(T1, (void *)b, b->title);

        //check if there is a trie for this author:
        Trie *Tauthor = (Trie *)search_info(T2, author);
        if (!Tauthor){//if there is not:
            Tauthor = (Trie *)malloc(sizeof(Trie));
            if (!Tauthor)
                exit(101);

            *Tauthor = getNode(0);
            insert(T2, (void *)Tauthor, author);
        }

        insert(*Tauthor, (void *)b, b->title);
    }
}

void search_book(char *line, FILE *out, Trie T1){
    char *title = line;

    // for: search_book <prefix_titlu>~
    if (title[strlen(title) - 1] == '~'){
        prefix(out, T1, title, "carte");
        return;
    }

    Book *b = (Book *)search_info(T1, title);

    if (!b){
        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", title);
    } else {
        fprintf(out, "Informatii recomandare: ");
        fprintf(out, "%s, %s, %d, %d\n", b->title, b->author, 
        b->rating, b->nr_pages);
    }
}

void list_author(char *line, FILE *out, Trie T2){
    char *author = line;
    if (author[strlen(author) - 1] == '~'){
        prefix(out, T2, author, "autor");
        return;
    }
    
    Trie *Tauthor = (Trie *)search_info(T2, author);
    if (!Tauthor){
        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n",
         author);
        return;
    }

    printTrie(out, *Tauthor, print_booktitle);
}

void search_by_author(char *line, FILE *out, Trie T2){
    char *title, *author;
    author = strtok(line, ":");
    title = strtok(NULL, ":");
    if (!title){ //i have only a prefix_autor in string author
        list_author(author, out, T2);
        return;
    }

    Trie *Tauthor = (Trie *)search_info(T2, author);
    if (!Tauthor){
        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n",
         author);
        return;
    }

    search_book(title, out, *Tauthor);
}

//key has ~ (key is a prefix), typekey is "carte" or "autor"
void prefix(FILE *out, Trie t, char *key, char *typekey){
    int nr = 0;
    key[strlen(key) - 1] = '\0';
    char **words = search_words(t, key, &nr);
    if (nr == 0){
        if (strcmp(typekey, "carte") == 0){
            fprintf(out, "Nicio carte gasita.\n");
            return;
        }

        if (strcmp(typekey, "autor") == 0){
            fprintf(out, "Niciun autor gasit.\n");
            return;
        }
        return;
    }

    //if nr != 0
    int i;
    for (i = 0; i < nr; i++){
        fprintf(out, "%s\n", words[i]);
    }
    
    for (i = 0; i < NR_WORDS; i++){
        free(words[i]);
    }
    free(words);
}

void delete_book(char *line, FILE *out, Trie T1, Trie T2){
    char *title = line;

    Book *b = (Book *)search_info(T1, title);
    if (!b){
        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", title);
        return;
    }

    //if the book exists in T1:
    char *author = (char *)malloc(MAX_LEN_AUTHOR * sizeof(char));
    if (!author)
        exit(101);

    strcpy(author, b->author);

    T1 = deletekey(T1, title, 0, DestroyBook);
    Trie *Tauthor = (Trie *)search_info(T2, author);
    *Tauthor = deletekey(*Tauthor, title, 0, Donothing);
    if (!(*Tauthor)){
        T2 = deletekey(T2, author, 0, DestroyTrieAuthor);
    }

    free(author);
}
