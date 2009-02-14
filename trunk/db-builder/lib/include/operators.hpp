#ifdef OPERATOR_CATEGORY_DEFINES
ADD_OP_TO_CAT("Flat",            "Texture");
ADD_OP_TO_CAT("Clouds",          "Texture");
ADD_OP_TO_CAT("Crackle",         "Texture");
ADD_OP_TO_CAT("Pixels",          "Texture");
ADD_OP_TO_CAT("Text",            "Texture");
ADD_OP_TO_CAT("Rectangle",       "Texture");
ADD_OP_TO_CAT("Glow",            "Texture");
ADD_OP_TO_CAT("Blur",            "Texture");
ADD_OP_TO_CAT("Normal Map",      "Texture");

ADD_OP_TO_CAT("Torus",            "Mesh");
ADD_OP_TO_CAT("Random Selection", "Mesh");
ADD_OP_TO_CAT("Mega Extrude",     "Mesh");
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
DEF_OP_FOR_LOADER(PixelsTextureFilter, -1, 4, 
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Pixels", PixelsTextureFilter, Texture);
ADD_COLOR_PROP("Color 1", 255, 255, 255);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_BYTE_PROP("Count", 32);
ADD_BYTE_PROP("Seed",  0);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_NORMALMAPTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(NormalMapTextureFilter, 1, 1, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Normal Map", NormalMapTextureFilter, Texture);
ADD_BYTE_PROP("Amplify", 16);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_BLURTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(BlurTextureFilter, 1, 4, 
                  DB_ENUM_PROP, 
                  DB_ENUM_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Blur", BlurTextureFilter, Texture);
ADD_ENUM_PROP("Type", "Box,Triangle,Gaussien", "Box");
ADD_ENUM_PROP("Direction", "X,Y,X and Y", "X and Y");
ADD_BYTE_PROP("Width", 1);
ADD_BYTE_PROP("Amplify", 16);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CLOUDSTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(CloudsTextureFilter, 0, 4, 
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP, 
                  DB_ENUM_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Clouds", CloudsTextureFilter, Texture);
ADD_COLOR_PROP("Color 1", 0, 0, 0);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_ENUM_PROP("Size", "1,2,4,8,16,32,64,128", "2");
ADD_BYTE_PROP("Seed", 1);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_TEXTTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(TextTextureFilter, -1, 6, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_STRING_PROP, 
                  DB_TEXT_PROP);
DEF_OP_FOR_EDITOR("Text", TextTextureFilter, Texture);
ADD_COLOR_PROP("Color", 255, 255, 255);
ADD_BYTE_PROP("Height", 30);
ADD_BYTE_PROP("X", 10);
ADD_BYTE_PROP("Y", 5);
ADD_STRING_PROP("Font", "");
ADD_TEXT_PROP("Text", "Text!");
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_RECTANGLETEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(RectangleTextureFilter, -1, 5, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP,
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Rectangle", RectangleTextureFilter, Texture);
ADD_COLOR_PROP("Color", 255, 255, 0);
ADD_BYTE_PROP("X",      10);
ADD_BYTE_PROP("Y",      10);
ADD_BYTE_PROP("Width",  100);
ADD_BYTE_PROP("Height", 100);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CRACKLETEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(CrackleTextureFilter, 0, 5,
                  DB_COLOR_PROP,
				  DB_COLOR_PROP,
				  DB_BYTE_PROP,
                  DB_BYTE_PROP,
				  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Crackle", CrackleTextureFilter, Texture);
ADD_COLOR_PROP("Color 1", 0, 0, 0);
ADD_COLOR_PROP("Color 2", 255, 255, 255);
ADD_BYTE_PROP("Count", 8);
ADD_BYTE_PROP("Randomness", 128);
ADD_BYTE_PROP("Seed", 1);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_GLOWTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(GlowTextureFilter, -1, 7, 
                  DB_COLOR_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Glow", GlowTextureFilter, Texture);
ADD_COLOR_PROP("Color", 255, 0, 0);
ADD_BYTE_PROP("Center X", 128);
ADD_BYTE_PROP("Center Y", 128);
ADD_BYTE_PROP("Radius X", 128);
ADD_BYTE_PROP("Radius Y", 128);
ADD_BYTE_PROP("Gamma", 1);
ADD_BYTE_PROP("Alpha", 255);
ADD_OPTIONAL_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_TORUSMESHFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(TorusMeshFilter, 0, 4, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Torus", TorusMeshFilter, Mesh);
ADD_FLOAT_PROP("Inner radius", 0.3f);
ADD_FLOAT_PROP("Outer radius", 0.7f);
ADD_BYTE_PROP("Sides",         5);
ADD_BYTE_PROP("Rings",         10);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_RANDOMSELECTIONMESHFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(RandomSelectionMeshFilter, 1, 2, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Random Selection", RandomSelectionMeshFilter, Mesh);
ADD_BYTE_PROP("Probablility", 128);
ADD_BYTE_PROP("Seed", 1);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_MEGAEXTRUDEMESHFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(MegaExtrudeMeshFilter, 1, 4, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR("Mega Extrude", MegaExtrudeMeshFilter, Mesh);
ADD_FLOAT_PROP("Distance",   0.2f);
ADD_BYTE_PROP("Count", 3);
ADD_VECTOR_PROP("Scale", 1.0f, 1.0f, 1.0f);
ADD_VECTOR_PROP("Rotation", 0.0f, 0.0f, 0.0f);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_FLATTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(FlatTextureFilter, 0, 1, 
                  DB_COLOR_PROP);
DEF_OP_FOR_EDITOR("Flat", FlatTextureFilter, Texture);
ADD_COLOR_PROP("Color", 255, 255, 255);
END_OP_FOR_EDITOR();
#endif

#endif
