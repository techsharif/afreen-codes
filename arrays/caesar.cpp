#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    int key = 0;

    if (argc == 2)
    {
       key = atoi(argv[1]);
    }

    if (key == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    int ln = strlen(plaintext);
    int i;

    for (i = 0; i < ln; i++)
    {
        char c = plaintext[i]; // H

        if (isupper(c)){
            int pos = c - 'A'; // 7
            pos = (pos + key) % 26; // 7 + 1 -> 8
            c = 'A' + pos; // A + 8 -> A B C D E F G H I -> I
        }

        if (islower(c)){
            int pos = c - 'a'; // 7
            pos = (pos + key) % 26; // 7 + 1 -> 8
            c = 'a' + pos; // A + 8 -> A B C D E F G H I -> I
        }

        plaintext[i] = c;
    }

    printf("ciphertext: %s\n", plaintext);
}

