#pragma once

class Texture;
class Mesh;
class Renderable;

enum Filters
{
    // Texture filters
    CloudsTextureFilter,
    PixelsTextureFilter,
    BlurTextureFilter,
    TextTextureFilter,
    RectangleTextureFilter,
    CrackleTextureFilter,
    FlatTextureFilter,
    GlowTextureFilter,
    NormalMapTextureFilter,

    // Torus filters
    TorusMeshFilter,
    RandomSelectionMeshFilter,
    MegaExtrudeMeshFilter,
};

class TextureFilters
{
public:
    static Texture* clouds(D3DXCOLOR color1, D3DXCOLOR color2, int scale, int seed);
    static Texture* pixels(Texture* texture, D3DXCOLOR color1, D3DXCOLOR color2, int count, int seed, bool inPlace = false);
    static Texture* blur(Texture* texture, int passes, int width, int amplify = 16, int direction = 3);
    static Texture* text(Texture* texture, D3DXCOLOR color, int height, int x, int y, const char *font, const char *text, bool inPlace = false);
    static Texture* rectangle(Texture* texture, D3DXCOLOR color, int x, int y, int width, int height, bool inPlace = false);
    static Texture* crackle(D3DXCOLOR color1, D3DXCOLOR color2, int count, int randomness, int seed);
    static Texture* flat(D3DXCOLOR color);
    static Texture* glow(Texture* texture, D3DXCOLOR color, int centerX, int centerY, int radiusX, int radiusY, int gamma_, int alpha_, bool inPlace = false);
    static Texture* normalMap(Texture* texture, int amplify, bool inPlace = false);
};

class MeshFilters
{
public:
   static Mesh* torus(float innerRadius, float outerRadius, int sides, int rings, bool inPlace = false);
   static Mesh* randomSelection(Mesh* mesh, int probability, int seed, bool inPlace = false);
   static Mesh* megaExtrude(Mesh* mesh, float distance, int count, D3DXVECTOR3 scaleVector, D3DXVECTOR3 rotationVector);
};

class RenderableFilters
{
public:
};