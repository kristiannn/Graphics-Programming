#include "Game.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

Game::Game()
{
	_gameState = GameState::PLAY;
	Screen* _gameDisplay = new Screen(); //new display
}

Game::~Game()
{
}

/*
This method is being executed at the start of the program by the main method
it runs the systemsinitalise method which sets up the game
and then the updategame method which keeps it running and updates its data
*/
void Game::run()
{
	systemsInitialise();
	updateGame();
}


/*
This method is run on game execution by the run method
it initialises the display (sdl window)
loads the models and sounds and initialises the camera
sets values for variables
*/
void Game::systemsInitialise()
{
	effectInt = 0; //sets the default shader effect for the main object to reflection
	rotation = 1.0f; //sets the default value for the rotation float
	_gameDisplay.displayInitialise(); //initialises display

									  //Load sounds
	whistle = audioDevice.loadSound("..\\res\\bang.wav");
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");

	//Load textures
	texture.initialise("..\\res\\bricks.jpg"); //load texture
	texture1.initialise("..\\res\\water.jpg"); //load texture
	texture2.initialise("..\\res\\effect.png"); //load texture

												//Load all shaders
	shaderSkybox.initialise("..\\res\\shaderSkybox.vert", "..\\res\\shaderSkybox.frag");
	shaderReflection.initialise("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");
	shaderBP.initialise("..\\res\\shaderBP.vert", "..\\res\\shaderBP.frag");
	shaderADS.initialise("..\\res\\shaderADS.vert", "..\\res\\shaderADS.frag");
	shaderADSFog.initialise("..\\res\\shaderADSFog.vert", "..\\res\\shaderADSFog.frag");
	shaderToon.initialise("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag");
	shaderRim.initialise("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	shaderRimToon.initialise("..\\res\\shaderRimToon.vert", "..\\res\\shaderRimToon.frag");
	shaderLighting.initialise("..\\res\\shaderLighting.vert", "..\\res\\shaderLighting.frag");
	shaderFog.initialise("..\\res\\shaderFog.vert", "..\\res\\shaderFog.frag");
	//Vertex2D vertices[] = { Vertex2D(glm::vec2(-0.5, 1.0), glm::vec2(0.0, 0.0)),
	//						Vertex2D(glm::vec2(0.5, 0.5), glm::vec2(1.0, 0.0)),
	//						Vertex2D(glm::vec2(0.5,-0.5), glm::vec2(1.0, 1.0)),
	//						Vertex2D(glm::vec2(-0.5,-0.5), glm::vec2(0.0, 1.0)) };

	overlay.init("..\\res\\bricks.jpg");

	//Load all models
	mesh1.loadModel("..\\res\\monkey3.obj");
	mesh2.loadModel("..\\res\\rock.obj");
	mesh3.loadModel("..\\res\\f.obj");
	mesh4.loadModel("..\\res\\monkey3.obj");
	mesh5.loadModel("..\\res\\monkey3.obj");
	mesh6.loadModel("..\\res\\monkey3.obj");
	mesh7.loadModel("..\\res\\monkey3.obj");
	mesh8.loadModel("..\\res\\monkey3.obj");
	mesh9.loadModel("..\\res\\monkey3.obj");
	mesh10.loadModel("..\\res\\monkey3.obj");
	mesh11.loadModel("..\\res\\monkey3.obj");
	mesh12.loadModel("..\\res\\monkey3.obj");

	/*
	Load skybox textures
	Order is very important and must not be changed
	due to the way cubemaps work and are being rendered
	*/
	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};
	cubemapTexture = skybox.loadCubemap(faces); //Load the cubemap using "faces" into cubemapTextures


												//The position of the vertices of the skybox, also changes its size
	float skyboxVertices[] = {
		// positions          
		-6.0f,  6.0f, -6.0f,
		-6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f, -6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,

		-6.0f, -6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f, -6.0f,  6.0f,
		-6.0f, -6.0f,  6.0f,

		-6.0f,  6.0f, -6.0f,
		6.0f,  6.0f, -6.0f,
		6.0f,  6.0f,  6.0f,
		6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f,  6.0f,
		-6.0f,  6.0f, -6.0f,

		-6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		6.0f, -6.0f, -6.0f,
		6.0f, -6.0f, -6.0f,
		-6.0f, -6.0f,  6.0f,
		6.0f, -6.0f,  6.0f
	};

	//use openGL functionality to generate & bind data into buffers
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//Initialise the camera
	camera.cameraInitialise(glm::vec3(0, 0, -10.0), 70.0f, (float)_gameDisplay.getDisplayWidth() / _gameDisplay.getDisplayHeight(), 0.01f, 1000.0f);
}


