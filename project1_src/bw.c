#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readwriteimage.h"

int main(int argc, char *argv[])
{

    Image_File image;
    FILE *fp;
    FILE *outfp;
    const char *inpath;
    const char *outpath;
    const char ch = '.';
    char *in_extsn_chck;
    char *out_extsn_chck;
    unsigned char rval, gval, bval, newval;

    int row, col;

    if(argc != 3){
        fprintf(stderr, "Incorrect number of args. Should be 2, have %d: Terminating. \n", argc-1);
        exit(-1);
    }

    inpath = malloc(sizeof(strlen(argv[1] + 1)));
    inpath = argv[1];
    in_extsn_chck = strrchr(inpath, ch);
    if (strcmp(in_extsn_chck, ".simp") != 0)
    {
        fprintf(stderr, "Input file does not have the .simp extension. Terminating.\n");
        exit(-1);
    }

    fp = fopen(inpath, "r");
    if (!fp)
    {
        fprintf(stderr, "Could not open input file path: %s\n Terminating.\n", inpath);
        exit(-1);
    }

    ReadImageToMemory(fp, &image);

    /**
     Set image to grayscale.
     (r + g + b) / 3 = value for r, g, b.
     */
    for (row = 0; row < image.height; row++)
    {
        for (col = 0; col < image.width; col++)
        {
            /* readability & manipulation */
            rval = image.pixmap[row][col].red;
            gval = image.pixmap[row][col].green;
            bval = image.pixmap[row][col].blue;

            /* get average of r, g, & b, store */
            newval = (rval + gval + bval) / 3;

            /* give each channel new averaged grayscale value */
            image.pixmap[row][col].red = newval;
            image.pixmap[row][col].green = newval;
            image.pixmap[row][col].blue = newval;

        }
    }

    outpath = malloc(sizeof(strlen(argv[2] + 1)));
    outpath = argv[2];

    out_extsn_chck = strrchr(outpath, ch);
    if (strcmp(out_extsn_chck, ".simp") != 0)
    {
        fprintf(stderr, "Output file does not have the .simp extension. Terminating.\n");
        exit(-1);
    }

    outfp = fopen(outpath, "w");
    if (!outfp)
    {
        fprintf(stderr, "Could not open output file path: %s\n Terminating.\n", outpath);
        exit(-1);
    }

    WriteBwShiftOverToFile(outfp, &image);

    fclose(fp);
    fclose(outfp);
    destroy_imagestruct(&image);

    return 0;
}
