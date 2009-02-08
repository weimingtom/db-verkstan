#pragma once

class Renderable
{
public:
	virtual ~Renderable() {}
    virtual void render(float time) = 0;
};