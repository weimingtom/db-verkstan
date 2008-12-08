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
#include "core/operators/transformmodeloperator.hpp"
#include "core/operators/texturemappingoperator.hpp"
#include "core/operators/materialoperator.hpp"
#include "core/operators/modeloperator.hpp"
#include "core/operators/addmodelsoperator.hpp"
#include "core/operators/lightoperator.hpp"
#include "core/operators/cameraoperator.hpp"
#include "core/operators/clonemodeloperator.hpp"
#include "core/operators/timelineoperator.hpp"
#include "core/operators/icosahedronoperator.hpp"
#include "core/operators/subdivideoperator.hpp"
#include "core/operators/relaxoperator.hpp"
#include "core/operators/randomselectionoperator.hpp"
#include "core/operators/extrudeoperator.hpp"
#include "core/operators/rendertotextureoperator.hpp"
#include "core/operators/bluroperator.hpp"
#include "core/operators/cloudsoperator.hpp"
#include "core/operators/glowoperator.hpp"

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
        using ::TransformModelOperator;
        using ::TextureMappingOperator;
        using ::MaterialOperator;
        using ::ModelOperator;
        using ::AddModelsOperator;
        using ::LightOperator;
        using ::CameraOperator;
        using ::CloneModelOperator;
		using ::IcosahedronOperator;
		using ::SubdivideOperator;
		using ::RelaxOperator;
		using ::RandomSelectionOperator;
		using ::ExtrudeOperator;
        using ::TimelineOperator;
        using ::RenderToTextureOperator;
        using ::BlurOperator;
        using ::CloudsOperator;
        using ::GlowOperator;
    }
}
#endif

#ifdef OPERATOR_CATEGORY_DEFINES
ADD_OP_TO_CAT("Clouds",          "Texture");
ADD_OP_TO_CAT("Pixels",          "Texture");
ADD_OP_TO_CAT("Flat",            "Texture");
ADD_OP_TO_CAT("Text",            "Texture");
ADD_OP_TO_CAT("Rectangle",       "Texture");
ADD_OP_TO_CAT("Glow",            "Texture");
ADD_OP_TO_CAT("Rotozoom",        "Texture");
ADD_OP_TO_CAT("Blur",            "Texture");
ADD_OP_TO_CAT("Render To",       "Texture");
ADD_OP_TO_CAT("Torus",           "Mesh");
ADD_OP_TO_CAT("Sphere",          "Mesh");
ADD_OP_TO_CAT("Cylinder",        "Mesh");
ADD_OP_TO_CAT("Box",             "Mesh");
ADD_OP_TO_CAT("Icosahedron",     "Mesh");
ADD_OP_TO_CAT("Texture Mapping", "Mesh");
ADD_OP_TO_CAT("Subdivide",       "Mesh");
ADD_OP_TO_CAT("Relax",	         "Mesh");
ADD_OP_TO_CAT("Random Selection","Mesh");
ADD_OP_TO_CAT("Extrude",		 "Mesh");
ADD_OP_TO_CAT("Model",           "Model");
ADD_OP_TO_CAT("Transform Model", "Model");
ADD_OP_TO_CAT("Light",           "Model");
ADD_OP_TO_CAT("Add Models",      "Model");
ADD_OP_TO_CAT("Material",        "Model");
ADD_OP_TO_CAT("Clone Model",     "Model");
ADD_OP_TO_CAT("Camera",          "Renderer");
ADD_OP_TO_CAT("Timeline",        "Renderer");
ADD_OP_TO_CAT("Transform",       "Renderer");
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
ADD_OPTIONAL_INPUT(Texture);
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

DEF_OP("Icosahedron", IcosahedronOperator, Mesh);
END_OP();

DEF_OP("Subdivide", SubdivideOperator, Mesh);
ADD_BYTE_PROP("Repetitions", 1);
ADD_FLOAT_PROP("Smoothness", 0.5f);
ADD_INPUT(Mesh);
END_OP();

DEF_OP("Relax", RelaxOperator, Mesh);
ADD_FLOAT_PROP("Strength", 0.1f);
ADD_BYTE_PROP("Repetitions", 2);
ADD_INPUT(Mesh);
END_OP();

DEF_OP("Random Selection", RandomSelectionOperator, Mesh);
ADD_BYTE_PROP("Probablility", 128);
ADD_BYTE_PROP("Seed", 1);
ADD_INPUT(Mesh);
END_OP();


