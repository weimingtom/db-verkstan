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
#include "core/operators/transformmeshoperator.hpp"
#include "core/operators/texturemappingoperator.hpp"
#include "core/operators/materialoperator.hpp"

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
        using ::TransformMeshOperator;
        using ::TextureMappingOperator;
        using ::MaterialOperator;
    }
}
#endif

#ifdef OPERATOR_CATEGORY_DEFINES
ADD_OP_TO_CAT("Pixels",          "Texture");
ADD_OP_TO_CAT("Flat",            "Texture");
ADD_OP_TO_CAT("Text",            "Texture");
ADD_OP_TO_CAT("Rectangle",       "Texture");
ADD_OP_TO_CAT("Rotozoom",        "Texture");
ADD_OP_TO_CAT("Torus",           "Mesh");
ADD_OP_TO_CAT("Sphere",          "Mesh");
ADD_OP_TO_CAT("Cylinder",        "Mesh");
ADD_OP_TO_CAT("Box",             "Mesh");
ADD_OP_TO_CAT("Transform",       "Mesh");
ADD_OP_TO_CAT("Texture Mapping", "Mesh");
ADD_OP_TO_CAT("Material",        "Model");
#endif

#ifdef OPERATOR_DEFINES
DEF_OP("Pixels", PixelsOperator, Texture);
ADD_COLOR_PROP("Color 1", 255, 255, 255);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_INT_PROP("Count", 255);
ADD_INT_PROP("Seed",  0);
ADD_OPTIONAL_INPUT(Texture);
END_OP();

DEF_OP("Flat", FlatOperator, Texture);
ADD_COLOR_PROP("Color", 255, 255, 255);
END_OP();

DEF_OP("Text", TextOperator, Texture);
ADD_COLOR_PROP("Color", 255, 255, 255);
ADD_BYTE_PROP("Height", 30);
ADD_BYTE_PROP("X", 10);
ADD_BYTE_PROP("Y", 5);
ADD_STRING_PROP("Font", "");
ADD_TEXT_PROP("Text", "Text!");
ADD_OPTIONAL_INPUT(Texture);
END_OP();

DEF_OP("Rectangle", RectangleOperator, Texture);
ADD_COLOR_PROP("Color", 255, 255, 0);
ADD_BYTE_PROP("X",      10);
ADD_BYTE_PROP("Y",      10);
ADD_BYTE_PROP("Width",  100);
ADD_BYTE_PROP("Height", 100);
ADD_INPUT(Texture);
END_OP();

DEF_OP("Rotozoom", RotozoomOperator, Texture);
ADD_BYTE_PROP("Center X", 128);
ADD_BYTE_PROP("Center Y", 128);
ADD_BYTE_PROP("Rotation", 0);
ADD_FLOAT_PROP("Zoom",    1.0f);
ADD_INPUT(Texture);
END_OP();

DEF_OP("Torus", TorusOperator, Mesh);
ADD_FLOAT_PROP("Inner radius", 0.3f);
ADD_FLOAT_PROP("Outer radius", 0.7f);
ADD_BYTE_PROP("Sides",         5);
ADD_BYTE_PROP("Rings",         10);
END_OP();

DEF_OP("Sphere", SphereOperator, Mesh);
ADD_FLOAT_PROP("Radius", 1.0f);
ADD_BYTE_PROP("Slices",  10);
ADD_BYTE_PROP("Stacks",  10);
END_OP();

DEF_OP("Cylinder", CylinderOperator, Mesh);
ADD_FLOAT_PROP("Radius 1", 1.0f);
ADD_FLOAT_PROP("Radius 2", 1.0f);
ADD_FLOAT_PROP("Length",   5.0f);
ADD_BYTE_PROP("Slices",    10);
ADD_BYTE_PROP("Stacks",    3);
END_OP();

DEF_OP("Box", BoxOperator, Mesh);
ADD_FLOAT_PROP("Width",  1.0f);
ADD_FLOAT_PROP("Height", 1.0f);
ADD_FLOAT_PROP("Depth",  1.0f);
END_OP();

DEF_OP("Transform", TransformMeshOperator, Mesh);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Mesh);
END_OP();

DEF_OP("Texture Mapping", TextureMappingOperator, Mesh);
ADD_INPUT(Mesh);
END_OP();

DEF_OP("Material", MaterialOperator, Model);
ADD_INPUT(Mesh);
ADD_INPUT(Texture);
END_OP();


#endif