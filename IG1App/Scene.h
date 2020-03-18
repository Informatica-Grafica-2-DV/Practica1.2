//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>
#include "Texture.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;
#pragma region implementación1.0
	void update();
#pragma endregion
#pragma region implementación1.1
	void setState(int id_);
	void initScene0();
	void initScene1();
	void chargeTextures();
	int getState() { return mId; };
#pragma endregion


protected:
#pragma region implementación1.1
	std::vector<Texture*> gTextures;
	int mId = 0;
#pragma endregion
	void free();
	void setGL();
	void resetGL();
	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

