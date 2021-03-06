#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Game
{
public:
	Game(class MainWindow& wnd, int w, int h);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Game::drawPixel(int x, int y, int r, int g, int b);
	void Game::begin();
	void Game::end();
	void Game::screenshot();
	void Game::loopLogic();
private:
	void ComposeFrame();
	void UpdateModel();
private:
	MainWindow& wnd;
	Graphics gfx;
};