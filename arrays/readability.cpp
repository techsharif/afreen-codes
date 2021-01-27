#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{
    string text = get_string("Text: ");

    int ln = strlen(text);

    int i, grade;
    float lcount=0, wcount=1, scount=0, L, S;

    for (i = 0; i < ln; i = i + 1){
        if (isalpha(text[i]))
        {
            lcount = lcount + 1;
        }

        if (text[i] == ' ')
        {
            wcount = wcount + 1;
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            scount = scount + 1;
        }
    }

    // printf("%d letter(s)\n", lcount);
    // printf("%d word(s)\n", wcount);
    // printf("%d sentence(s)\n", scount);

    L = round((lcount * 100) / wcount);
    S = round((scount * 100) / wcount);

    grade = 0.0588 * L - 0.296 * S - 15.8;

    printf("Grade %d\n", grade);

}