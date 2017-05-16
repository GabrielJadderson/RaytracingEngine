#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd, int w, int h) : wnd(wnd), gfx(wnd, w, h)
{
	//MessageBox(nullptr, L"Exception caught at main window creation.", L"Unhandled Non-STL Exception", MB_OK);
}


void Game::loopLogic()
{
	UpdateModel();
}

//game logic
void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_ESCAPE)) //exit on escape character
		wnd.Kill();
}

//draw the pixel
void Game::drawPixel(int x, int y, int r, int g, int b)
{
	gfx.PutPixel(x, y, r, g, b);
}

void Game::begin()
{
	gfx.BeginFrame();
}

void Game::end()
{
	gfx.EndFrame();
}


//implement
void Game::screenshot()
{

}