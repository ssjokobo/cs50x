#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //getting input
    string name = get_string("What is your name? ");

    //printing 
    printf("hello, %s\n", name);
}