/*
this method is an infinite loop until the game state is set to EXIT
it checks for input, draws the game & checks for collisions
*/
void Game::updateGame()
{
	while (_gameState != GameState::EXIT)
	{
		inputCheck();
		gameDraw();
		checkCollision(mesh1.SpherePosition(), mesh1.SphereRadius(), mesh2.SpherePosition(), mesh2.SphereRadius());
		playSound(backGroundMusic, glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

/*
This method checks for events through SDL_Event
It sets the gamestate to exit if the quit function is activated
Also checks if any key is pressed through evnt.key.keysym.sym
*/
void Game::inputCheck()
{
	SDL_Event evnt; //Instance of SDL_Event type

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type) //checks the event type
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT; //sets gamestate to EXIT
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym) //checks which key is being pressed
			{
				/*
				Checks if effectInt is within the correct range and
				increases/decreases it upon button press if it is
				effectInt is used to change the current shader effect
				on the first (main) mesh
				*/
			case SDLK_RIGHT:
				if (effectInt < 8)
					effectInt++;
				break;
			case SDLK_LEFT:
				if (effectInt > 0)
					effectInt--;
				break;
			}
		}
	}

}

/*
Takes in the position and radius of two objects
Checks if the two objects occupy the same world space
if they do it sets listener position to the camera position and the orientation to the first object position
in order for the sound to come from the first object's direction
plays the sound, prints Collision for debug purposes and returns true
if the objects don't collide the method simply returns false
*/
bool Game::checkCollision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		audioDevice.setlistener(camera.getCameraPosition(), m1Pos); //add bool to mesh
																	//playAudio(whistle, m1Pos);
		printf("\n Collision");
		return true;
	}
	else
	{
		return false;
	}
}

void Game::playSound(unsigned int Source, glm::vec3 pos)
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		//audioDevice.playSound(Source, pos);
	}
}

/*
Sets all the uniforms for the shader
*/
void Game::Reflection()
{
	shaderReflection.setMat4("model", transform.GetModel());
	shaderReflection.setMat4("view", camera.GetView());
	shaderReflection.setMat4("projection", camera.GetProjection());
	shaderReflection.setVec3("cameraPos", camera.getCameraPosition());
	shaderReflection.setInt("skybox", 0);
}

/*
Sets all the variables for the skybox to work properly
Disables depth writing so the skybox is always drawn in the background
Sets the uniforms for the shader
Sets up the skybox cube
Returns the depth writing to default
*/
void Game::Skybox()
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shaderSkybox.BindToGPU();
	shaderSkybox.setInt("skybox", 0);
	//view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	shaderSkybox.setMat4("view", camera.GetView());
	shaderSkybox.setMat4("projection", camera.GetProjection());
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

/*
Sets all the uniforms for the shader
Sets lightPos's position to 5,5,5, this can be manually changed to any position
*/
void Game::LightingBP()
{
	shaderBP.setMat4("view", camera.GetView());
	shaderBP.setMat4("projection", camera.GetProjection());
	shaderBP.setMat4("model", transform.GetModel());

	shaderBP.setVec3("viewPos", camera.getCameraPosition());
	shaderBP.setVec3("lightPos", glm::vec3(5, 5, 5));
}


/*
Sets objectColor, lightColor and lightPos to preset values
Sets all the uniforms for the shader
*/
void Game::LightingADS()
{
	shaderADS.setVec3("objectColor", 0.5f, 0.5f, 1.0f);
	shaderADS.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shaderADS.setVec3("lightPos", 5.0f, 5.0f, 5.0f);
	shaderADS.setVec3("viewPos", camera.getCameraPosition());

	shaderADS.setMat4("projection", camera.GetProjection());
	shaderADS.setMat4("view", camera.GetView());
	shaderADS.setMat4("model", transform.GetModel());
}


