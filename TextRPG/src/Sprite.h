#pragma once
#include "BasicTypes.h"
#include "vector2.h"

class Sprite
{
public:
    Sprite();
    Sprite(Sprite*);
    ~Sprite(void);

    virtual void Update(long) = 0;
    virtual void Render() = 0;

    void SetPosition(const vector2f& pos) { _pos = pos; }
    vector2f GetPosition() { return _pos; }

    void SetSize(const vector2f& size) { _size = size; }
    vector2f GetSize() { return _size; }

    virtual void MakeAlive() { _isAlive = true; }
    virtual void Kill() { _isAlive = false; }
    virtual bool IsAlive() { return _isAlive; }

    virtual void Move(const vector2f& dir);
protected:
    virtual void Init();

    vector2f _pos;
    vector2f _size;

    bool _isAlive;
};