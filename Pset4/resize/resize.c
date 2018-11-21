#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }


    // remember filenames and scale factor
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    //check n <= 100
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Please use a scaling factor that is positive and less than or equal to 100!\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    BITMAPFILEHEADER bf_n = bf;
    BITMAPINFOHEADER bi_n = bi;


    bi_n.biWidth = bi.biWidth * n;
    bi_n.biHeight = bi.biHeight * n;

     // determine padding for scanlines for new and old
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_n = (4 - (bi_n.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_n.biSizeImage = ((sizeof(RGBTRIPLE) * bi_n.biWidth) + padding_n) * abs(bi_n.biHeight);
    bf_n.bfSize = bi_n.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);




    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_n, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_n, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int row = 0, biHeight = abs(bi.biHeight); row < biHeight; row++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile based on n
                for (int k = 0; k < n; k++)
                {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }
            for (int pad = 0; pad < padding_n; pad++)
            {
                fputc(0x00, outptr);
            }
            int distance = bi.biWidth * sizeof(RGBTRIPLE);
            fseek(inptr, -distance, SEEK_CUR);


        }


        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile based on n
            for (int k = 0; k < n; k++)
            {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

         // then add it back (to demonstrate how)
        for (int pad = 0; pad < padding_n; pad++)
        {
            fputc(0x00, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
