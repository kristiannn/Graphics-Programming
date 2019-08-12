#pragma once
#include <string>
#include <GL\glew.h>
#include <vector>

class Textures
{
public:
	Textures();

	void Bind(unsigned int unit); // bind upto 32 textures
	void initialise(const std::string& fileName);
	GLuint loadCubemap(std::vector<std::string> faces);
	~Textures();
	GLint getTexHandler() { return textHandler; }

protected:
private:

	GLuint textHandler;
};

