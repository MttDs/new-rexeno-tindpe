/*
 * 05/28/2003
 *
 * bmp.h
 * Classe permettant la lecture, l'ecriture d'image BMP
 * ainsi que la creation de textures 
 *
 * 2003 Thierry Vouriot (Yéri)
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

#ifndef _BMP_H
#define _BMP_H

#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F	
#endif

// Codes erreurs de retour des fonctions
enum BMPErrors
{
	BMP_FILE_NOT_FOUND,
	BMP_BAD_IMAGE_TYPE,
	BMP_BAD_BITS,
	BMP_BAD_DATA,
	BMP_FILE_NOT_CREATE,
	BMP_BAD_SIZE,
	BMP_OK
};

// ###########
// Classe CBmp
// ###########
class CBmp
{
public:

	// ============
	// Constructeur
	// ============
	CBmp();

	// ===========
	// Destructeur
	// ===========
	~CBmp();
	
	// ======================================================
	// Fonction lisant un fichier BMP 8 ou 24 (non compresse)
	// ======================================================
	int Load(char *filename);

	// ====================================================================
	// Retourne le format OpenGL de l'image (GL_RGB, GL_RGBA, GL_LUMINANCE)
	// ====================================================================
	GLenum GetTextureFormat();

	// ==================================================
	// Retourne le nombre de pixels en largeur de l'image
	// ==================================================
	short int GetWidth();

	// ==================================================
	// Retourne le nombre de pixels en hauteur de l'image
	// ==================================================
	short int GetHeight();

	// ===============================================================================
	// Retourne le nombre de bits par pixel (RGB = 24, RGBA = 32, Niveaux de gris = 8)
	// ===============================================================================
	unsigned char GetBitCount();

	// ===================================================
	// Retourne le tableau contenant les pixels de l'image
	// ===================================================
	unsigned char * GetData();

	// ================================================================
	// Fonction permettant de tester si un entier est une puisance de 2
	// ================================================================
	bool static CheckSize(int x);

	// ===================================================
	// Creation d'une texture a partir de l'image courante
	// ===================================================
	int CreateTexture(GLuint textureArray[], GLuint textureID, bool mipmapping, GLint textureWrap = GL_REPEAT);

	// ================================================
	// Creation d'une texture a partir d'un fichier BMP
	// ================================================
	int static CreateTexture(char* filename, GLuint textureArray[], GLuint textureID, bool mipmapping, GLint textureWrap = GL_REPEAT);
	
private:

	// Format OpenGL de l'image (GL_RGB, GL_RGBA, GL_LUMINANCE)
	GLenum m_texFormat;

	// Nombre de pixels en largeur de l'image
	short int m_width;

	// Nombre de pixels en hauteur de l'image
	short int m_height;

	// Nombre de bits par pixel (RGB = 24, RGBA = 32, Niveaux de gris = 8)
	unsigned char m_bitCount;

	// Tableau contenant les pixels de l'image
	unsigned char *m_data;

};

#endif



