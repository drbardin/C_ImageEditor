#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readwriteimage.h"

void ReadImageToMemory(FILE *fptr, Image_File *imstruct)
{
    int col = 0;
    int row = 0;

    fread(&(imstruct->width), sizeof(unsigned int), 1, fptr);
    fread(&(imstruct->height), sizeof(unsigned int), 1, fptr);

    imstruct->pixmap = (Pixel **) malloc((imstruct->height) * sizeof(Pixel *));
    for (row = 0; row < imstruct->height; row++)
    {
        imstruct->pixmap[row] = (Pixel *) malloc((imstruct->width) * sizeof(Pixel));
        for (col = 0; col < imstruct->width; col++)
        {
            fread(&imstruct->pixmap[row][col].red, sizeof(unsigned char), 1, fptr);
            fread(&imstruct->pixmap[row][col].green, sizeof(unsigned char), 1, fptr);
            fread(&imstruct->pixmap[row][col].blue, sizeof(unsigned char), 1, fptr);
            fread(&imstruct->pixmap[row][col].alpha, sizeof(unsigned char), 1, fptr);
        }
    }
}

void WriteCropToFile(FILE *output, Image_File *image, int x, int y, int w, int h)
{
    int col = 0;
    int row = 0;
    int outh, outw;

    /* Write output width and height to output file */
    if (fwrite(&w, sizeof(unsigned int), 1, output) != 1) 
    {
        fprintf(stderr, "Write error of new width to output file. Terminating.");
    }
    if (fwrite(&h, sizeof(unsigned int), 1, output) != 1)
    {
        fprintf(stderr, "Write error of new height to output file. Terminating.");
    }

    outh = y + h;
    outw = x + w;
    for (row = y; row < outh; row++)
    {
        for (col = x; col < outw; col++)
        {
            fwrite(&image->pixmap[row][col].red, sizeof(unsigned char), 1, output);
            fwrite(&image->pixmap[row][col].green, sizeof(unsigned char), 1, output);
            fwrite(&image->pixmap[row][col].blue, sizeof(unsigned char), 1, output);
            fwrite(&image->pixmap[row][col].alpha, sizeof(unsigned char), 1, output);
        }

    }
}

void WriteBwShiftOverToFile(FILE *output, Image_File *image)
{
	int row, col;

    fwrite(&image->width, sizeof(unsigned int), 1, output);
    fwrite(&image->height, sizeof(unsigned int), 1, output);

	   for (row = 0; row < image->height; row++)
    {
        for (col = 0; col < image->width; col++)
        {
            fwrite(&image->pixmap[row][col].red, sizeof(unsigned char), 1, output);
            fwrite(&image->pixmap[row][col].green, sizeof(unsigned char), 1, output);
            fwrite(&image->pixmap[row][col].blue, sizeof(unsigned char), 1, output);
            fwrite(&image->pixmap[row][col].alpha, sizeof(unsigned char), 1, output);
        }

    }
}

void destroy_imagestruct(Image_File *imf)
{
    free(imf->pixmap);
}

