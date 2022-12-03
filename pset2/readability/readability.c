#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Getting input
    string text = get_string("Text: ");

    //function calls
    int l = count_letters(text);
    int w = count_words(text);
    int s = count_sentences(text);

    //grading calculation
    float words = w;
    float grade = 0.0588 * (l * 100 / words) - 0.296 * (s * 100 / words) - 15.8;
    grade = round(grade);

    //printing grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade);
    }
}

//counting letters
int count_letters(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //check if letter
        if (islower(text[i]) || isupper(text[i]))
        {
            counter++;
        }
    }
    return counter;
}

//counting words
int count_words(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //check if space
        if (text[i] == 32)
        {
            counter++;
        }
    }

    //adjusting counter
    if (strlen(text) != 0)
    {
        counter++;
    }

    return counter;
}

//counting sentences
int count_sentences(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //check if punctuation
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            counter++;
        }
    }
    return counter;
}