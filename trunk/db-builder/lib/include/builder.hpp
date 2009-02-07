#pragma once

#include "texture.hpp"
#include "mesh.hpp"
#include "renderable.hpp"

class BuilderLoadCallback
{
public:
    virtual void loading(int numberOfSteps, int currentStep) = 0;
};

class Builder
{
public:
    static LPDIRECT3DDEVICE9 device;
    BuilderLoadCallback* callback;

    void setLoadCallback(BuilderLoadCallback* callback);
    void load(const unsigned char* data);
    Texture* getTexture(unsigned int id);
    Mesh* getMesh(unsigned int id);
    Renderable* getRenderable(unsigned int id);
};