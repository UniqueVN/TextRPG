#include "BasicTypes.h"
#include "GraphicDevice.h"
#include "Canvas.h"

Canvas::Canvas(void)
{
    _device = GraphicDevice::GetInstance();
}

Canvas::~Canvas(void)
{
}

// Frame, border - drawing functions
void Canvas::DrawRectangle(const Rect& rect, const Color& color, const char tile)
{
    Coordinate pos;
    for (int i = rect.Left; i <= rect.Right; i++)
    {
        pos.X = i;
        for (int j = rect.Top; j <= rect.Bottom; j++)
        {
            pos.Y = j;

            (*_device)[pos].Char.AsciiChar = tile;
            (*_device)[pos].Attributes = color;
        }
    }
}

void Canvas::DrawBorder(const Rect& rect, const Color& color)
{
    Coordinate pos;
    // Draw 4 corner
	_device->SetPixelData(rect.Left, rect.Top, CORNER_TOP_LEFT, color);
	_device->SetPixelData(rect.Right, rect.Top, CORNER_TOP_RIGHT, color);
	_device->SetPixelData(rect.Left, rect.Bottom, CORNER_BOTTOM_LEFT, color);
	_device->SetPixelData(rect.Right, rect.Bottom, CORNER_BOTTOM_RIGHT, color);

    // Draw 2 horizon lines for the top and bottom borders
    for (int x = rect.Left + 1; x <= rect.Right - 1; x++)
    {
		_device->SetPixelData(x, rect.Top, HORIZON_LINE, color);
		_device->SetPixelData(x, rect.Bottom, HORIZON_LINE, color);
    }

    // Draw 2 vertical lines for the left and right borders
    for (int y = rect.Top + 1; y <= rect.Bottom - 1; y++)
    {
		_device->SetPixelData(rect.Left, y, VERTICAL_LINE, color);
		_device->SetPixelData(rect.Right, y, VERTICAL_LINE, color);
    }
}

void Canvas::DrawBorderDouble(const Rect& rect, const Color& color)
{
    Coordinate pos;
    // Draw 4 corner
	_device->SetPixelData(rect.Left, rect.Top, CORNER_TOP_LEFT_DOUBLE, color);
	_device->SetPixelData(rect.Right, rect.Top, CORNER_TOP_RIGHT_DOUBLE, color);
	_device->SetPixelData(rect.Left, rect.Bottom, CORNER_BOTTOM_LEFT_DOUBLE, color);
	_device->SetPixelData(rect.Right, rect.Bottom, CORNER_BOTTOM_RIGHT_DOUBLE, color);

    // Draw 2 horizon lines
    for (int x = rect.Left + 1; x <= rect.Right - 1; x++)
    {
		_device->SetPixelData(x, rect.Top, HORIZON_LINE_DOUBLE, color);
		_device->SetPixelData(x, rect.Bottom, HORIZON_LINE_DOUBLE, color);
    }

    // Draw 2 vertical lines
    for (int y = rect.Top + 1; y <= rect.Bottom - 1; y++)
    {
		_device->SetPixelData(rect.Left, y, VERTICAL_LINE_DOUBLE, color);
		_device->SetPixelData(rect.Right, y, VERTICAL_LINE_DOUBLE, color);
    }
}

void Canvas::DrawBorder(const Rect& rect, int borderWidth, const Color& color, const char tile)
{
	// TODO
}

void Canvas::ShowText(const char* text, const Coordinate& pos, const Color& color)
{
	int l = strlen(text);
	Coordinate coord = pos;
	for (int i = 0; i < l; i++)
	{
		(*_device)[coord].Char.AsciiChar = text[i];
		(*_device)[coord].Attributes = color;
		coord.X++;
	}
}

vector2i Canvas::GetTextSize(const char* text)
{
	return strlen(text);
}
