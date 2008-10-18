#ifdef OPERATOR_HEADERS
#include "core/operators/flatoperator.hpp"
#include "core/operators/pixelsoperator.hpp"
#include "core/operators/textoperator.hpp"
#include "core/operators/rectangleoperator.hpp"
#include "core/operators/rotozoomoperator.hpp"
#include "core/operators/torusoperator.hpp"
#include "core/operators/sphereoperator.hpp"
#include "core/operators/cylinderoperator.hpp"
#include "core/operators/boxoperator.hpp"

namespace Verkstan
{
    namespace Core
    {
        using ::FlatOperator;
        using ::PixelsOperator;
        using ::TextOperator;
        using ::RectangleOperator;
        using ::RotozoomOperator;
        using ::TorusOperator;
        using ::SphereOperator;
        using ::CylinderOperator;
        using ::BoxOperator;
    }
}
#endif

#ifdef OPERATOR_CATEGORY_DEFINES
ADD_OP_TO_CAT("Pixels",    "Texture");
ADD_OP_TO_CAT("Flat",      "Texture");
ADD_OP_TO_CAT("Text",      "Texture");
ADD_OP_TO_CAT("Rectangle", "Texture");
ADD_OP_TO_CAT("Rotozoom",  "Texture");
ADD_OP_TO_CAT("Torus",     "Mesh");
ADD_OP_TO_CAT("Sphere",    "Mesh");
ADD_OP_TO_CAT("Cylinder",  "Mesh");
ADD_OP_TO_CAT("Box",  "Mesh");
#endif

#ifdef OPERATOR_DEFINES
DEF_OP("Pixels", PixelsOperator, Texture);
ADD_PROP("Color 1", Color, 0xffffffff);
ADD_PROP("Color 2", Color, 0xffffffff);
ADD_PROP("Count", Int,   255);
ADD_PROP("Seed",  Int,   0);
ADD_OPTIONAL_INPUT(Texture);
END_OP();

DEF_OP("Flat", FlatOperator, Texture);
ADD_PROP("Color", Color, 0xffffffff);
END_OP();

DEF_OP("Text", TextOperator, Texture);
ADD_PROP("Color",  Color,  0xffffffff);
ADD_PROP("Height", Byte,   30);
ADD_PROP("X",      Byte,   10);
ADD_PROP("Y",      Byte,   5);
ADD_PROP("Font",   String, "");
ADD_PROP("Text",   Text,   "Text!");
ADD_OPTIONAL_INPUT(Texture);
END_OP();

DEF_OP("Rectangle", RectangleOperator, Texture);
ADD_PROP("Color",  Color,  0xffff00);
ADD_PROP("X",      Byte,  10);
ADD_PROP("Y",      Byte,  10);
ADD_PROP("Width",  Byte,  100);
ADD_PROP("Height", Byte,  100);
ADD_INPUT(Texture);
END_OP();

DEF_OP("Rotozoom", RotozoomOperator, Texture);
ADD_PROP("Center X", Byte,  128);
ADD_PROP("Center Y", Byte,  128);
ADD_PROP("Rotation", Byte,  0);
ADD_PROP("Zoom",     Float, 1.0f);
ADD_INPUT(Texture);
END_OP();

DEF_OP("Torus", TorusOperator, Mesh);
ADD_PROP("Inner radius", Float, 0.3f);
ADD_PROP("Outer radius", Float, 0.7f);
ADD_PROP("Sides",        Byte,  5);
ADD_PROP("Rings",        Byte,  10);
END_OP();

DEF_OP("Sphere", SphereOperator, Mesh);
ADD_PROP("Radius", Float, 1.0f);
ADD_PROP("Slices", Byte,  10);
ADD_PROP("Stacks", Byte,  10);
END_OP();

DEF_OP("Cylinder", CylinderOperator, Mesh);
ADD_PROP("Radius 1", Float, 1.0f);
ADD_PROP("Radius 2", Float, 1.0f);
ADD_PROP("Length", Float, 1.0f);
ADD_PROP("Slices", Byte,  10);
ADD_PROP("Stacks", Byte,  10);
END_OP();

DEF_OP("Box", BoxOperator, Mesh);
ADD_PROP("Width", Float, 1.0f);
ADD_PROP("Height", Float, 1.0f);
ADD_PROP("Depth", Float, 1.0f);
END_OP();

#endif