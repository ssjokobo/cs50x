#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //getting input and check
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //line counter
    for (int i = 1; i <= n; i++)
    {
        //printing space
        for (int j = n - i; j > 0; j--)
        {
            printf(" ");
        }

        //printing left brick
        for (int k = i; k > 0; k--)
        {
            printf("#");
        }

        //gap
        printf("  ");

        //printing right brick
        for (int k = i; k > 0; k--)
        {
            printf("#");
        }

        //new line
        printf("\n");
    }
}
