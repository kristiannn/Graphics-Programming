#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& texCoord)
	{
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Sphere
{
public:

	Sphere() {}

	Sphere(glm::vec3& position, float radius)
	{
		this->position = position;
	}

	glm::vec3 GetPosition() { return position; }
	float GetRadius() { return radius; }

	void SetPosition(glm::vec3 position)
	{
		this->position = position;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 position;
	float radius;
};

class GameMesh
{
public:
	GameMesh();
	~GameMesh();


	void drawGame();
	void initialise(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initialiseModel(const IndexedModel& model);
	void updateSphere(glm::vec3 position, float radius);
	glm::vec3 SpherePosition() { return meshSphere.GetPosition(); }
	float SphereRadius() { return meshSphere.GetRadius(); }

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere meshSphere;
	GLuint vertexArrayObj;
	GLuint vertexArrayBuff[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};