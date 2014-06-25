#pragma once
#include "Singleton.h"
#include "BasicTypes.h"
#include "GraphicDevice.h"

class Canvas : public Singleton<Canvas>
{
public:
    // Frame, border - drawing functions
    void DrawRectangle(const Rect& rect, const Color& color, const char tile = ' ');
    void DrawBorder(const Rect& rect, const Color& color);
    void DrawBorderDouble(const Rect& rect, const Color& color);
    void DrawBorder(const Rect& rect, int borderWidth, const Color& color, const char tile = (char)219);

    // Text functions
    void ShowText(const char* text, const Coordinate& pos, const Color& color = 0);
    vector2i GetTextSize(const char* text);

protected:
    friend class Singleton<Canvas>;
    Canvas(void);
    ~Canvas(void);

    GraphicDevice* _device;
};
