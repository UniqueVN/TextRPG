#pragma once
#include <windows.h>
#include "Vector2.h"

typedef unsigned int uint;
typedef vector2i Size;
typedef vector2i Coordinate;
typedef vector2f Position;
typedef char TileID;

template <typename T = int>
struct TRect
{
    T Left, Top, Right, Bottom;
    
    TRect(T left = 0, T top = 0, T right = 0, T bottom = 0) 
        : Left(left), Top(top), Right(right), Bottom(bottom) {}

    Vector2<T> GetPosition() { return Vector2<T>(Left, Top); }
    Vector2<T> GetSize() { return Vector2<T>(Right - Left, Bottom - Top); }
};
typedef TRect<int> Rect;

typedef CHAR_INFO PIXEL;
typedef char Color;

// Color
#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
#define BACKGROUND_WHITE BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED

// Special ASCII symbol
#define VERTICAL_LINE (char)179 // │
#define HORIZON_LINE (char)196  // -
#define CORNER_TOP_LEFT (char)218   // ┌
#define CORNER_TOP_RIGHT (char)191  // ┐
#define CORNER_BOTTOM_LEFT (char)192    // └
#define CORNER_BOTTOM_RIGHT (char)217   // ┘

#define VERTICAL_LINE_DOUBLE (char)186 // ¦
#define HORIZON_LINE_DOUBLE (char)205  // ═
#define CORNER_TOP_LEFT_DOUBLE (char)201    // ╔
#define CORNER_TOP_RIGHT_DOUBLE (char)187       // ╗
#define CORNER_BOTTOM_LEFT_DOUBLE (char)200     // ╚
#define CORNER_BOTTOM_RIGHT_DOUBLE (char)188    // ╝

#define HALLWAY_TILE (char)176
#define ROOM_TILE '.'