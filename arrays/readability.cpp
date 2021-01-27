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
    float lcount = 0, wcount = 1, scount = 0, L, S;

    for (i = 0; i < ln; i = i + 1)
    {
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

    L = (lcount * 100) / wcount;
    S = (scount * 100) / wcount;

    grade = round(0.0588 * L - 0.296 * S - 15.8);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    if (grade >= 1 && grade < 16)
    {
        printf("Grade %d\n", grade);
    }


}