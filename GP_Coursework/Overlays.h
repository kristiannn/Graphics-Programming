#pragma once
#include <string>
#include "Textures.h"
#include "Screen.h"
#include "GameMesh.h"
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <vector>


class Overlays
{
public:
	Overlays();
	~Overlays();
	void olDraw(GLuint program);
	void init(const std::string& fileName);

private:
	Textures textures;
};

