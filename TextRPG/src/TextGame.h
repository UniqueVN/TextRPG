#pragma once
#include <map>
#include <string>
using namespace std;

#include "Singleton.h"

#include "GraphicDevice.h"
#include "Game.h"
#include "StateMachine.h"
#include "GameState.h"
#include "WelcomeScreen.h"
#include "PlayingState.h"

#include "Sprite.h"
#include "PlayerController.h"

#include "Map.h"
#include "MapGenerator.h"

class TextGame : public Game, public StateMachine, public Singleton<TextGame>
{
public:
	friend class WelcomeScreen;
	friend class PlayingState;

    Map* GetMap();
    Sprite* GetPlayer();

protected:
    friend class Singleton<TextGame>;

    TextGame(void);
    ~TextGame(void);

    void Init();
    void Update(long);
    void Render();

    GraphicDevice* _device;

    Map* _map;
    MapGenerator* _mapGenerator;
    
    Sprite* _player;
    PlayerController* _playerController;
};
