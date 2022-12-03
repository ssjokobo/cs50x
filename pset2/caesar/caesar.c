#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);

int main(int argc, string argv[])
{
    //check if two arg
    if (argc != 2)
    {
        printf("Error!\n");
        return 1;
    }

    //check if digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //convert key
    int k = atoi(argv[1]);

    //input text
    string text = get_string("plaintext:  ");

    //encrypt
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = ((text[i] - 65 + k) % 26) + 65;
        }
        else if (islower(text[i]))
        {
            text[i] = ((text[i] - 97 + k) % 26) + 97;
        }
    }

    //print result
    printf("ciphertext:  %s\n", text);

    //return value
    return 0;
}

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isdigit(s[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}