// 1.19 -> 10

// 119 / 25 -> 4
// 119 % 25 -> 19

// 19 / 10 -> 1
// 19 % 10 -> 9

// 9 / 5 = 1
// 9 % 5 = 4

// 4

#include <stdio.h>
#include <math.h>
// #include <cs50.h>

int main()
{
    float dollars;
    int count25, count10, count5, count1;
    
    while (1)
    {
        printf("Change owed: ");
        scanf("%f", &dollars); // 1.19

        // repeat = get_float("Change owed: ");

        if (dollars > 0.0)
        {
            break;
        }
    }

    int cents = round(dollars * 100); // 119

    count25 = cents / 25; // 119 / 25 -> 4
    cents = cents % 25; // 119 % 25 -> 19

    count10 = cents / 10; // 19 / 10 -> 1
    cents = cents % 10; // 19 % 10 -> 9

    count5 = cents / 5; // 9 / 5 = 1
    cents = cents % 5; // 9 % 5 = 4

    count1 = cents / 1; // 4 / 1 = 4

    int answer = count25 + count10 + count5 + count1;
    printf("%d\n", answer);

}
