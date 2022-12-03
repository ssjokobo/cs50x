#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //check one argc
    if (argc != 2)
    {
        printf("Usage: ./recover [file]");
        return 1;
    }

    //open input
    FILE *f_in = fopen(argv[1], "r");

    //check if the input file is ok
    if (f_in == NULL)
    {
        fclose(f_in);
        printf("Invalid file. Could not read.");
        return 1;
    }

    //variable declaration
    char *out_name = malloc(sizeof(char) * 8);
    int counter = 0;
    int block_size = 512;
    FILE *f_out;
    uint8_t *buffer = malloc(sizeof(uint8_t) * block_size);

    //loop through the input file
    while (fread(buffer, sizeof(uint8_t), block_size, f_in) == block_size)
    {
        //finding jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //first jpeg
            if (counter == 0)
            {
                //file name adjust
                sprintf(out_name, "%03i.jpg", counter);

                //open new jpeg
                FILE *out_add = fopen(out_name, "w");
                f_out = out_add;

                //copying
                fwrite(buffer, sizeof(uint8_t), block_size, f_out);

                //counter adjust
                counter++;
            }
            //later jpeg
            else
            {
                //close previous file
                fclose(f_out);

                //file name adjust
                sprintf(out_name, "%03i.jpg", counter);

                //open new jpeg
                FILE *out_add = fopen(out_name, "w");
                f_out = out_add;

                //copying
                fwrite(buffer, sizeof(uint8_t), block_size, f_out);

                //counter adjust
                counter++;
            }
        }
        else if (counter > 0)
        {
            //copying
            fwrite(buffer, sizeof(uint8_t), block_size, f_out);
        }
    }

    //cleaning
    free(out_name);
    free(buffer);
    fclose(f_in);
    fclose(f_out);
    return 0;
}