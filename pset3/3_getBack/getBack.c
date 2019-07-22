#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FATBLOCK 512

void makeFile(int fileNumber);

// initialise buffer for img
unsigned char imgBuffer[513];
// file count for file naming and flag for determining whether we may need file
int filesMade, filePending;

// declare outfile
FILE *outfile;

int main(int argc, char *argv[])
{
    filesMade = 0;
    filePending = 0;

    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // forensic image
    char *imgFile = argv[1];
    // open the forensic image raw data file
    FILE *inptr = fopen(imgFile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", imgFile);
        return 2;
    }
    // repeat until end of file
    while (fread(imgBuffer, 1, FATBLOCK, inptr) == 512)
    {
        // found start of JPEG
        if (imgBuffer[0] == 0xff &&
            imgBuffer[1] == 0xd8 &&
            imgBuffer[2] == 0xff &&
            (imgBuffer[3] & 0xf0) == 0xe0)
        {
            // no file open
            if (filePending == 0)
            {
                // create file
                makeFile(filesMade);
                // file count incremented
                filesMade++;
            }
            // start of JPEG found and JPEG file already open
            else
            {
                filePending = 0;
                makeFile(filesMade);
                filesMade++;
            }
        } // end found new JPEG
        // new JPEG not found
        else
        {
            if (filePending == 1)
            {
                makeFile(filesMade - 1);
            }
        }
    } // end card
    // close infile
    fclose(inptr);
    // success
    return 0;
}

// create a new file or append to an existing one
void makeFile(int fileNumber)
{
    // initialise buffer
    char filename[8];
    // format filename
    sprintf(filename, "%03i.jpg", fileNumber);
    // open output file
    outfile = fopen(filename, "a");
    // write or append 512 bytes to file
    fwrite(imgBuffer, 1, 512, outfile);
    fclose(outfile);
    // file creation may not be complete
    filePending = 1;
}