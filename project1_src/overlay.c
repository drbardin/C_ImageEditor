#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readwriteimage.h"

void DrawPic2onPic1(Image_File *pic1, Image_File *pic2, int x, int y)
{
    int r = 0;
    int c = 0;
    int i = 0;
    int j = 0;

    double rval, gval, bval, aval;
    double p2A, p2R, p2G, p2B,
           p1A, p1R, p1G, p1B;

    for (r = y; r < pic1->height - 1; r++)
    {
        j = 0;
        for (c = x; c < pic1->width - 1; c++)
        {
            if ((unsigned int)pic2->pixmap[i][j].alpha != 255)
            {
                /* For readability and floating point math */
                p2A = pic2->pixmap[i][j].alpha;
                p2R = pic2->pixmap[i][j].red;
                p2G = pic2->pixmap[i][j].green;
                p2B = pic2->pixmap[i][j].blue;
                p1A = pic1->pixmap[r][c].alpha;
                p1R = pic1->pixmap[r][c].red;
                p1G = pic1->pixmap[r][c].green;
                p1B = pic1->pixmap[r][c].blue;


                rval = (p2R * (p2A / 255)) + (((p1A * (255 - p2A)) / pow(255, 2)) * p1R);

                gval = (p2G * (p2A / 255)) + (((p1A * (255 - p2A)) / pow(255, 2)) * p1G);

                bval = (p2B * (p2A / 255)) + (((p1A * (255 - p2A)) / pow(255, 2)) * p1B);

                aval = (((p2A / 255) + ((p1A * (255 - p2A)) / pow(255, 2))) * 255);


                pic1->pixmap[r][c].red   = (unsigned char)rval;
                pic1->pixmap[r][c].green = (unsigned char)gval;
                pic1->pixmap[r][c].blue  = (unsigned char)bval;
                pic1->pixmap[r][c].alpha = (unsigned char)aval;
            }
            else
            {
                pic1->pixmap[r][c].red = pic2->pixmap[i][j].red;
                pic1->pixmap[r][c].green = pic2->pixmap[i][j].green;
                pic1->pixmap[r][c].blue = pic2->pixmap[i][j].blue;
                pic1->pixmap[r][c].alpha = pic2->pixmap[i][j].alpha;
            }
            j++;
            if (j == pic2->width)
                break;
        }
        i++;
        /* Break out of loops if we've brought in the image. */
        if (i == pic2->height)
            break;
    }
}

/* args: pic1, pic2, Out, X, Y */
int main(int argc, char **argv)
{

    Image_File pic1_image;
    Image_File pic2_image;
    FILE *fppic1;
    FILE *fppic2;
    FILE *outfp;
    const char *inpathpic1;
    const char *inpathpic2;
    const char *outpath;
    const char ch = '.';
    char *in_extsn_chck;
    char *out_extsn_chck;
    int usrX, usrY;

    if (argc != 6)
    {
        fprintf(stderr, "Incorrect number of args. Should be 5, have %d: Terminating. \n", argc - 1);
        exit(-1);
    }

    /* INPUT 1 */
    inpathpic1 = malloc(sizeof(strlen(argv[1] + 1)));
    inpathpic1 = argv[1];
    in_extsn_chck = strrchr(inpathpic1, ch);
    if (strcmp(in_extsn_chck, ".simp") != 0)
    {
        fprintf(stderr, "Input file does not have the .simp extension. Terminating.\n");
        exit(-1);
    }

    fppic1 = fopen(inpathpic1, "r");
    if (!fppic1)
    {
        fprintf(stderr, "Could not open file: %s \n", inpathpic1);
        exit(-1);
    }

    /* INPUT 2 */
    inpathpic2 = malloc(sizeof(strlen(argv[2] + 1)));
    inpathpic2 = argv[2];
    in_extsn_chck = strrchr(inpathpic2, ch);
    if (strcmp(in_extsn_chck, ".simp") != 0)
    {
        fprintf(stderr, "Input file does not have the .simp extension. Terminating.\n");
        exit(-1);
    }

    fppic2 = fopen(inpathpic2, "r");
    if (!fppic2)
    {
        fprintf(stderr, "Could not open file: %s \n", inpathpic2);
        exit(-1);
    }

    /* OUTPUT */
    outpath = malloc(sizeof(strlen(argv[3] + 1)));
    outpath = argv[3];
    out_extsn_chck = strrchr(outpath, ch);
    if (strcmp(out_extsn_chck, ".simp") != 0)
    {
        fprintf(stderr, "Output file does not have the .simp extension. Terminating.\n");
        exit(-1);
    }

    outfp = fopen(outpath, "w");
    if (!outfp)
    {
        fprintf(stderr, "Could not open file: %s \n", inpathpic2);
        exit(-1);
    }

    /* get (X,Y) to superimpose */
    usrX = atoi(argv[4]);
    usrY = atoi(argv[5]);

    /* Load pic1 and pic2 images to structs */
    ReadImageToMemory(fppic1, &pic1_image);
    ReadImageToMemory(fppic2, &pic2_image);

    /* overlay the images */
    DrawPic2onPic1(&pic1_image, &pic2_image, usrX, usrY);

    /* send output image to file */
    WriteBwShiftOverToFile(outfp, &pic1_image);

    return (0);
}
