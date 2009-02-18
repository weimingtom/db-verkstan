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
    RotoZoomTextureFilter,
    MergeTextureFilter,
    InvertTextureFilter,
    DistortionTextureFilter,
    ContrastTextureFilter,
    ColorizeTextureFilter,

    // Mesh filters
    BoxMeshFilter,
    TorusMeshFilter,
    RandomSelectMeshFilter,
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
    static Texture* rotoZoom(Texture* texture, int centerX, int centerY, int rotation, int zoom, bool inPlace = false);
    static Texture* merge(Texture* texture1, Texture* texture2, int mode, bool inPlace = false);
    static Texture* invert(Texture* texture, bool inPlace = false);
    static Texture* distortion(Texture* texture, Texture* map, int mode, int amount_, bool inPlace = false);
    static Texture* contrast(Texture* texture, int amount, bool inPlace = false);
    static Texture* colorize(Texture* texture, int hue_, int saturation_,int light_, bool inPlace = false);
};

class MeshFilters
{
public:
   static Mesh* box(float width, float height, float depth, int xSlices, int ySlices, int zSlices);
   static Mesh* torus(float innerRadius, float outerRadius, int sides, int rings);
   static Mesh* randomSelect(Mesh* mesh, int probability, int seed, bool inPlace = false);
   static Mesh* megaExtrude(Mesh* mesh, float distance, int count, D3DXVECTOR3 scaleVector, D3DXVECTOR3 rotationVector);
};

class RenderableFilters
{
public:
};