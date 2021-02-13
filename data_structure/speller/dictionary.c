// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int h = hash(word);

    node *data = table[h];

    while (data != NULL)
    {
        if (strcasecmp(data->word, word) == 0)
        {
            return true;
        }

        data = data->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int MOD = 10000007;
    unsigned int ln = strlen(word);
    unsigned int hash = 0;

    for (int i = 0; i < ln; i++)
    {
        unsigned int power = 1;
        unsigned int num = tolower(word[i]) - 'a';
        num = num > 0 ? num : num * -1;
        unsigned int base = 26;
        for (int j = 1; j <= i; j++)
        {
            power *= base;
            power %= MOD;
        }

        unsigned int value = power * num;
        hash += value;
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    int dln = strlen(dictionary);

    FILE *input = fopen(dictionary, "r");

    if (!input)
    {
        return false;
    }
    int jj = 0;
    char w[100];
    while (1)
    {
        char c;
        bool r = false;

        if (fread(&c, sizeof(char), 1, input) == 0)
        {
            r = true;
            c = '\n';
        }


        if (c == '\n')
        {
            w[jj] = '\0';
            jj = 0;
            int wln = strlen(w);
            if (wln)
            {
                unsigned int h = hash(w);
                node *data = table[h];

                if (data == NULL)
                {
                    table[h] = (node *) malloc(sizeof(node));
                    data = table[h];
                }
                else
                {
                    while (data->next != NULL)
                    {
                        data = data->next;
                    }

                    data->next = (node *) malloc(sizeof(node));
                    data = data->next;

                }

                strcpy(data->word, w);
                data->next = NULL;

            }

        }
        else
        {
            w[jj++] = c;
        }
        if (r)
        {
            break;
        }
    }

    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int count = 0;
    for (int i = 0; i < N; i++)
    {
        node *data = table[i];
        while (data != NULL)
        {
            data = data->next;
            count++;


        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *data = table[i];
        node *next_data = table[i];

        while (data != NULL)
        {
            next_data = data->next;
            free(data);
            data = next_data;
        }
    }

    return true;
}
