/*
 * 10/07/2003
 *
 * 3dmodel.cpp
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

#include "3dmodel.hh"
#include "stdio.h"
#include "string.h"
// ###############
// Classe C3DModel
// ###############

// ============
// Constructeur
// ============
C3DModel::C3DModel() 
{ 
	numOfObjects = 0;
	numOfMaterials = 0;
	for (int i=0; i<MAX_TEXTURES; i++) m_textures[i] = 0;
}


// ===========
// Destructeur
// ===========
C3DModel::~C3DModel() 
{ 
	Destroy();
}


// ===============
// Détruit l'objet
// ===============
void C3DModel::Destroy()
{
	numOfObjects = 0;
	numOfMaterials = 0;
	pObject.clear();
	pMaterials.clear();
	glDeleteTextures(MAX_TEXTURES, m_textures);
}


// ============================
// Charge les textures du model
// ============================
int C3DModel::LoadTextures()
{
	// Charge uniquement les textures au format BMP

	// Pour tous les materiels
	for(int i = 0; i < numOfMaterials; i++)
	{
		// regarde si il y un fichier texture
		if(strlen(pMaterials[i].strFile) > 0)
		{
			if (CBmp::CreateTexture(pMaterials[i].strFile, m_textures, i, true) == -1) {
				printf("Cannot load texture : %s\n", pMaterials[i].strFile);
			}	
		}
		// Change le texture ID pour ce materiel
		pMaterials[i].texureId = i;
	}

	return 1;
}


// ================
// Dessine le model
// ================
void C3DModel::Draw() 
{ 

	// Pour tous les objets du model

	for(int i = 0; i < numOfObjects; i++)
	{
		// On regarde si on a une liste valide d'objets
		if(pObject.size() <= 0) break;

       	// Recupere l'objet courant qu'on va afficher
		t3DObject *object = &(pObject[i]);
			int spec[4] = {1,1,0,1};
			int light[4] = {0,0,4,0};

			glMaterialiv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
			glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 2);
			glLightiv(GL_LIGHT0, GL_POSITION, light);
		// Si l'objet a une texture
		if(object->bHasTexture) {

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, m_textures[object->materialID]);
		} 
		else {
			glDisable(GL_TEXTURE_2D);	
		}

		// Couleur par défaut
		glColor3ub(255, 128, 0);

		// Dessine l'objet
		glBegin(GL_TRIANGLES);

			// Pour toutes les faces de l'objet
			for(int j = 0; j < object->numOfFaces; j++)
			{
				// Pour chaque sommet d'une face
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// Recupere l'index du point courant
					int index = object->pFaces[j].vertIndex[whichVertex];
			
					// Donne à OpenGL la normale en ce point
					glNormal3f(object->pNormals[ index ].x, object->pNormals[ index ].y, object->pNormals[ index ].z);
				
					// Si l'objet a une texture, on donne a OpenGL la coordonnee de texture
					if(object->bHasTexture) {
						if(object->pTexVerts) {	// Verifie la validite du tableau des coordonnees
							glTexCoord2f(object->pTexVerts[ index ].x, object->pTexVerts[ index ].y);
						}
					} else {
						// Si il existe un materiel pour cet objet
						if(pMaterials.size() && object->materialID >= 0) 
						{
							// Recupere la couleur du materiel
							unsigned char *pColor = pMaterials[object->materialID].color;

							// Assigne la couleur du materiel au point courant
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}

					// Donne a OpenGL, les coordoonees du point courant
					glVertex3f(object->pVerts[ index ].x, object->pVerts[ index ].y, object->pVerts[ index ].z);
				}
			}
		glEnd();
	}
}

