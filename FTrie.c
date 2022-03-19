/* Mușuroi Daniel-Nicușor - 313CB */
#include "HTrie.h"

Trie getNode(char c){
    Trie pNode = (Trie)malloc(sizeof(TrieNode));
    if (!pNode){
        exit(101);
    }
    int i;
  
    pNode->info = NULL;
    pNode->c = c;
  
    for (i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
  
    return pNode;
}

//tranform char c into a index for a node
int char_to_index(char c){
    //index(a) = 0, index(b) = 1 ... index(z) = 25
    if (c >= 'a' && c <= 'z')
        return (int)c - 97;

    //index(a) = 26, index(b) = 27 ... index(z) = 51
    if (c >= 'A' && c <= 'Z')
        return (int)c - 39;

    //index(0) = 52, ... index(9) = 61
    if (c >= '0' && c <= '9')
        return (int)c + 4;

    if (c == '.')
        return 62;

    if (c == '-')
        return 63;

    if (c == '\'')
        return 64;
    
    if (c == '?')
        return 65;
    
    if (c == '!')
        return 66;
    
    if (c == ' ')
        return 67;

    return -1;
}

void insert(Trie t, void *info, char *key){
    int i;
    int len = strlen(key);
    int index;
  
    Trie p = t;
  
    for (i = 0; i < len; i++)
    {
        index = char_to_index(key[i]);
        if (!p->children[index])
            p->children[index] = getNode(key[i]);
  
        p = p->children[index];
    }
  
    //mark last node as leaf and put the info there:
    p->info = info;
}

void *search_info(Trie t, char *key){
    if (!t)
        return NULL;

    int i;
    int len = strlen(key);
    int index;
    Trie p = t;
  
    for (i = 0; i < len; i++)
    {
        index = char_to_index(key[i]);
  
        if (!p->children[index])
            return NULL;
  
        p = p->children[index];
    }
  
    if (p->info)
        return p->info;
    else 
        return NULL;
}

void search(Trie p, char **words, int *nr, char *wordArray, int pos){
    if (p == NULL)
        return;

    if (*nr == 3)
        return;
        
    if (p->info){
        strcat(words[*nr], wordArray);
        (*nr)++;
    }

    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if(p->children[i]) {
            wordArray[pos] = p->children[i]->c;
            wordArray[pos + 1] = '\0';
            search(p->children[i], words, nr, wordArray, pos + 1);
        }
    }
}

//returns the first 3 words with the prefix key(without ~)
char **search_words(Trie t, char *key, int *nr){
    int i;
    int len = strlen(key);
    int index;
    Trie p = t;
  
    for (i = 0; i < len; i++)
    {
        index = char_to_index(key[i]);
  
        if (!p->children[index])
            return NULL;
  
        p = p->children[index];
    }

    char **words = (char **)malloc(NR_WORDS * sizeof(char *));
    if (!words)
        exit(101);

    for (i = 0; i < NR_WORDS; i++){
        words[i] = (char *)calloc(MAX_LEN_WORD, sizeof(char));
        if (!words[i]){
            int j;
            for (j = i - 1; j >= 0; j--){
                free(words[j]);
            }
            exit(101);
        }

        strcpy(words[i], key);
    }
    char *wordArray = (char *)calloc(MAX_LEN_WORD, sizeof(char));
    if (!wordArray)
        exit(101);

    search(p, words, nr, wordArray, 0);
    free(wordArray);
    return words;
}

void printTrie(FILE *out, Trie t, TPrint fp){
    if (!t)
        return;

    if (t->info)
        fp(out, t->info);

    Trie p = t;
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++){
        if (p->children[i]){
            printTrie(out, p->children[i], fp);
        }
    }

}

int haschild(Trie p){
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++){
        if (p->children[i])
            return 1;
    }
    return 0;
}

Trie deletekey(Trie t, char *key, int level, TElib fe)
{
    // If trie is empty
    if (!t)
        return NULL;
 
    // If last character of key is being processed
    if (level == strlen(key)) {
 
        // This node (t) is no more end of word after
        // removal of given key
        if (t->info){
            fe(t->info);
            t->info = NULL;
        }
 
        // If given is not prefix of any other word
        if (!haschild(t)) {
            free(t);
            t = NULL;
        }
 
        return t;
    }
 
    // If not last character, recur for the child
    int index = char_to_index(key[level]);
    t->children[index] = deletekey(t->children[index], key, level + 1, fe);
 
    // If root does not have any child (its only child got
    // deleted), and it is not end of another word.
    if (!haschild(t) && !t->info) {
        free(t);
        t = NULL;
    }
 
    return t;
}

void destroy(Trie t, TElib fe){
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++){
        if (t->children[i])
            destroy(t->children[i], fe);
    }

    if (t->info){//leaf
        fe(t->info);
    }

    free(t);
}

void DestroyTrie(Trie *t, TElib fe){
    if (!(*t)){ //empty (unallocated)
        return;
    }
    
    destroy(*t, fe);
    *t = NULL;
}
