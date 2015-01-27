#ifndef READWRITEIMAGE_H
#define READWRITEIMAGE_H

typedef struct {

	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;

} Pixel;

typedef struct {
 
	unsigned int width;
	unsigned int height;
	Pixel **pixmap;

} Image_File;

void ReadImageToMemory(FILE*, Image_File*);
void WriteCropToFile(FILE*, Image_File*, int, int, int, int);
void WriteBwShiftOverToFile(FILE*, Image_File*);
void destroy_imagestruct(Image_File*);

#endif /* READWRITEIMAGE_H */
