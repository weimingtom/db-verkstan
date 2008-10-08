#ifdef OPERATOR_HEADERS
#include "flatoperator.hpp"
#include "pixelsoperator.hpp"
#include "textoperator.hpp"
#include "rotozoomoperator.hpp"
#endif

#ifdef OPERATOR_CATEGORY_DEFINES
ADD_OP_TO_CAT("Pixels", "Texture");
ADD_OP_TO_CAT("Flat", "Texture");
ADD_OP_TO_CAT("Text", "Texture");
ADD_OP_TO_CAT("Rotozoom", "Texture");
#endif

#ifdef OPERATOR_DEFINES
DEF_OP("Pixels", PixelsOperator, Texture);
ADD_PROP("Color", Color, 0xffffffff);
ADD_PROP("Count", Int,   255);
ADD_PROP("Seed",  Int,   0);
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
END_OP();

DEF_OP("Rotozoom", RotozoomOperator, Texture);
ADD_PROP("Center X", Byte,  128);
ADD_PROP("Center Y", Byte,  128);
ADD_PROP("Rotation", Byte,  0);
ADD_PROP("Zoom",     Float, 1.0f);
ADD_INPUT(Texture);
END_OP();

#endif