/*
Sets objectColor, lightColor and lightPos to preset values
Sets all the uniforms for the shader
Sets the values for the fog, which are the minimum and maximum distance
used for the fog intensity calculation and sets the fog's color
*/
void Game::LightingADSFog()
{
	shaderADSFog.setVec3("objectColor", 0.5f, 0.5f, 1.0f);
	shaderADSFog.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shaderADSFog.setVec3("lightPos", 5.0f, 5.0f, 5.0f);
	shaderADSFog.setVec3("viewPos", camera.getCameraPosition());

	shaderADSFog.setMat4("projection", camera.GetProjection());
	shaderADSFog.setMat4("view", camera.GetView());
	shaderADSFog.setMat4("model", transform.GetModel());


	shaderADSFog.setVec3("fogColor", glm::vec3(0.8, 0.8, 0.8));
	shaderADSFog.setFloat("minDist", -5.0f);
	shaderADSFog.setFloat("maxDist", 5.0f);
}

/*
Sets the lightDir uniform to a preset value of 0.5,0.5,0.5
*/
void Game::ToonLighting()
{
	shaderToon.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
}


/*
Sets the uniforms for view and projection matrices
*/
void Game::RimShader()
{
	shaderRim.setMat4("u_vm", camera.GetView());
	shaderRim.setMat4("u_pm", camera.GetProjection());
}

/*
Sets the lightDir uniform to a preset value of 0,5,0.5,0.5
Sets the uniforms for view and projection matrices
*/
void Game::RimToon()
{
	shaderRimToon.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shaderRimToon.setMat4("u_vm", camera.GetView());
	shaderRimToon.setMat4("u_pm", camera.GetProjection());
}

/*
Sets the lightDir uniform to a preset value of 0,5,0.5,0.5
Sets the uniforms for view and projection matrices
Sets the uniform values for the fogColor and the
min and max distance to preset values
*/
void Game::setLighting()
{
	shaderLighting.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));

	shaderLighting.setMat4("u_vm", camera.GetView());
	shaderLighting.setMat4("u_pm", camera.GetProjection());

	shaderLighting.setVec3("fogColor", glm::vec3(0.2, 0.2, 0.2));
	shaderLighting.setFloat("minDist", -5.0f);
	shaderLighting.setFloat("maxDist", 5.0f);
}

void Game::Fog()
{
	shaderFog.setVec3("objectColor", 0.5f, 0.5f, 1.0f);

	shaderFog.setMat4("projection", camera.GetProjection());
	shaderFog.setMat4("view", camera.GetView());
	shaderFog.setMat4("model", transform.GetModel());

	shaderFog.setVec3("fogColor", glm::vec3(0.4, 0.4, 0.4));
	shaderFog.setFloat("minDist", -50.0f);
	shaderFog.setFloat("maxDist", 5.0f);
}

/*
When this method is called, it executes a different shader to the main camera
depending on the value put in upon calling it.
Cleans up Draw method & allows for changing of shader effect through user input
*/
void Game::ShaderEffect(int effectInt)
{
	//Reflection shader
	if (effectInt == 0)
	{
		shaderReflection.BindToGPU();
		Reflection();
		shaderReflection.Update(transform, camera);
	}
	//Blinn-Phong Lighting shader
	else if (effectInt == 1)
	{
		shaderBP.BindToGPU();
		LightingBP();
		shaderBP.Update(transform, camera);
	}
	//ADS Lighting shader
	else if (effectInt == 2)
	{
		shaderADS.BindToGPU();
		LightingADS();
		shaderADS.Update(transform, camera);
	}
	//ADS Lighting with fog shader
	else if (effectInt == 3)
	{
		shaderADSFog.BindToGPU();
		LightingADSFog();
		shaderADSFog.Update(transform, camera);
		shaderADSFog.setFloat("zValue", transform.GetPosition()->z);
	}
	//Toon Lighting shader
	else if (effectInt == 4)
	{
		shaderToon.BindToGPU();
		ToonLighting();
		shaderToon.Update(transform, camera);
	}
	//Rim Shader
	else if (effectInt == 5)
	{
		shaderRim.BindToGPU();
		RimShader();
		shaderRim.Update(transform, camera);
	}
	//Rim & Toon shader
	else if (effectInt == 6)
	{
		shaderRimToon.BindToGPU();
		RimToon();
		shaderRimToon.Update(transform, camera);
	}
	//Toon, Rim & Fog shader
	else if (effectInt == 7)
	{
		shaderLighting.BindToGPU();
		setLighting();
		shaderLighting.Update(transform, camera);
		shaderLighting.setFloat("zValue", transform.GetPosition()->z);
	}
	else if (effectInt == 8)
	{
		shaderFog.BindToGPU();
		Fog();
		shaderFog.Update(transform, camera);
		shaderFog.setFloat("zValue", transform.GetPosition()->z);
	}
}


