#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readwriteimage.h"

void shift2(Image_File *im, int pattern)
{
    unsigned char temp;
    int row, col;
    /** (RG = 6) (GR = 7) (RB = 8)
      * (BR = 9) (GB = 10) (BG = 11) */
    for (row = 0; row < im->height; row++)
    {
        for (col = 0; col < im->width; col++)
        {
            switch (pattern)
            {
            case 6:
                temp = im->pixmap[row][col].green;
                im->pixmap[row][col].green = im->pixmap[row][col].red;
                im->pixmap[row][col].red = temp;
                break;
            case 7:
                temp = im->pixmap[row][col].red;
                im->pixmap[row][col].red = im->pixmap[row][col].green;
                im->pixmap[row][col].green = temp;
                break;
            case 8:
                temp = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = im->pixmap[row][col].red;
                im->pixmap[row][col].red = temp;
                break;
            case 9:
                temp = im->pixmap[row][col].red;
                im->pixmap[row][col].red = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = temp;
                break;
            case 10:
                temp = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = im->pixmap[row][col].green;
                im->pixmap[row][col].green = temp;
                break;
            case 11:
                temp = im->pixmap[row][col].green;
                im->pixmap[row][col].green = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = temp;
                break;
            }
        }
    }
}

void shift3(Image_File *im, int pattern)
{
    unsigned char temp;
    int row, col;

    /** (RGB = 0) (GBR = 1) (BRG = 2)
      * (RBG = 3) (BGR = 4) (GRB = 5) */
    for (row = 0; row < im->height; row++)
    {
        for (col = 0; col < im->width; col++)
        {
            switch (pattern)
            {
            case 0:
                temp = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = im->pixmap[row][col].green;
                im->pixmap[row][col].green = im->pixmap[row][col].red;
                im->pixmap[row][col].red = temp;
                break;
            case 1:
                temp = im->pixmap[row][col].red;
                im->pixmap[row][col].red = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = im->pixmap[row][col].green;
                im->pixmap[row][col].green = temp;
                break;
            case 2:
                temp = im->pixmap[row][col].green;
                im->pixmap[row][col].green = im->pixmap[row][col].red;
                im->pixmap[row][col].red = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = temp;
                break;
            case 3:
                temp = im->pixmap[row][col].green;
                im->pixmap[row][col].green = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = im->pixmap[row][col].red;
                im->pixmap[row][col].red = temp;
                break;
            case 4:
                temp = im->pixmap[row][col].red;
                im->pixmap[row][col].red = im->pixmap[row][col].green;
                im->pixmap[row][col].green = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = temp;
                break;
            case 5:
                temp = im->pixmap[row][col].blue;
                im->pixmap[row][col].blue = im->pixmap[row][col].red;
                im->pixmap[row][col].red = im->pixmap[row][col].green;
                im->pixmap[row][col].green = temp;
                break;
            }
        }
    }
}

int main(int argc, char **argv)
{

    Image_File image;
    FILE *fp;
    FILE *outfp;
    const char *inpath;
    const char *outpath;
    const char *pattern;
    const char ch = '.';
    char *in_extsn_chck;
    char *out_extsn_chck;
    int pattern_case;


    if (argc != 4)
    {
        fprintf(stderr, "Incorrect number of args. Should be 3, have %d: Terminating. \n", argc - 1);
        exit(-1);
    }
    /* INPUT */
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
        fprintf(stderr, "Cannot open source image file: %s Terminating.\n", inpath);
        exit(-1);
    }


    /* OUTPUT */
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
        fprintf(stderr, "Cannot open output file: %s Terminating.\n", outpath);
    }


    /* PATTERN */
    pattern = malloc(sizeof(strlen(argv[3] + 1)));
    pattern = argv[3];

    if (strcmp(pattern, "RGB") == 0)
        pattern_case = 0;
    else if (strcmp(pattern, "GBR") == 0)
        pattern_case = 1;
    else if (strcmp(pattern, "BRG") == 0)
        pattern_case = 2;
    else if (strcmp(pattern, "RBG") == 0)
        pattern_case = 3;
    else if (strcmp(pattern, "BGR") == 0)
        pattern_case = 4;
    else if (strcmp(pattern, "GRB") == 0)
        pattern_case = 5;
    else if (strcmp(pattern, "RG") == 0)
        pattern_case = 6;
    else if (strcmp(pattern, "GR") == 0)
        pattern_case = 7;
    else if (strcmp(pattern, "RB") == 0)
        pattern_case = 8;
    else if (strcmp(pattern, "BR") == 0)
        pattern_case = 9;
    else if (strcmp(pattern, "GB") == 0)
        pattern_case = 10;
    else if (strcmp(pattern, "BG") == 0)
        pattern_case = 11;
    else
    {
        fprintf(stderr, "Cannot complete colorshift due to unknown pattern: %s Terminating.\n\
            Make sure pattern is in CAPS.\n", pattern);
        exit(-1);
    }


    ReadImageToMemory(fp, &image);

    /* send to value-shift func */
    if (pattern_case < 6)
        shift3(&image, pattern_case);
    else if (pattern_case > 5)
        shift2(&image, pattern_case);


    WriteBwShiftOverToFile(outfp, &image);

    fclose(fp);
    fclose(outfp);

    destroy_imagestruct(&image);

    return (0);
}