DEF_OP("Extrude", ExtrudeOperator, Mesh);
ADD_FLOAT_PROP("Distance", 0.1f);
ADD_INPUT(Mesh);
END_OP();

DEF_OP("Texture Mapping", TextureMappingOperator, Mesh);
ADD_INPUT(Mesh);
END_OP();

DEF_OP("Model", ModelOperator, Model);
ADD_INPUT(Mesh);
END_OP();

DEF_OP("Transform Model", TransformModelOperator, Model);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Model);
END_OP();

DEF_OP("Add Models", AddModelsOperator, Model);
ADD_INFINITE_INPUT(Model);
END_OP();

DEF_OP("Light", LightOperator, Model);
ADD_ENUM_PROP("Type", "Point,Spot,Directional", "Point");
ADD_COLOR_PROP("Diffuse", 255, 255, 0);
ADD_COLOR_PROP("Specular", 255, 255, 255);
ADD_COLOR_PROP("Ambient", 0, 0, 0);
ADD_VECTOR_PROP("Position", 0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Direction", 1.0f, 0.0f, 0.0f);
ADD_FLOAT_PROP("Range", 10.0f);
ADD_FLOAT_PROP("Falloff", 10.0f);
ADD_FLOAT_PROP("Attenuation0", 1.0f);
ADD_FLOAT_PROP("Attenuation1", 1.0f);
ADD_FLOAT_PROP("Attenuation2", 1.0f);
ADD_FLOAT_PROP("Theta", 1.0f);
ADD_FLOAT_PROP("Phi", 1.0f);
END_OP();

DEF_OP("Material", MaterialOperator, Model);
ADD_INPUT(Mesh);
ADD_OPTIONAL_INPUT(Texture);
END_OP();

DEF_OP("Clone Model", CloneModelOperator, Model);
ADD_BYTE_PROP("Clones",      2);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Model);
END_OP();

DEF_OP("Camera", CameraOperator, Renderer);
ADD_FLOAT_PROP("Angle", 45.0f);
ADD_INT_PROP("Aspect width", 1024);
ADD_INT_PROP("Aspect height", 768);
ADD_COLOR_PROP("Clear color", 255, 0, 255);
ADD_VECTOR_PROP("Translation", 0.0f, 0.0f, -5.0f);
ADD_VECTOR_PROP("Look at", 0.0f, 0.0f, 0.0f);
ADD_FLOAT_PROP("Rotation", 0.0f);
ADD_INFINITE_INPUT(Unspecified);
END_OP();

DEF_OP("Transform", TransformModelOperator, Renderer);
ADD_VECTOR_PROP("Scale",     1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotate",    0.0f, 0.0f, 0.0f);
ADD_VECTOR_PROP("Translate", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Scene);
END_OP();

DEF_OP("Timeline", TimelineOperator, Renderer);
ADD_BYTE_PROP("Render", 1);
ADD_FLOAT_PROP("Time offset", 0);
ADD_INFINITE_INPUT(Unspecified);
END_OP();

DEF_OP("Render To", RenderToTextureOperator, Texture);
ADD_INFINITE_INPUT(Unspecified);
END_OP();

DEF_OP("Blur", BlurOperator, Texture);
ADD_ENUM_PROP("Type", "Box,Triangle,Gaussien", "Box");
ADD_ENUM_PROP("Direction", "X,Y,X and Y", "X and Y");
ADD_BYTE_PROP("Width", 1);
ADD_BYTE_PROP("Amplify", 5);
ADD_INPUT(Texture);
END_OP();

DEF_OP("Clouds", CloudsOperator, Texture);
ADD_COLOR_PROP("Color 1", 0, 0, 0);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_BYTE_PROP("Size", 1);
ADD_BYTE_PROP("Seed", 1);
END_OP();

DEF_OP("Glow", GlowOperator, Texture);
ADD_COLOR_PROP("Color", 255, 0, 0);
ADD_BYTE_PROP("Center X", 128);
ADD_BYTE_PROP("Center Y", 128);
ADD_BYTE_PROP("Radius X", 128);
ADD_BYTE_PROP("Radius Y", 128);
ADD_BYTE_PROP("Gamma", 1);
ADD_BYTE_PROP("Alpha", 255);
ADD_OPTIONAL_INPUT(Texture);
END_OP();

#endif
