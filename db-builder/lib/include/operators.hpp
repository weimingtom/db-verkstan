#ifdef OPERATOR_CATEGORY_DEFINES
ADD_OP_TO_CAT("Pixels",          "Texture");
ADD_OP_TO_CAT("Blur",            "Texture");
#endif

#define DB_BYTE_PROP 0x00
#define DB_ENUM_PROP 0x00
#define DB_INT_PROP  0x01
#define DB_FLOAT_PROP 0x02
#define DB_COLOR_PROP 0x03
#define DB_VECTOR_PROP 0x04
#define DB_STRING_PROP 0x05
#define DB_TEXT_PROP 0x05

//DEF_OP_FOR_LOADER params
// Id, e.i 0
// Class, e.i TimelineOperator
// Number of constant inputs, e.i -1 for no constant inputs or 2 for two constant inputs
// Number of properties, e.i 2
// Property types, e.i DB_BYTE_PROP, DB_FLOAT_PROP for a byte property and a float property. 


//DEF_OP_FOR_LOADER_WITH_NO_PROPS params
// Id, e.i 0
// Class, e.i TimelineOperator
// Number of constant inputs, e.i -1 for no constant inputs or 2 for two constant inputs

#ifdef OPERATOR_DEFINES

#if defined(DB_PIXELSTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(1, PixelsTextureFilter, -1, 4, 
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(1, "Pixels", PixelsTextureFilter, Texture);
ADD_COLOR_PROP("Color 1", 255, 255, 255);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_BYTE_PROP("Count", 1);
ADD_BYTE_PROP("Seed",  0);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_BLURTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(23, BlurTextureFilter, 1, 4, 
                  DB_ENUM_PROP, 
                  DB_ENUM_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR(23, "Blur", BlurTextureFilter, Texture);
ADD_ENUM_PROP("Type", "Box,Triangle,Gaussien", "Box");
ADD_ENUM_PROP("Direction", "X,Y,X and Y", "X and Y");
ADD_BYTE_PROP("Width", 1);
ADD_BYTE_PROP("Amplify", 16);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#endif
