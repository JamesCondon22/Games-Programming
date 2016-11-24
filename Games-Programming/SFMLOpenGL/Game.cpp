#include "Game.h"

Game::Game() : window(VideoMode(800, 600), "OpenGL")
{
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Draw up" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glBegin(GL_TRIANGLE_STRIP); {
		glVertex3f(0.0, 2.0, -5.0); 
		glVertex3f(-2.0, -2.0, -5.0); 
		glVertex3f(2.0, -2.0, -5.0); 
	} 
	glEnd();

	window.display();
}
/// <summary>
/// GL_POINTS;GL_LINES;GL_LINE_STRIP;GL_LINE_LOOP;GL_TRIANGLES;GL_TRIANGLE_STRIP;GL_TRIANGLE_FAN;GL_QUADS;GL_QUAD_STRIP;GL_POLYGON;

/// </summary>
void Game::unload()
{
	cout << "Cleaning up" << endl;
}

