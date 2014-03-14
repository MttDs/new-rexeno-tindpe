#include "aircraft.hh"
#include "3dmodel.hh"
#include <GL/glut.h>

Aircraft::Aircraft(const ShapeInfo& si,
		   VariableManager& vm,
		   Trial * father): _isTextured(false){

  assert(si.attributes.size() == 8);

  _name = si.attributes[0];
  _id = 10;

  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_z = new Variable(si.attributes[3]));
  vm.addVariable(_frameStart = new Variable(si.attributes[4]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[5]));
  vm.addVariable(_R = new Variable(255));
  vm.addVariable(_G = new Variable(255));
  vm.addVariable(_B = new Variable(255));
  vm.addVariable(_veloX = new Variable(si.attributes[6]));
  vm.addVariable(_dir = new Variable(si.attributes[7]));

 const char *file ="aircraft/aircraft.3ds";
 

 if (_load3ds.Import3DS(&_model3ds, file)== false){
      printf("Erreur lors de l'importation du fichier 3ds\n");
      exit(0);
 }


}

Aircraft::~Aircraft(){
}

void Aircraft::Display(){
  	glEnable(GL_COLOR_MATERIAL);
  if (_isTextured == false){
 
    _model3ds.LoadTextures();
    _isTextured = true;
  }	
  glPushMatrix();

  glTranslatef(0,5.0,-600.0);
  // Rotation du model sur X
  // glRotatef(0.3, 0,0, 1);
  glScalef(0.2f,0.2f,0.2f);
  
  // Dessine le model 
 _model3ds.Draw();
  glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);


}

string 
Aircraft::getAttrsToString(){
  return "";
}
