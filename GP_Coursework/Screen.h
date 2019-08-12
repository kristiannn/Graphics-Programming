#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Screen
{
public:
	Screen();
	~Screen();
	void displayInitialise();
	void swapBuffer();
	void displayClear(float r, float g, float b, float a);

	float getDisplayWidth();
	float getDisplayHeight();

private:

	void returnError(std::string errorString);

	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	float displayWidth;
	float displayHeight;
};

