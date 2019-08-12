#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Screen.h" 
#include "Shaders.h"
#include "GameMesh.h"
#include "Textures.h"
#include "transform.h"
#include "Sounds.h"
#include "Overlays.h"

enum class GameState { PLAY, EXIT };

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	GLuint skyboxVAO, skyboxVBO, cubemapTexture;
	vector<std::string> faces;

	void systemsInitialise();
	void inputCheck();
	void updateGame();
	void gameDraw();
	bool checkCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playSound(unsigned int Source, glm::vec3 pos);
	void effectBlob();
	void ToonLighting();
	void RimShader();
	void RimToon();
	void setLighting();
	void LightingBP();
	void LightingADS();
	void LightingADSFog();
	void Skybox();
	void Reflection();
	void Fog();
	void ShaderEffect(int effectInt);

	Screen _gameDisplay;
	GameState _gameState;
	GameMesh mesh1;
	GameMesh mesh2;
	GameMesh mesh3;
	GameMesh mesh4;
	GameMesh mesh5;
	GameMesh mesh6;
	GameMesh mesh7;
	GameMesh mesh8;
	GameMesh mesh9;
	GameMesh mesh10;
	GameMesh mesh11;
	GameMesh mesh12;
	Textures texture;
	Textures texture1;
	Textures texture2;
	Textures skybox;
	Overlays overlay;
	Shaders shaderToon;
	Shaders shaderRim;
	Shaders shaderRimToon;
	Shaders shaderLighting;
	Shaders shaderBP;
	Shaders shaderADS;
	Shaders shaderADSFog;
	Shaders shaderSkybox;
	Shaders shaderReflection;
	Shaders shaderFog;

	glm::mat4 modelView;

	Camera camera;
	Sounds audioDevice;

	float rotation;
	unsigned int whistle;
	unsigned int backGroundMusic;
	int effectInt;
};

