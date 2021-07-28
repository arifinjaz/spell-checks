// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>
//#include <conio.h>

int insertnode(const char *newword, int number);
bool check_hash(const char *word, int h_val);
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 3000;
unsigned int counter = 0;


// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //printf("words:%s\n",word);
    int hash_val = hash(word);
    if (word == NULL)
    {
        return false;
    }
    if (check_hash(word, hash_val) == true)
    {
        return true;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    if (word == NULL)
    {
        return 0;
    }

    int wordint = 0;
    int fw[2];
    int sw = 0;

    for (int i = 0; i < 2; i++)
    {
        if (isupper(word[i]))
        {
            fw[i] = (int)word[i] + 32;
        }
        else
        {
            fw[i] = (int)word[i];
        }
    }


    int hash = 0;
    int c = 25;

    if (strlen(word) > 2 && strlen(word) < 5)
    {
        hash = ((fw[0] - 'a') * (c)) + (fw[0] + fw[1]); // FIrst letter is * by 25 to get unique hash.
        return hash;
    }
    else if (strlen(word) > 5)
    {
        hash = (((fw[0] - 'a') * (c)) + (fw[0] + fw[1])) + 626;
        return hash;
    }
    else
    {
        hash = (fw[0] - 'a');
        return hash;
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *f;

    f = fopen(dictionary, "r");

    if (f == NULL)
    {
        return false;
    }

    while (true)
    {
        char word[N + 1];

        if (fscanf(f, "%45s", word) == EOF)
        {
            break;
        }

        node *temp = malloc(sizeof(node));
        strcpy(temp->word, word);
        temp->next = NULL;

        int h_number = hash(word);

        temp -> next = table[h_number];

        table[h_number] = temp;

        //free(word);

        counter++;
    }

    fclose(f);
    // TODO

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (counter > 0)
    {
        return counter; // global variable
    }
    return 0;
}


void destroy(node *tables)
{

    if (tables == NULL)
    {
        return;
    }
    destroy(tables->next);
    free(tables);

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            destroy(table[i]);
        }
    }

    return true;
}

bool check_hash(const char *word, int h_val)
{
    if (table[h_val] == NULL)
    {

        return false;
    }
    node *search = NULL;

    search = table[h_val];

    while (search->next != NULL)
    {
        if (strcasecmp(word, search->word) == 0)
        {
            return true;

        }

        search = search -> next;
    }
    if (strcasecmp(word, search->word) == 0)
    {
        return true;
    }

    return false;
}
