#pragma once
#include "Vector2.h"
#include "Sprite.h"

class TextSprite : public Sprite
{
public:
    TextSprite(void);
    TextSprite(TextSprite*);
    ~TextSprite(void);

    void Update(long);
    void Render();

    void Move(const vector2f& dir);

    char GetAvatar() { return _avatar; }
    void SetAvatar(const char& newAvatar) { _avatar = newAvatar; }

protected:
    void Init();

    char _avatar;
};
