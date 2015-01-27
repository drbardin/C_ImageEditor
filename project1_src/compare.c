#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "readwriteimage.h"

int main(int argc, char**argv)
{

	Image_File pic1;
	Image_File pic2;
	FILE *fppic1;
	FILE *fppic2;
	const char *inpathpic1;
	const char *inpathpic2;
	int i, j;
	int counter = 0;

	/* get filepath strings and open files */
	inpathpic1 = malloc(sizeof(strlen(argv[1] + 1)));
	inpathpic1 = argv[1];
	fppic1 = fopen(inpathpic1, "r");
	if (!fppic1)
	{
		fprintf(stderr, "Could not open file: %s \n", inpathpic1);
		exit(-1);
	}

	inpathpic2 = malloc(sizeof(strlen(argv[2] + 1)));
	inpathpic2 = argv[2];
	fppic2 = fopen(inpathpic2, "r");
	if (!fppic2)
	{
		fprintf(stderr, "Could not open file: %s \n", inpathpic2);
		exit(-1);
	}

	ReadImageToMemory(fppic1, &pic1);
	ReadImageToMemory(fppic2, &pic2);

	for (i = 0; i < pic1.height; i++)
	{
		for (j = 0; j < pic1.width; j++)
		{

			int flag = 0;

			if (pic1.pixmap[i][j].red != pic2.pixmap[i][j].red)
			{
				printf("Dif at R[%d][%d]: pic1 %i   pic2 %i \n", i, j, pic1.pixmap[i][j].red, pic2.pixmap[i][j].red);
				flag = 1;
			}
			if (pic1.pixmap[i][j].green != pic2.pixmap[i][j].green)
			{
				printf("Dif at G[%d][%d]: pic1 %i   pic2 %i \n", i, j, pic1.pixmap[i][j].green, pic2.pixmap[i][j].green);
				flag = 1;
			}
			if (pic1.pixmap[i][j].blue != pic2.pixmap[i][j].blue)
			{
				printf("Dif at B[%d][%d]: pic1 %i   pic2 %i \n", i, j, pic1.pixmap[i][j].blue, pic2.pixmap[i][j].blue);
				flag = 1;
			}
			if (pic1.pixmap[i][j].alpha != pic2.pixmap[i][j].alpha)
			{
				printf("Dif at A[%d][%d]: pic1 %i   pic2 %i \n", i, j, pic1.pixmap[i][j].alpha, pic2.pixmap[i][j].alpha);
				flag = 1;
			}
			if(flag){
				counter++;
			}

		}
	}
	printf("Error count: %d \n", counter);


}
