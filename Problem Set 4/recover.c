#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc !=2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    //open memory card
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Error: Image %s cannot be opened.\n", argv[1]);
        return 2;
    }

    //set outfile pointer to NULL
    FILE *outptr = NULL;

    //create array of 512 elements to store 512 bytes from memory card
    BYTE buffer[512];

    //count amount of jped files found;
    int count = 0;

    //string to hold filename
    char filename[8] = {0};

    //read memory card until end of file
    while(fread(buffer[1], sizeof(BYTE)*512, 1, inptr) == 1)
    {
        //check if jpeg file was found
        if(buffer[0]==0xFF && buffer[1]==0xD8 && buffer[2]==0xFF && (buffer[3]&0xF0 == 0xE0))
        {
            //close outptr if jped was found before and written into ###.jpg
            if(outptr !=NULL)
            {
                fclose(outptr)
            };
                sprintf(filename, "%03i.jpg", count++);

                //open a new outptr for writing a new found jpeg
                outptr = fopen(filename, "w");
        }
    }

    //keep writing to jpeg file if new jpeg is not found
    if(outptr ! = NULL)
    {
        fwrite(buffer, sizeof(BYTE)*512, 1, outptr);
    }

    //close input file (forensic image)
    fclose(inptr);

    return 0; 
}
