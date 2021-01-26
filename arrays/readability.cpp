#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main()
{
    string text = get_string("Text: ");

    int ln = strlen(text);

    int i, lcount=0, wcount=1, scount=0;

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

    printf("%d letter(s)\n", lcount);
    printf("%d word(s)\n", wcount);
    printf("%d sentence(s)\n", scount);


}