#pragma once
#include "BasicTypes.h"
#include "ConfigData.h"

class GraphicDevice
{
public:
    static GraphicDevice* CreateInstance(const Size& resolution = Size(80, 50));
    static GraphicDevice* CreateInstance(const ConfigData& configData);
    static void DeleteInstance();
    static GraphicDevice* GetInstance();

    Size GetResolution();
    int GetWidth();
    int GetHeight();

    void Clear();   // Clear the buffer of GraphicDevice
    void Render();    // Show the whole buffer to the screen

    void DrawRectangle(const Rect& rect, const Color& color, const char tile = ' ');

    void SetPixelData(const int colIndex, const int rowIndex, const char& pixelChar, const Color& color);
	
    void SetCursorPos(const Coordinate& cursorPos);
    void SetCursorVisibility(const bool bVisibility);

    PIXEL& operator [](const Coordinate& pos);

protected:
    void Init();
    void SetupBuffer(HANDLE& bufferHandle);

    static GraphicDevice* _instance;

    Size _res;			// Resolution
    Size _fontSize;
    PIXEL *_pixels;		// Array of pixels data
    HANDLE _hBackBuffer, _hActiveBuffer;

    PIXEL _errPixel;

private:
    GraphicDevice(const Size& resolution);
    GraphicDevice(const ConfigData& configData);
    ~GraphicDevice(void);
};