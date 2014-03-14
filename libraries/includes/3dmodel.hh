/*
 * 10/07/2003
 *
 * 3dmodel.h
 * Classe et structures representant un model 3D
 *
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

#ifndef _3DMODEL_H
#define _3DMODEL_H

#include <vector>
#include <GL/glut.h>
#include "vector.hh"
#include <string.h>
#include "bmp.hh"

using namespace std;

// Face composées de 3 points et de 3 coordonnées de texture
typedef struct
{
	int vertIndex[3];
	int coordIndex[3];
} tFace;

// Objet 3D
typedef struct 
{
	int  numOfVerts;			// Nombre de points
	int  numOfFaces;			// Nombre de faces
	int  numTexVertex;			// Nombre de coordonnées de texture
	int  materialID;			// Texture ID, dans le tableau de textures de la classe C3DModel
	bool bHasTexture;			// Vrai si l'objet a une texture
	char strName[255];			// Nom de l'objet
	CVector3  *pVerts;			// Points de l'objet
	CVector3  *pNormals;		// Normales de l'objet
	CVector2  *pTexVerts;		// Coordonnées de textures
	tFace *pFaces;				// Faces de l'objet
} t3DObject;

// Info d'un materiel (texture)
typedef struct 
{
	char  strName[255];			// Nom de la texture
	char  strFile[255];			// Fichier contenant la texture
	unsigned char color[3];		// Couleur (R, G, B)
	int   texureId;				// Texture ID
	float uTile;				// u tiling of texture  (Currently not used)
	float vTile;				// v tiling of texture	(Currently not used)
	float uOffset;			    // u offset of texture	(Currently not used)
	float vOffset;				// v offset of texture	(Currently not used)
} tMaterialInfo;


// ###############
// Classe C3DModel
// ###############
class C3DModel 
{

public:
	// Nombre d'objets du model
	int numOfObjects;
	// Nombre de materiels pour le model
	int numOfMaterials;
	// Liste des infos de materiel (textures et couleurs)
	vector<tMaterialInfo> pMaterials;
	// Liste des objets du model
	vector<t3DObject> pObject;

	// ============
	// Constructeur
	// ============
	C3DModel();

	// ===========
	// Destructeur
	// ===========
	~C3DModel();

	// ===============
	// Détruit l'objet
	// ===============
	void Destroy();

	// ============================
	// Charge les textures du model
	// ============================
	int LoadTextures();

	// ================
	// Dessine le model
	// ================
	void Draw();

private:

	// Nombre maximum de textures
	#define MAX_TEXTURES  100

	// Tableau contenant les ids des textures du model
	GLuint m_textures[MAX_TEXTURES];						// This holds the texture info, referenced by an ID

};

#endif

