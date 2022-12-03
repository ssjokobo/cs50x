#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check if 2 arg
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check if 26 char
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //check if duplication
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][(i + j) % n])
            {
                printf("Error! Duplicated characters!\n");
                return 1;
            }
        }
    }

    //check if invalid character in key

    //make key to upper
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (islower(argv[1][i]))
        {
            argv[1][i] -= 32;
        }
        else if (!isupper(argv[1][i]))
        {
            printf("Error! Invalid characters!\n");
            return 1;
        }
    }

    //input
    string text = get_string("plaintext: ");

    //encrypting
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = argv[1][text[i] - 65];
        }
        else if (islower(text[i]))
        {
            text[i] = argv[1][text[i] - 97] + 32;
        }unzip sort.zip
    }

    //output
    printf("ciphertext: %s", text);
    printf("\n");
    return 0;
}