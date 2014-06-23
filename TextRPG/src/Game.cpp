#include "BasicTypes.h"
#include "Game.h"

Game::Game() : _isEnd(false)
{
}

Game::~Game(void)
{
    Destroy();
}

int Game::Run()
{
	static long lastTime = GetTickCount();
	static long period;

    // Initial game's components
    Init();
    
    _isRunning = true;

	while (!IsGameOver())
	{					
        // Count the time period between last update and current update
	    period = GetTickCount() - lastTime;
	    lastTime = GetTickCount();

        UpdateFPS(period);

        // Update game's logic
        Update(period);
        // Render game scene
        Render();
	}

    return 0;
}

// Loop with locked fps
int Game::Run(int fps)
{
    // TODO
    return 0;
}

int Game::GetFPS()
{
    return _fps;
}

void Game::UpdateFPS(long period)
{
    static long frame = 0;
    static long second = 1;

    // Count frame per second
    frame++;
    second += period;
    _fps = (frame * 1000) / second;

    if (second >= 1000)
    {
        second = 1;
        frame = 0;
    }
}

// Destroy all game's components
void Game::Destroy()
{
}

// Initial game's components
void Game::Init()
{
    // Create render device
    // Load game's contents

    // Create input handler
    //_input = Input::GetInstance();
}

// Update game contents
void Game::Update(long period)
{
    if (!_isRunning)
        return;
    // TODO
}

// Render game's scene
void Game::Render()
{
    // TODO
}

void Game::TogglePause()
{
    _isRunning = !_isRunning;
}

void Game::Pause()
{
    _isRunning = false;
}

void Game::Resume()
{
    _isRunning = true;
}

bool Game::IsRunning()
{
    return _isRunning;
}

bool Game::IsGameOver()
{
    return _isEnd;
}

void Game::Exit()
{
    _isEnd = true;
}