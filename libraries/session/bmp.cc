/*
 * 05/28/2003
 *
 * bmp.cpp
 * Thierry Vouriot (Yéri)
 * yeri@fr.st
 * http://www.yeri.fr.st
 * thierry.vouriot@free.fr
 * http://thierry.vouriot.free.fr
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "bmp.hh"

// ###########
// Classe CBmp
// ###########


// ============
// Constructeur
// ============
CBmp::CBmp() {
	m_data = NULL;
}


// ===========
// Destructeur
// ===========
CBmp::~CBmp()
{
	delete m_data;
}
	

#define CTOI(C) (*(int*)&C)	//récupère en int un nombre pointé par un char*

// ======================================================
// Fonction lisant un fichier BMP 8 ou 24 (non compresse)
// ======================================================
int CBmp::Load(char *filename) 
{
	FILE *filePtr;			// pointeur sur le fichier
	unsigned char header[0x36];	// tableau qui contiendra l'en-tête du fichier BMP
	int colorMode;			// 3 pour RGB
	int imagePos;			// offset du début des données de l'image
	long imageSize;			// taille de l'image BMP
	long imageIdx;			// compteur
	unsigned char colorSwap;	// variable d'échange
	
	// ouverture du fichier BMP
	if (!(filePtr = fopen(filename, "rb"))) {
        	return BMP_FILE_NOT_FOUND;
	}	
	// lecture de l'en-tête
	if (fread(header,1,0x36,filePtr)!=0x36) {
		fclose(filePtr);
		return BMP_BAD_IMAGE_TYPE;
	}	
	// BM indique que l'on se trouve en présence d'un fichier bitmap
	if (header[0]!='B' || header[1]!='M') {
		fclose(filePtr);
		return BMP_BAD_IMAGE_TYPE;
	}
	// indique que l'image n'est pas compressée	
	if (CTOI(header[0x1E])!=0) {
		fclose(filePtr);
		return BMP_BAD_IMAGE_TYPE;
	}
	// image 24 et 8 bits uniquement
	m_bitCount = CTOI(header[0x1C]);
	if (m_bitCount!=24 && m_bitCount!=8) {
		fclose(filePtr);
		return BMP_BAD_BITS;
	}
	colorMode = m_bitCount / 8;

	// récupère les infos sur les données de l'image
	imagePos = CTOI(header[0x0A]);
	imageSize = CTOI(header[0x22]);
	// récupère les dimensions de l'image
	m_width = CTOI(header[0x12]);
	m_height = CTOI(header[0x16]);	
		
	// si les infos sur les données de l'image n'ont pas été récupéré
	// on les calcule
	if (imageSize==0)
		imageSize=m_height*m_width*colorMode;
	if (imagePos==0)
		imagePos=0x36;

	// charge les données de l'image
	fseek(filePtr,imagePos,0);
	m_data = (unsigned char*) malloc(sizeof(unsigned char) * imageSize);
	
	if (!m_data) {
		fclose(filePtr);
		return BMP_BAD_DATA;
	}

	if (fread(m_data,1,imageSize,filePtr) != (unsigned long)imageSize) 
	{
		free(m_data);
		fclose(filePtr);
		return BMP_BAD_DATA;
	}
	
	fclose(filePtr);

	// dans les images BMP les couleurs des pixels sont en mode BGR
	// transformation en mode RGB
	if (m_bitCount == 24)
	for (imageIdx=0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = m_data[imageIdx];
		m_data[imageIdx] = m_data[imageIdx + 2];
		m_data[imageIdx + 2] = colorSwap;
	}
	
	// Format de l'image RGB ou niveau de gris
	switch (m_bitCount) {
		case 8: m_texFormat = GL_LUMINANCE; break;
		case 24: m_texFormat = GL_RGB; break;
	}
	
	return BMP_OK;
}


// ====================================================================
// Retourne le format OpenGL de l'image (GL_RGB, GL_RGBA, GL_LUMINANCE)
// ====================================================================
GLenum CBmp::GetTextureFormat()
{
	return m_texFormat;
}


// ==================================================
// Retourne le nombre de pixels en largeur de l'image
// ==================================================
short int CBmp::GetWidth()
{
	return m_width;
}


// ==================================================
// Retourne le nombre de pixels en hauteur de l'image
// ==================================================
short int CBmp::GetHeight()
{
	return m_height;
}


// ===============================================================================
// Retourne le nombre de bits par pixel (RGB = 24, RGBA = 32, Niveaux de gris = 8)
// ===============================================================================
unsigned char CBmp::GetBitCount()
{
	return m_bitCount;
}


// ===================================================
// Retourne le tableau contenant les pixels de l'image
// ===================================================
unsigned char * CBmp::GetData()
{
	return m_data;
}


// ================================================================
// Fonction permettant de tester si un entier est une puisance de 2
// ================================================================
bool CBmp::CheckSize(int x)
{
    if (x == 2	 || x == 4 || 
        x == 8	 || x == 16 || 
        x == 32  || x == 64 ||
        x == 128 || x == 256 || 
	x == 512 || x == 1024)
        return true;
    else return false;
}


// ===================================================
// Creation d'une texture a partir de l'image courante
// ===================================================
int CBmp::CreateTexture(GLuint textureArray[], GLuint textureID, bool mipmapping, GLint textureWrap)
{
	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);
		
	if (!mipmapping) {
		// filtrage plus rapide
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		glTexImage2D(GL_TEXTURE_2D, 0,  m_texFormat, m_width, m_height, 
			0,  m_texFormat, GL_UNSIGNED_BYTE, m_data);
	}
	else {
		// Mipmapping: meilleur qualité d'affichage mais plus lent
		gluBuild2DMipmaps(GL_TEXTURE_2D, m_texFormat, m_width, m_height, m_texFormat, GL_UNSIGNED_BYTE, m_data);

		// filtrage offrant une meilleur qualité	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	}

	// l'option GL_CLAMP_TO_EDGE permet de ne pas répéter la texture comme GL_REPEAT
	// et évite donc des effets indésirables, de plus elle permet de ne pas voir
	// les bordures des textures contrairement à GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);

	//delete m_data;

	return 1;
}


// ================================================
// Creation d'une texture a partir d'un fichier BMP
// ================================================
int CBmp::CreateTexture(char* filename, GLuint textureArray[], GLuint textureID, bool mipmapping, GLint textureWrap)
{
	CBmp bmp = CBmp();
	if (bmp.Load(filename) != BMP_OK) return -1;
	
	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);
		
	if (!mipmapping) {
		// filtrage plus rapide
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		glTexImage2D(GL_TEXTURE_2D, 0,  bmp.m_texFormat, bmp.m_width, bmp.m_height, 
			0,  bmp.m_texFormat, GL_UNSIGNED_BYTE, bmp.m_data);
	}
	else {
		// Mipmapping: meilleur qualité d'affichage mais plus lent
		gluBuild2DMipmaps(GL_TEXTURE_2D, bmp.m_texFormat, bmp.m_width, bmp.m_height, bmp.m_texFormat, GL_UNSIGNED_BYTE, bmp.m_data);

		// filtrage offrant une meilleur qualité	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	}
	
	// l'option GL_CLAMP_TO_EDGE permet de ne pas répéter la texture comme GL_REPEAT
	// et évite donc des effets indésirables, de plus elle permet de ne pas voir
	// les bordures des textures contrairement à GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);

	return 1;
}


/* Structure d'un fichier BMP 24 bits
 * Le format BMP est divisé en 3 parties le header,
 * la zone bitmap info et les données
 *
 * Le header
 * Position		Type		Description
 * 00h			DB "BM"		BM indique qu'il s'agit d'un fichier bitmap
 * 02h			DD ?		Taille du fichier en octets
 * 06h			DW 0		Réservé
 * 08h			DW 0		Réservé
 * 0Ah			DD ?		Offset des données de l'image
 *
 * La zone bitmap info
 * Position		Type		Description
 * OEh			DD ?		Taille de la zone bitmap info
 * 12h			DD ?		Largeur de l'image en pixels
 * 16h			DD ?		Hauteur de l'image en pixels
 * 1Ah			DW 1		Nombre de plans (1)
 * 1Ch			DW 1|4|8|24	Bits par pixel
 * 1Eh			DD 0|1|2	Format de compression (O=non compressée)
 * 22h			DD ?		Taille de l'image en octets
 * 26h			DD ?		Résolution horizontale en pixels par mètre
 * 2Ah			DD ?		Résolution verticale en pixels par mètre
 * 2Eh			DD ?		Nombre de couleurs utilisées  ...
 * 32h			DD ?		Nombre d'index de couleurs importants pour l'affichage
 *
 */
 
 
 
 
