#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#define HEADERBYTES 54

/*
    Modified function from:
    https://www.programmingsimplified.com/c/source-code/c-program-convert-string-to-integer-without-using-atoi-function
 */
int toInt(char[]);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    // number of times to scale image by
    int scaleFactor = toInt(argv[1]);

    // ensure appropriate scale factor
    if (scaleFactor < 1 || scaleFactor > 100)
    {
        fprintf(stderr, "n must be a positive integer less than or equal to 100\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
    // set new height/width values
    LONG biWidth = bi.biWidth;
    LONG biHeight = bi.biHeight;
    LONG newBiWidth = biWidth * scaleFactor;
    LONG newBiHeight = biHeight * scaleFactor;
    DWORD newBiSizeImage;
    DWORD newBfSize;

    // determine padding for scanlines
    int newPadding = (4 - (newBiWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oldPadding = (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine image size with padding factored in
    bi.biWidth = newBiWidth;
    bi.biHeight = newBiHeight;
    newBiSizeImage = ((sizeof(RGBTRIPLE) * newBiWidth) + newPadding) * abs(newBiHeight);
    bi.biSizeImage = newBiSizeImage;
    newBfSize = bi.biSizeImage + (sizeof(BITMAPFILEHEADER)) + (sizeof(BITMAPINFOHEADER));
    bf.bfSize = newBfSize;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // read over lines
    for (int i = 0; i < abs(biHeight); i++)
    {
        // repeat line scan for each line to resize vertically
        for (int a = 0, iterations = scaleFactor - 1; a < scaleFactor; a++)
        {
            // scan over pixels in line
            for (int j = 0; j < biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // write RGB triple to outfile
                for (int z = 0; z < scaleFactor; z++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
            // do not rescan line for final iteration
            if (a != iterations)
            {
                int move = HEADERBYTES + ((biWidth * 3) + oldPadding) * i;
                fseek(inptr, move, SEEK_SET);
            }
            else
            {
                fseek(inptr, oldPadding, SEEK_CUR);
            }
        }
    }
    // close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);
    // success
    return 0;
}

// removed code handling negative integers
int toInt(char a[])
{
    int c, n;
    n = 0;

    for (c = 0; a[c] != '\0'; c++)
    {
        n = n * 10 + a[c] - '0';
    }
    return n;
}
