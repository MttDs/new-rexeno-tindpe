/*
 * ImageLoad.h
 *
 *  Created on: Dec 11, 2013
 *      Author: xeno1
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef IMAGELOAD_H_
#define IMAGELOAD_H_

class ImageLoad{
	public:
		ImageLoad();
		ImageLoad(const char *filename);
		~ImageLoad();

		bool load();
		char * getData();
		unsigned long getSizeX();
		unsigned long getSizeY();

		void setFilename(const char * filename);

	private:
		char *filename;
		unsigned long sizeX;
		unsigned long sizeY;
		char *data;
};
//		Image *image;


#endif /* IMAGELOAD_H_ */
