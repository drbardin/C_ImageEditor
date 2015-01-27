#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readwriteimage.h"

int main(int argc, char *argv[])
{
    FILE *fp;
    FILE *outfp;
    Image_File imageptr;
    const char *inpath;
    const char *outpath;
    const char ch = '.';
    char *in_extsn_chck;
    char *out_extsn_chck;
    int x, y, w, h;

    /* malloc vars for input and output files */
    inpath = malloc(sizeof(strlen(argv[1] + 1)));
    inpath = argv[1];
    outpath = malloc(sizeof(strlen(argv[2] + 1)));
    outpath = argv[2];

    if(argc != 7){
        fprintf(stderr, "Incorrect number of args. Should be 6, have %d: Terminating. \n", argc-1);
        exit(-1);
    }

    /* check input file for proper extension */
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

    out_extsn_chck = strrchr(outpath, ch);
    if (strcmp(out_extsn_chck, ".simp") != 0)
    {
        fprintf(stderr, "Output file does not have the .simp extension. Terminating.\n");
        exit(-1);
    }
    outfp = fopen(outpath, "w");
    if (!outfp)
    {
        fprintf(stderr, "Could not open output file \n");
        exit(-1);
    }

    x = atoi(argv[3]); /* (x,y) start position for crop */
    y = atoi(argv[4]);
    w = atoi(argv[5]); /* w & h are output width and height  */
    h = atoi(argv[6]);



    ReadImageToMemory(fp, &imageptr); /* Load image w & h, each pixel to struct */

    /* Check for valid user input. */
    if (x > imageptr.width)
    {
        fprintf(stderr, "Input 'x' > image file width. Terminating.");
    }
    if (x < 0)
    {
        fprintf(stderr, "Input 'x' < 0. Terminating.");
    }
    if (y > imageptr.height)
    {
        fprintf(stderr, "Input 'y' > image file height. Terminating.");
    }
    if (y < 0)
    {
        fprintf(stderr, "Input 'y' < 0. Terminating.");
    }

    WriteCropToFile(outfp, &imageptr, x, y, w, h);

    fclose(fp);
    fclose(outfp);
    destroy_imagestruct(&imageptr);

    return 0;

}
