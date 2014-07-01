#include <map>
#include <string>
using namespace std;

#include "BasicTypes.h"
#include "ConsoleInput.h"
#include "GraphicDevice.h"
#include "Canvas.h"

#include "ConfigData.h"
#include "ConfigParser.h"

#include "Game.h"
#include "StateMachine.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayingState.h"

#include "Sprite.h"
#include "TextSprite.h"
#include "PlayerController.h"

#include "Map.h"
#include "ViewFrame.h"
#include "MapGenerator.h"
#include "GridBasedMapGenerator.h"

#include "UIManager.h"

#include "TextGame.h"

TextGame::TextGame(void) : Game(), StateMachine()
{
}

TextGame::~TextGame(void)
{
    ConsoleInput::DeleteInstance();
    GraphicDevice::DeleteInstance();
    UIManager::DeleteInstance();

    if (_mapGenerator)
        delete _mapGenerator;
}

void TextGame::Init()
{
    Game::Init();

	// Get the game's data from the config file
    ConfigParser* parser = new ConfigParser();
    ConfigDataSet* data = parser->ParseFile("../Data/Config.ini");
	
	ConfigData* gameData = data->GetSection("Game");
    _device = GraphicDevice::CreateInstance(*gameData);

	// Initialize the map and its view frame
	ConfigData* mapData = data->GetSection("Map");
    int mapWidth = mapData->GetIntValue("Width");
    int mapHeight = mapData->GetIntValue("Height");
    int mapFrameWidth = mapData->GetIntValue("MapFrameWidth");
    int mapFrameHeight = mapData->GetIntValue("MapFrameHeight");
    _map = new Map(Size(mapWidth, mapHeight));
    ViewFrame* viewFrame = _map->GetViewFrame();
    viewFrame->SetSize(vector2f(float(mapFrameWidth), float(mapFrameHeight)));
    viewFrame->SetPosition(vector2f(1, 1));

	ConsoleInput::CreateInstance();

	ConfigData* playerData = data->GetSection("Player");
    _player = new TextSprite();
    _player->SetPosition(vector2f());
	((TextSprite*)_player)->SetAvatar((char)playerData->GetIntValue("PlayerAvatar"));

    _playerController = new PlayerController();
    _playerController->SetPuppet(_player);
	_playerController->SetSpeed(playerData->GetFloatValue("PlayerSpeed"));

    _mapGenerator = new GridBasedMapGenerator();
    _mapGenerator->Generate(_map);

    // Initialize the UI system
    UIManager* uiManager = UIManager::GetInstance();
    uiManager->Import("../Data/UI.xml");

	// Create game states
    AddState(new MenuState());
	AddState(new PlayingState());

	ChangeState("MenuState");
	//ChangeState("PlayingState");

    delete data;
}

void TextGame::Update(long period)
{
    Game::Update(period);

    ConsoleInput* input = ConsoleInput::GetInstance();
    input->Update();

    if (_curState != 0)
    {
        ((GameState*)_curState)->Update(period);
        return;
    }

	if (input->DidVKeyJustGoDown(VK_ESCAPE))
        Exit();
}

void TextGame::Render()
{
    _device->Clear();
    
    if (_curState != 0)
        ((GameState*)_curState)->Render();

    _device->Render();
}

Map* TextGame::GetMap()
{
    return _map;
}

Sprite* TextGame::GetPlayer()
{
    return _player;
}