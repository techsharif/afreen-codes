#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *input = fopen(argv[1], "r");

    if (!input)
    {
        return 1;
    }

    BYTE a = 0, b = 0, c = 0, d = 0;
    int count = 0;
    int isFileOpen = 0;
    FILE *output;
    while (1)
    {
        if (fread(&d, sizeof(BYTE), 1, input) == 0)
        {
            if (isFileOpen)
            {
                fwrite(&a, sizeof(BYTE), 1, output);
                fwrite(&b, sizeof(BYTE), 1, output);
                fwrite(&c, sizeof(BYTE), 1, output);
                fclose(output);
                isFileOpen = 0;
            }
            break;
        }

        if (a == 0xff && b == 0xd8 && c == 0xff)
        {
            if (d >= 0xe0 && d <= 0xef)
            {
                if (isFileOpen)
                {
                    fclose(output);
                    isFileOpen = 0;
                }
                char fileName[100];
                sprintf(fileName, "%03d.jpg", count);
                output = fopen(fileName, "w");
                isFileOpen = 1;
                count++;
            }
        }

        if (isFileOpen)
        {
            fwrite(&a, sizeof(BYTE), 1, output);
        }

        a = b;
        b = c;
        c = d;

    }

    fclose(input);
}