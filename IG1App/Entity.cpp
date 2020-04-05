#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}

#pragma region Implementaci�n
/*void Abs_Entity::update() {

}*/
#pragma endregion


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

#pragma region Implementaci�n 1.0
#pragma region Poligono
Poligono::Poligono(GLuint numL_, GLdouble rd_) : numL(numL_), rd(rd_) {
	mMesh = Mesh::generaPoligono(numL, rd);
}

Poligono::~Poligono() {
	delete mMesh; mMesh = nullptr;
}
void Poligono::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		mMesh->render();

		//Reseteamos aributos
		glLineWidth(1);
		glColor3d(1, 1, 1);
		if(mTexture != nullptr) mTexture->unbind();
	}
}
#pragma endregion
#pragma region Sierpinski
Sierpinski::Sierpinski(GLdouble rd_, GLuint numP_) : numP(numP_), rd(rd_) {
	mMesh = Mesh::generaSierpinski(rd, numP);
}

Sierpinski::~Sierpinski() {
	delete mMesh; mMesh = nullptr;
}

void Sierpinski::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor4dv(value_ptr(mColor));
		glPointSize(2);
		mMesh->render();

		//Reseteamos atributos
		glPointSize(1);
		glColor4dv(value_ptr(glm::dvec4(1.0, 1.0, 1.0, 1.0)));
	}
}
#pragma endregion
#pragma region Tri�nguloRGB
TrianguloRGB::TrianguloRGB(GLdouble rd_) : rd(rd_) {
	mMesh = Mesh::generaTrianguloRGB(rd);
	transform = dmat4(1);
}

TrianguloRGB::~TrianguloRGB() {
	delete mMesh; mMesh = nullptr;
}

void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		glPolygonMode(GL_BACK, GL_LINE); //Para que no se rellene la parte trasera del tri�ngulo.
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		mMesh->render();

		//Reseteamos aributos
		glLineWidth(1);
		glColor3d(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if(mTexture != nullptr) mTexture->unbind();
	}
}

//Se encarga del movimiento
void TrianguloRGB::update() {
	angulo++;
	posCfc.x = 300 * cos(radians(angulo));
	posCfc.y = 300 * sin(radians(angulo));
	setModelMat(translate(transform, posCfc));
	setModelMat(rotate(modelMat(), radians(angulo), dvec3(0.0, 0.0, 1.0)));
}
#pragma endregion
#pragma region Rect�nguloRGB

RectanguloRGB::RectanguloRGB(GLdouble w_, GLdouble h_) :width(w_), height(h_) {
	mMesh = Mesh::generaRectanguloRGB(width,height);
	setModelMat(translate(dmat4(1), dvec3(0.0, 0.0, -100.0)));
}

RectanguloRGB::~RectanguloRGB() {
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		glPolygonMode(GL_BACK, GL_LINE);
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		mMesh->render();

		//Reseteamos aributos
		glLineWidth(1);
		glColor3d(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if(mTexture != nullptr) mTexture->unbind();
	}
}

#pragma endregion
#pragma endregion
#pragma region Implementaci�n 1.1
#pragma region Estrella3D
Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h) : re_(re), np_(np), h_(h) {
	mMesh = Mesh::generaEstrella3D(re_, np_, h_);
	transform = dmat4(1);
	setModelMat(translate(transform, dvec3({ -50.0, 250.0, -50.0 })));
}

Estrella3D::~Estrella3D() {
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat * transform;  //glm matrix multiplication
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		upload(aMat);
		glLineWidth(2);
		mMesh->render();

		//Segunda estrella
		aMat = rotate(aMat, radians(180.0), dvec3(0, 1, 0));
		upload(aMat);
		mMesh->render();

		//Reseteamos aributos
		glLineWidth(1);
		if (mTexture != nullptr) mTexture->unbind();
	}
}

void Estrella3D::update() {
	angulo++;
	setModelMat(translate(transform, dvec3({ -50.0, 250.0, -50.0 })));
	setModelMat(rotate(modelMat(), radians(angulo), dvec3(0.0, 1.0, 0.0)));
	setModelMat(rotate(modelMat(), radians(angulo), dvec3(0.0, 0.0, 1.0)));
}
#pragma endregion
#pragma region Suelo

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint rh): w_(w), h_(h), rw_(rw), rh_(rh) {
	mMesh = Mesh::generaRectanguloTexCor(w_, h_, rw_, rh_);
	transform = dmat4(1);
	setModelMat(rotate(transform, radians(90.0), dvec3(1.0, 0.0, 0.0)));
}

Suelo::~Suelo() {
	delete mMesh; mMesh = nullptr;
}
//	virtual void render(glm::dmat4 const& modelViewMat) const {};
void Suelo::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  //glm matrix multiplication
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		upload(aMat);
		glLineWidth(2);
		mMesh->render();

		//Reseteamos aributos
		glLineWidth(1);
		if (mTexture != nullptr) mTexture->unbind();
	}
}

#pragma endregion
#pragma region Caja
Caja::Caja(GLdouble ld) {
	mMesh = Mesh::generaCajaTexCor(ld);
	transform = dmat4(1);
}

Caja::~Caja() {
	delete mMesh; mMesh = nullptr;
}

void Caja::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  //glm matrix multiplication
		glEnable(GL_CULL_FACE); //Habilita el modo para renderizar la caja por dentro o por fuera

		//Renderiza el exterior de la caja
		glCullFace(GL_BACK);
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		upload(aMat);
		mMesh->render();

		//Renderiza el interior de la caja
		glCullFace(GL_FRONT);
		if (mTextureInt != nullptr) mTextureInt->bind(GL_REPLACE);
		upload(aMat);
		mMesh->render();

		//Reseteamos aributos
		if (mTexture != nullptr) mTexture->unbind();
		if (mTextureInt != nullptr) mTextureInt->unbind();
		glDisable(GL_CULL_FACE);
	}
}
#pragma endregion
#pragma region Foto
Foto::Foto(GLdouble w, GLdouble h) : w_(w), h_(h) {	
	mMesh = Mesh::generaFoto(w, h);
	transform = dmat4(1);
	setModelMat(translate(transform, dvec3(0, 1, 0)));
	setModelMat(rotate(modelMat(), radians(90.0), dvec3(1, 0, 0)));
}

Foto::~Foto() {
	delete mMesh; mMesh = nullptr;
}

void Foto::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  //glm matrix multiplication
		if (mTexture != nullptr) {
			mTexture->bind(GL_REPLACE);
			mTexture->loadColorBuffer();
		}
		upload(aMat);
		mMesh->render();

		//Reseteamos aributos
		if (mTexture != nullptr) mTexture->unbind();
	}
}

void Foto::update() {
}
#pragma endregion

#pragma endregion

//-------------------------------------------------------------------------

Cristal::Cristal(GLdouble w, GLdouble h) : w_(w), h_(h)
{
	mMesh = Mesh::generaCajaRectangulo(w, h);
	transform = dmat4(1);
}

Cristal::~Cristal()
{
	delete mMesh;
}

void Cristal::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		dmat4 aMat = modelViewMat * mModelMat;  //glm matrix multiplication
		if (mTexture != nullptr) mTexture->bind(GL_REPLACE);
		upload(aMat);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

		mMesh->render();

		//Reseteamos aributos
		if (mTexture != nullptr) mTexture->unbind();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
}
