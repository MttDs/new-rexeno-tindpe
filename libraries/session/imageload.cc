/*
 * ImageLoad.cpp
 *
 *  Created on: Dec 11, 2013
 *      Author: xeno1
 */
#include "imageload.hh"

ImageLoad::ImageLoad(const char *filename): filename((char*)filename){
	this->sizeX = 0;
	this->sizeY = 0;
	this->data = NULL;
}
ImageLoad::ImageLoad(){
	this->sizeX = 0;
	this->sizeY = 0;
	this->data = NULL;
	this->filename = NULL;
}
ImageLoad::~ImageLoad(){
	free(this->data);
}
bool ImageLoad::load(){
	   	FILE *file;

	    unsigned long size;                 // size of the image in bytes.
	    unsigned long i;                    // standard counter.
	    unsigned short int planes;          // number of planes in image (must be 1)
	    unsigned short int bpp;             // number of bits per pixel (must be 24)
	    char temp;                          // used to convert bgr to rgb color.

	    struct Image{
	    	unsigned long sizeX;
	    	unsigned long sizeY;
	    	char *data;
	    };
	    typedef struct Image Image;

		Image *image;
		image = (Image *) malloc(sizeof(Image));

		if (image == NULL){
			printf("Erreur d'allocation de mémoire pour l'image");
			return 0;
		}
	    // make sure the file is there.
	    if ((file = fopen(this->filename, "rb"))==NULL)
	    {
	    	printf("File Not Found : %s\n",this->filename);
	    	return 0;
	    }

	    // seek through the bmp header, up to the width/height:
	    fseek(file, 18, SEEK_CUR);

	    // read the width
	    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
	    	printf("Error reading width from %s.\n", this->filename);
	    	return 0;
	    }
	    //	printf("Width of %s: %lu\n", this->filename, image->sizeX);

	    // read the height
	    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
	    	printf("Error reading height from %s.\n", this->filename);
			return 0;
	    }
	    //	    	printf("Height of %s: %lu\n", this->filename, image->sizeY);

	    // calculate the size (assuming 24 bits or 3 bytes per pixel).
	    size = image->sizeX * image->sizeY * 3;

	    // read the planes
	    if ((fread(&planes, 2, 1, file)) != 1) {
	    	printf("Error reading planes from %s.\n", this->filename);
			return 0;
	    }
	    if (planes != 1) {
	    	printf("Planes from %s is not 1: %u\n", this->filename, planes);
			return 0;
	    }

	    // read the bpp
	    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	    	printf("Error reading bpp from %s.\n", this->filename);
			return 0;
	    }
	    if (bpp != 24) {
	    	printf("Bpp from %s is not 24: %u\n", this->filename, bpp);
			return 0;
	    }

	    // seek past the rest of the bitmap header.
	    fseek(file, 24, SEEK_CUR);

	    // read the data.
	    image->data = (char *) malloc(size);
	    if (image->data == NULL) {
	    	printf("Error allocating memory for color-corrected image data");
			return 0;
	    }

	    if ((i = fread(image->data, size, 1, file)) != 1) {
	    	printf("Error reading image data from %s.\n", filename);
	    	return 0;
	    }

	    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
		temp = image->data[i];
		image->data[i] = image->data[i+2];
		image->data[i+2] = temp;
	    }
	    this->data = image->data;
	    this->sizeY = image->sizeY;
	    this->sizeX = image->sizeX;

	    free(image);

	    return 1;
}

char * ImageLoad::getData(){
	return (char*)this->data;
}
unsigned long ImageLoad::getSizeX(){
	return this->sizeX;
}
unsigned long ImageLoad::getSizeY(){
	return this->sizeY;
}

void ImageLoad::setFilename(const char * filename){
	this->filename = (char*)filename;
}
