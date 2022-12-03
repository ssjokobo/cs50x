#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //getting input
    long card_num = get_long("Enter your credit card number: ");
    int checksum = 0;
    int length_counter = 0;
    int current_digit = 0;
    int first_two = 0;

    //processing
    while (card_num >= 0)
    {
        //getting last digit and counting which digit
        current_digit = card_num % 10;
        length_counter++;

        //processing the algorithm
        if (length_counter % 2 == 1)
        {
            checksum += current_digit;
        }
        else
        {
            current_digit = current_digit * 2;
            if (current_digit < 10)
            {
                checksum += current_digit;
            }
            else
            {
                checksum += current_digit % 10 + current_digit / 10;
            }
        }

        //getting the first two digit
        if (card_num < 100 && card_num > 9)
        {
            first_two = card_num;
        }

        //move to next digit
        card_num = card_num / 10;

        if (card_num == 0)
        {
            break;
        }

    }

    //identifying

    //check algorithm
    if (checksum % 10 == 0)
    {
        //amex
        if (length_counter == 15)
        {
            if (first_two == 34 || first_two == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //mastercard
        else if (length_counter == 16)
        {
            if (first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 || first_two == 55)
            {
                printf("MASTERCARD\n");
            }

            //visa 16
            else if (first_two / 10 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        //visa 13
        else if (length_counter == 13 && first_two / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}