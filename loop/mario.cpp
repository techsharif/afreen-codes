#include <stdio.h>
// #include <cs50.h>

int main()
{
    int repeat, stars, space;
    
    while (1)
    {
        // printf("Height: ");
        // scanf("%d", &repeat);

        // repeat = get_int("Height: ");

        if (repeat >= 1 && repeat <= 8)
        {
            break;
        }
    }

    int i;
    for (i = 1; i <= repeat; i = i + 1)
    {
        int j;
        space = repeat - i; // repeat, i
        for (j=1; j <= space; j = j + 1)
        {
            printf(" ");
        }

        int k;
        stars = i; // repeat, i
        for (k=1; k <= stars; k = k + 1)
        {
            printf("#");
        }

        printf("\n"); // print a new line
    }

    return 0;
}
