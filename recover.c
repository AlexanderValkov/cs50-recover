// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 512

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // iterate over infile's scanlines
    unsigned char buffer[BUFF_SIZE];

    int filenum = 1;

    int bytesRead = fread(&buffer, BUFF_SIZE, 1, inptr);

    while ( bytesRead > 0 )
    {
        if ( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ( buffer[3] & 0xf0 ) == 0xe0 )
        {
            //printf("found at %i chunk\n", k);

            char outfile[10];
            sprintf(outfile, "%03i.jpeg", filenum++);

            // open new file for writing
            FILE *outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", outfile);
                return 3;
            }

            do
            {
                fwrite(buffer, BUFF_SIZE, 1, outptr);
                bytesRead = fread(&buffer, 1, BUFF_SIZE, inptr);
            }
            while ( !( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ( buffer[3] & 0xf0 ) == 0xe0 ) && bytesRead == BUFF_SIZE );

            if ( !( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ( buffer[3] & 0xf0 ) == 0xe0 ) && bytesRead < BUFF_SIZE )
                fwrite(buffer, bytesRead, 1, outptr);

            fclose(outptr);
            //*/
        } else
        {
            bytesRead = fread(&buffer, BUFF_SIZE, 1, inptr);
        }
    }

    // close infile
    fclose(inptr);

    // success
    return 0;
}
