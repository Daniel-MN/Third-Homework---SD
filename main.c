/* Mușuroi Daniel-Nicușor - 313CB */
#include "HTema3.h"

void tema3(FILE *in, FILE *out){
    Trie T1, T2;
    T1 = getNode(0);
    T2 = getNode(0);

    char *line = (char *)malloc(MAX_LEN_LINE * sizeof(char));
    if (!line)
        exit(101);

    char *operation;
    char *line_rest;

    //read the file line by line
    while (fgets(line, MAX_LEN_LINE, in)){
        if (line[strlen(line) - 1] == '\n'){
            line[strlen(line) - 1] = '\0';
        }
        operation = strtok(line, " ");
        line_rest = line + strlen(operation) + 1;

        if (strcmp(operation, "add_book") == 0)
            add_book(line_rest, T1, T2);

        if (strcmp(operation, "search_book") == 0)
            search_book(line_rest, out, T1);

        if (strcmp(operation, "list_author") == 0)
            list_author(line_rest, out, T2);

        if (strcmp(operation, "search_by_author") == 0)
            search_by_author(line_rest, out, T2);

        if (strcmp(operation, "delete_book") == 0)
            delete_book(line_rest, out, T1, T2);
    }

    free(line);
    DestroyTrie(&T1, DestroyBook);
    DestroyTrie(&T2, DestroyTrieAuthor);
}

int main(int argc, char *argv[]){
    if (argc != 3)
    {
        printf("Mod de rulare al temei incorect!\n");
        exit(202);
    }

    FILE *in = fopen(argv[1], "rt");
    if (in == NULL)
    {
        return 2;
    }

    FILE *out = fopen(argv[2], "wt");
    if (out == NULL)
    {
        return 2;
    }

    //the function which solves the homework:
    tema3(in, out);

    fclose(in);
    fclose(out);

    return 0;
}