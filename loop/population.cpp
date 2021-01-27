#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n, count = 0;

    // TODO: Prompt for start size
    int start_size;

    while (1)
    {
        start_size = get_int("Start size: ");

        if (start_size >= 9)
        {
            break;
        }
    }


    // TODO: Prompt for end size
    int end_size;
    while (1)
    {
        end_size = get_int("End size: ");

        if (start_size <= end_size)
        {
            break;
        }
    }

    n = start_size;

    // TODO: Calculate number of years until we reach threshold
    while (n < end_size)
    {
        count = count + 1;

        int born = n / 3;
        int pass = n / 4;

        n = n + born - pass;
    }

    // TODO: Print number of years
    printf("Years: %d\n", count);
}