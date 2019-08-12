#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Sounds
{
	struct data {
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		data(unsigned int sourceID, unsigned int bufferID, char* buffer, const char* name)
		{
			this->sourceID = sourceID;
			this->bufferID = bufferID;
			this->buffer = buffer;
			this->name = name;
		}

	};

	struct Vector3
	{
		float x, y, z;
	};
	std::vector<data> datas;
	ALCcontext* context;
	ALCdevice *device;
	bool BigEndian();
	int convertToInt(char* buffer, int length);
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	Sounds();
	~Sounds();
	unsigned int loadSound(const char* filename);
	void deleteSound(unsigned int id);
	void playSound(unsigned int id);
	void playSound(unsigned int id, glm::vec3& pos);
	void stopSound(unsigned int id);
	void setlistener(glm::vec3& pos, glm::vec3& camLookAt);

private:

};

