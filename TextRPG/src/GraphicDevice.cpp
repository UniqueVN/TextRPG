#ifndef GRAPHIC_DEVICE_CPP
#define GRAPHIC_DEVICE_CPP

#include <windows.h>
#include "BasicTypes.h"
#include "ConfigData.h"

#include "GraphicDevice.h"

GraphicDevice* GraphicDevice::_instance = nullptr;

GraphicDevice* GraphicDevice::CreateInstance(const Size& resolution)
{
    if (!_instance)
        _instance = new GraphicDevice(resolution);

    return _instance;
}

GraphicDevice* GraphicDevice::CreateInstance(const ConfigData& configData)
{
    if (!_instance)
        _instance = new GraphicDevice(configData);

    return _instance;
}

void GraphicDevice::DeleteInstance()
{
	if (_instance)
	{
		delete _instance;
		_instance = nullptr;
	}
}

GraphicDevice* GraphicDevice::GetInstance()
{
    if (!_instance )
        CreateInstance();

    return _instance;
}

GraphicDevice::GraphicDevice(const Size& resolution) : _res(resolution)
{
    Init();
}

GraphicDevice::GraphicDevice(const ConfigData& configData)
{
	_res.X = configData.GetIntValue("Width");
	_res.Y = configData.GetIntValue("Height");
	_fontSize.X = configData.GetIntValue("FontWidth");
	_fontSize.Y = configData.GetIntValue("FontHeight");

    Init();
}

GraphicDevice::~GraphicDevice(void)
{
    delete _pixels;
}

Size GraphicDevice::GetResolution()
{
    return _res;
}

int GraphicDevice::GetWidth()
{
    return _res.X;
}

int GraphicDevice::GetHeight()
{
    return _res.Y;
}

void GraphicDevice::Init()
{
    _pixels = new PIXEL[_res.X * _res.Y];

	//_hActiveBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	_hActiveBuffer = CreateConsoleScreenBuffer( 
		   GENERIC_READ | GENERIC_WRITE, 
		   FILE_SHARE_READ | FILE_SHARE_WRITE,
		   NULL,
		   CONSOLE_TEXTMODE_BUFFER,
		   NULL);

	_hBackBuffer = CreateConsoleScreenBuffer( 
		   GENERIC_READ | GENERIC_WRITE, 
		   FILE_SHARE_READ | FILE_SHARE_WRITE,
		   NULL,
		   CONSOLE_TEXTMODE_BUFFER,
		   NULL);

    SetupBuffer(_hActiveBuffer);
    SetupBuffer(_hBackBuffer);
}

void GraphicDevice::SetupBuffer(HANDLE& bufferHandle)
{
	//CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	//GetConsoleScreenBufferInfo(bufferHandle, &bufferInfo);
	//COORD maxSize = GetLargestConsoleWindowSize(bufferHandle);

	COORD scrSize = { _res.X, _res.Y };
    SetConsoleScreenBufferSize(bufferHandle, scrSize);
	
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = true;
	//cursorInfo.dwSize = 100;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(bufferHandle, &cursorInfo);

	SMALL_RECT rect;
	rect.Top = rect.Left = 0;
	rect.Right = _res.X - 1;
	rect.Bottom = _res.Y - 1;
	SetConsoleWindowInfo(bufferHandle, true, &rect);

	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(bufferHandle, false, &fontInfo);
	fontInfo.dwFontSize.X = _fontSize.X;
	fontInfo.dwFontSize.Y = _fontSize.Y;
	SetCurrentConsoleFontEx(bufferHandle, false, &fontInfo);
}

// Clear the buffer of GraphicDevice
void GraphicDevice::Clear()
{
    int t = 0;
    for (int i = 0; i < _res.X; i++)
	{
        for (int j = 0; j < _res.Y; j++)
        {
            _pixels[t].Char.AsciiChar = ' ';
            _pixels[t].Attributes = FOREGROUND_WHITE;
            t++;
        }
	}
}

// Show the buffer to screen
void GraphicDevice::Render()
{
    static COORD bufferSize = { _res.X, _res.Y };
    static COORD bufferCoord = { 0, 0 };
    static SMALL_RECT rect;
    rect.Top = rect.Left = 0;
    rect.Bottom = _res.Y - 1;
    rect.Right = _res.X - 1;

	// Render to the back buffer
    //WriteConsoleOutput(_hActiveBuffer, _pixels, bufferSize, bufferCoord, &rect);
    WriteConsoleOutput(_hBackBuffer, _pixels, bufferSize, bufferCoord, &rect);

	// Swap the current active buffer and the back buffer
	HANDLE tempBuffer  = _hActiveBuffer;
	_hActiveBuffer = _hBackBuffer;
	_hBackBuffer = tempBuffer;
		
	SetConsoleActiveScreenBuffer(_hActiveBuffer);
}

void GraphicDevice::DrawRectangle(const Rect& rect, const Color& color, const char tile)
{
    int t = 0;
    for (int i = rect.Top; i <= rect.Bottom; i++)
    {
        t = i * _res.X + rect.Left;
        for (int j = rect.Left; j <= rect.Right; j++)
        {
            _pixels[t].Char.AsciiChar = tile;
            _pixels[t].Attributes = color;
            t++;
        }
    }
}

void GraphicDevice::SetPixelData(const int colIndex, const int rowIndex, const char& pixelChar, const Color& color)
{
	if (colIndex < 0 || colIndex > _res.X || rowIndex < 0 || rowIndex > _res.Y)
		return;

	PIXEL& currentPixel = _pixels[rowIndex * _res.X + colIndex];
	currentPixel.Char.AsciiChar = pixelChar;
	currentPixel.Attributes = color;
}

void GraphicDevice::SetCursorPos(const Coordinate& cursorPos)
{
	COORD newPos;
	newPos.X = cursorPos.X;
	newPos.Y = cursorPos.Y;
	SetConsoleCursorPosition(_hBackBuffer, newPos);
}

void GraphicDevice::SetCursorVisibility(const bool bVisibility)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(_hBackBuffer, &cursorInfo);

	cursorInfo.bVisible = bVisibility;
	SetConsoleCursorInfo(_hBackBuffer, &cursorInfo);
	SetConsoleCursorInfo(_hActiveBuffer, &cursorInfo);
}

PIXEL& GraphicDevice::operator [](const Coordinate& pos)
{
    if (pos.X < 0 || pos.X > _res.X || pos.Y < 0 || pos.Y > _res.Y)
        return _errPixel;

    return _pixels[pos.Y * _res.X + pos.X];
}

#endif