//Draws the game
void Game::gameDraw()
{
	_gameDisplay.displayClear(0.0f, 0.0f, 0.0f, 1.0f); //sets the background color to black (if nothing is rendered, there will be a black screen)
	texture.Bind(0); //Binds texture to first GPU
	Skybox(); //Executes the skybox method which draws the skybox. Must be drawn first so it's behind all other objects

			  /*
			  Sets the position,rotation and scale of the object to be drawn
			  Sets the shader effect through ShaderEffect method
			  The correct shader is selected through effectInt which can be manipulated through input
			  The mesh is drawn and the sphere used for collision calculation is updated based on the position
			  */
	transform.SetPosition(glm::vec3(0.0, 0.0, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(1.2, 1.2, 1.2));
	ShaderEffect(effectInt);
	mesh1.drawGame();
	mesh1.updateSphere(*transform.GetPosition(), 1.24f);

	/*
	All other meshes are rendered as above but the shader effect is manually selected
	*/
	transform.SetPosition(glm::vec3(-4.0, 2.0, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.2, 0.2, 0.2));
	ShaderEffect(2);
	mesh2.drawGame();
	mesh2.updateSphere(*transform.GetPosition(), 0.22f);


	transform.SetPosition(glm::vec3(4.0, 2.0, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.2, 0.2, 0.2));
	ShaderEffect(0);
	mesh3.drawGame();
	mesh3.updateSphere(*transform.GetPosition(), 0.22f);


	transform.SetPosition(glm::vec3(5.5, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(0);
	mesh4.drawGame();
	mesh4.updateSphere(*transform.GetPosition(), 0.48f);


	transform.SetPosition(glm::vec3(4, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(1);
	mesh5.drawGame();
	mesh5.updateSphere(*transform.GetPosition(), 0.48f);


	transform.SetPosition(glm::vec3(2.5, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(2);
	mesh6.drawGame();
	mesh6.updateSphere(*transform.GetPosition(), 0.48f);


	transform.SetPosition(glm::vec3(1, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(3);
	mesh7.drawGame();
	mesh7.updateSphere(*transform.GetPosition(), 0.48f);


	transform.SetPosition(glm::vec3(-0.5, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(4);
	mesh8.drawGame();
	mesh8.updateSphere(*transform.GetPosition(), 0.48f);


	transform.SetPosition(glm::vec3(-2, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(5);
	mesh9.drawGame();
	mesh9.updateSphere(*transform.GetPosition(), 0.48f);


	transform.SetPosition(glm::vec3(-3.5, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(6);
	mesh10.drawGame();
	mesh10.updateSphere(*transform.GetPosition(), 0.48f);


	transform.SetPosition(glm::vec3(-5, -2.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(7);
	mesh11.drawGame();
	mesh11.updateSphere(*transform.GetPosition(), 0.48f);

	transform.SetPosition(glm::vec3(-0.5, -4, 0.0));
	transform.SetRotation(glm::vec3(0.0, rotation * 0.3, 0.0));
	transform.SetScale(glm::vec3(0.45, 0.45, 0.45));
	ShaderEffect(8);
	mesh12.drawGame();
	mesh12.updateSphere(*transform.GetPosition(), 0.48f);

	rotation = rotation + 0.015f; //rotates the object
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();
	_gameDisplay.swapBuffer();
}