#include "game_engine.h"

// global
GameEngine *gameEngine;

void main_game_loop()
{
	gameEngine->loop();
}

GameEngine::GameEngine()
{
	timer = new Timer();
}

GameEngine::~GameEngine()
{
	delete(timer);
}

void GameEngine::loop()
{
	timer->tick();
	input();
	update();
	display();
}

void GameEngine::input()
{

}

void GameEngine::update()
{

}

void GameEngine::display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// game-specific stuff goes here

	glutSwapBuffers();
	glutPostRedisplay();
}