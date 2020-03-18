#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "Sierpinski.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

    // Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));

#pragma region Ejercicio1
	gObjects.push_back(new Poligono(3, 500)); //Triángulo
	gObjects.back()->setMColor({ 255.0, 255.0, 0.0, 1.0 }); //Asignamos amarillo al triángulo
	gObjects.push_back(new Poligono(360, 500)); //Circunferencia
	gObjects.back()->setMColor({255.0, 0.0, 255.0, 1.0}); //Asignamos magenta al triángulo
#pragma endregion
#pragma region Ejercicio2
	gObjects.push_back(new Sierpinski(10000, 100));
	gObjects.back()->setMColor({ 255.0, 0.0, 255.0, 1.0 }); //Asignamos magenta a Sierpinski
#pragma endregion
#pragma region Ejercicio3
	gObjects.push_back(new TrianguloRGB(500));
#pragma endregion
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------


