#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

#pragma region Implementación Enunciado
//Genera polígonos
Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {
    GLdouble angulo = 90;
    Mesh* poligono = new Mesh();
    poligono->mPrimitive = GL_LINE_LOOP;

    poligono->mNumVertices = numL;
    poligono->vVertices.reserve(poligono->mNumVertices);
    for (int i = 0; i < numL; i++) {
        poligono->vVertices.emplace_back(rd * cos(radians(angulo)), rd * sin(radians(angulo)), 0.0);
        angulo += 360 / numL;
    }

    return poligono;
}

//Genera triángulos de Sierpinski
Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
    Mesh* triangulo = generaPoligono(3, rd); //Genera triángulo exterior
    Mesh* sierpinski = new Mesh(); //Mesh para los puntos dentro del triángulo
    sierpinski->mPrimitive = GL_POINTS;//Utilizamos la primitiva de puntos

    sierpinski->mNumVertices = numP;
    sierpinski->vVertices.reserve(sierpinski->mNumVertices);
    for (int i = 0; i < 3; i++) {
        sierpinski->vVertices.emplace_back(triangulo->vVertices.at(i));
    }

    dvec3 ult = sierpinski->vVertices.back();
    for (int i = 0; i < numP - 3; i++) {
        dvec3 puntoAleatorio = triangulo->vVertices[rand() % 3];
        ult = (ult + puntoAleatorio) / 2.0;
        sierpinski->vVertices.emplace_back(ult);
    }
    delete triangulo; triangulo = nullptr;

    return sierpinski;
}

Mesh* Mesh::generaTrianguloRGB(GLdouble rd) {
    Mesh* triangulo = generaPoligono(3, rd); //Generamos el triángulo
    triangulo->mPrimitive = GL_TRIANGLES;

    //Añade el vector de colores
    triangulo->vColors.reserve(triangulo->mNumVertices);
    // X axis color: red  (Alpha = 1 : fully opaque)
    triangulo->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    // Y axis color: green
    triangulo->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    // Z axis color: blue
    triangulo->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

    return triangulo;
}
#pragma endregion