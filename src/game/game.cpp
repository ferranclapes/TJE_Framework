#include "game.h"
#include "framework/utils.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/fbo.h"
#include "graphics/shader.h"
#include "framework/input.h"
#include "framework/entities/entityMesh.h"
#include "game/world.h"


// INCLUDES AFEGITS:
#include "stage.h"

#include <cmath>

//some globals
//Mesh* mesh = NULL;
//Texture* texture = NULL;
//Shader* shader = NULL;
float angle = 0;
float mouse_speed = 20.0f;

//EntityMesh entity;

Game* Game::instance = NULL;


Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;


	// Create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 6.f, 6.f), Vector3(0.f, 0.f, 1.0f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective
    
    camera2D = new Camera();
    camera2D->view_matrix = Matrix44(); // Set View to identity
    camera2D->setOrthographic(0, window_width, 0, window_height, -1, 1 );
    // CREAR CAMERA 2D
    camera2D = new Camera();
    camera2D->view_matrix.setIdentity();
	camera2D->setOrthographic(0, window_width, window_height, 0, -1.f, 1.f);

    
    // STAGES
    intro_stage = new IntroStage();
	select_stage = new SelectStage();
	personalize_stage = new PersonalizeStage();
    commands_stage = new CommandsStage();
    play_stage = new PlayStage();
	lost_stage = new LostStage();
	win_stage = new WinStage();
    end_stage = new EndStage();

	stages.emplace_back(intro_stage);
	stages.emplace_back(select_stage);
	stages.emplace_back(personalize_stage);
    stages.emplace_back(commands_stage);
	stages.emplace_back(play_stage);
	stages.emplace_back(lost_stage);
	stages.emplace_back(win_stage);
	stages.emplace_back(end_stage);
    
  
    GoToStage(INTRO_STAGE);
   
    
	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = false;

	// OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle
	glEnable( GL_DEPTH_TEST ); //check the occlusions using the Z buffer

	
/*
	// Load one texture using the Texture Manager
	texture = Texture::Get("data/textures/texture.tga");

	// Example of loading Mesh from Mesh Manager
    mesh = Mesh::Get("data/meshes/box.ASE");
	*/

	// Example of shader loading using the shaders manager
	//shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	// Hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
    
    //CRIDAR A parseScene
    
}

//what to do when the image has to be draw
void Game::render(void)
{
	// Set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the camera as default
	camera->enable();

	// Set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
   
	//// Create model matrix for cube
	//Matrix44 m;
	//m.rotate(angle*DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));
	/*
	if(shader)
	{
		// Enable shader
		shader->enable();

		// Upload uniforms
		shader->setUniform("u_color", Vector4(1,1,1,1));
		shader->setUniform("u_viewprojection", camera->viewprojection_matrix );
		shader->setUniform("u_texture", texture, 0);
		shader->setUniform("u_model", m);
		shader->setUniform("u_time", time);

		// Do the draw call
		mesh->render( GL_TRIANGLES );

		// Disable shader
		shader->disable();
	}
	*/
	current_stage->render();
	//World::GetInstance()->render(camera);

	// Draw the floor grid
	//drawGrid();


	//Show camera eye position on screen
	/*Camera* cam = camera;
	float x = cam->eye.x;
	float y = cam->eye.y;
	float z = cam->eye.z;
	drawText(50, 50, "X = " + std::to_string(x) + ", Y = " + std::to_string(y) + ", Z = " + std::to_string(z), Vector3(1, 0, 0), 2);*/

	// Render the FPS, Draw Calls, etc
	//drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2); // NUM DALT

	// Swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	float speed = seconds_elapsed * mouse_speed; //the speed is defined by the seconds_elapsed so it goes constant

	// Example
	angle += (float)seconds_elapsed * 10.0f;

	// Mouse input to rotate the cam
	//if (Input::isMousePressed(SDL_BUTTON_LEFT) || mouse_locked) //is left button pressed?
	//{
	//	camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f,-1.0f,0.0f));
	//	camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector( Vector3(-1.0f,0.0f,0.0f)));
	//}

	// Async input to move the camera around
 	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT) ) speed *= 10; //move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP))
	{
		if (camera->eye.z > 2.8) {
			camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) 
	{
		if(camera->eye.z < 13.22){
			camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) 
	{
		if (camera->eye.x > -7.4){
			camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) 
	{
		if (camera->eye.x < 10.9) {
			camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_Z)) 
	{
		if (camera->eye.y > 3.f) {
			camera->zoom(Vector3(0.0f, 0.0f, 1.0f) * speed);
		}
	}
	if (Input::isKeyPressed(SDL_SCANCODE_X)) 
	{
		if(camera->eye.y<6.f){
			camera->zoom(Vector3(0.0f, 0.0f, -1.0f) * speed);
		}
	}

	current_stage->update(seconds_elapsed);
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_F1: Shader::ReloadAll(); break; 
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{

}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	//if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	//{
	//	mouse_locked = !mouse_locked;
	//	SDL_ShowCursor(!mouse_locked);
	//	SDL_SetRelativeMouseMode((SDL_bool)(mouse_locked));
	//}
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{

}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
	mouse_speed *= event.y > 0 ? 1.1f : 0.9f;
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	camera->aspect =  width / (float)height;
	window_width = width;
	window_height = height;
}


void Game::GoToStage(int stage_to_go) {
    
   if(current_stage != nullptr){
        current_stage->onExit(stage_to_go);
    }
    current_stage = stages[stage_to_go];
    current_stage->onEnter();
    
}


Game* Game::GetInstance() {
	return instance;
}


