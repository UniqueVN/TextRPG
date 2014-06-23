#pragma once

class Game
{
public:
    virtual void Destroy();     // Destroy all game's components

    int Run();          // Free loop
    int Run(int fps);   // Loop with locked fps

    int GetFPS();

    void TogglePause();
    void Pause();
    void Resume();
    bool IsRunning();
    bool IsGameOver();

    void Exit();

protected:
    Game();
    virtual ~Game(void);

    virtual void Init();        // Initial game's components
	virtual void Update(long);	// Update game contents
	virtual void Render();		// Render game's scene

    void UpdateFPS(long);

    int _fps;
    bool _isRunning;
    bool _isEnd;
};