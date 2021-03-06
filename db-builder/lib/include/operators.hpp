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
ADD_OP_TO_CAT("Roto Zoom",       "Texture");
ADD_OP_TO_CAT("Merge Textures",  "Texture");
ADD_OP_TO_CAT("Invert Texture",  "Texture");
ADD_OP_TO_CAT("Distort Texture", "Texture");
ADD_OP_TO_CAT("Contrast",        "Texture");
ADD_OP_TO_CAT("Colorize",        "Texture");

ADD_OP_TO_CAT("Box",              "Mesh");
ADD_OP_TO_CAT("Torus",            "Mesh");
ADD_OP_TO_CAT("Cylinder",         "Mesh");
ADD_OP_TO_CAT("Random Select",    "Mesh");
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
DEF_OP_FOR_EDITOR("Pixels", PixelsTextureFilter, Texture, TextureOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Normal Map", NormalMapTextureFilter, Texture, TextureOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Blur", BlurTextureFilter, Texture, TextureOperatorRenderer);
ADD_ENUM_PROP("Type", "Box,Triangle,Gaussien", "Box");
ADD_ENUM_PROP("Direction", "X,Y,X and Y", "X and Y");
ADD_BYTE_PROP("Width", 1);
ADD_BYTE_PROP("Amplify", 16);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_INVERTTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER_WITH_NO_PROPS(InvertTextureFilter, 1);
DEF_OP_FOR_EDITOR("Invert Texture", InvertTextureFilter, Texture, TextureOperatorRenderer);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_DISTORTIONTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(DistortionTextureFilter, 1, 2, 
                  DB_ENUM_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Distort Texture", DistortionTextureFilter, Texture, TextureOperatorRenderer);
ADD_ENUM_PROP("Mode", "Green-Blue,Normal Map", "Green-Blue");
ADD_BYTE_PROP("Amount", 0);
ADD_INPUT(Texture);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CONTRASTTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(ContrastTextureFilter, 1, 1, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Contrast", ContrastTextureFilter, Texture, TextureOperatorRenderer);
ADD_BYTE_PROP("Contrast", 128);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_MERGETEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(MergeTextureFilter, -1, 1, 
                  DB_ENUM_PROP);
DEF_OP_FOR_EDITOR("Merge Textures", MergeTextureFilter, Texture, TextureOperatorRenderer);
ADD_ENUM_PROP("Mode", "Add Clamp,Add Wrap,Sub Clamp,Sub Wrap,Mult,Alpha", "Add Clamp");
ADD_INPUT(Texture);
ADD_INPUT(Texture);
ADD_INFINITE_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_ROTOZOOMTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(RotoZoomTextureFilter, 1, 4, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Roto Zoom", RotoZoomTextureFilter, Texture, TextureOperatorRenderer);
ADD_BYTE_PROP("Center X", 128);
ADD_BYTE_PROP("Center Y", 128);
ADD_BYTE_PROP("Rotation", 0);
ADD_BYTE_PROP("Zoom",    128);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CLOUDSTEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(CloudsTextureFilter, 0, 4, 
                  DB_COLOR_PROP, 
                  DB_COLOR_PROP, 
                  DB_ENUM_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Clouds", CloudsTextureFilter, Texture, TextureOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Text", TextTextureFilter, Texture, TextureOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Rectangle", RectangleTextureFilter, Texture, TextureOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Crackle", CrackleTextureFilter, Texture, TextureOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Glow", GlowTextureFilter, Texture, TextureOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Torus", TorusMeshFilter, Mesh, MeshOperatorRenderer);
ADD_FLOAT_PROP("Inner radius", 0.3f);
ADD_FLOAT_PROP("Outer radius", 0.7f);
ADD_BYTE_PROP("Sides",         5);
ADD_BYTE_PROP("Rings",         10);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_CYLINDMESHFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(CylinderMeshFilter, 0, 7, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP,
                  DB_BYTE_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Cylinder", CylinderMeshFilter, Mesh, MeshOperatorRenderer);
ADD_FLOAT_PROP("Radius 1", 1.0f);
ADD_FLOAT_PROP("Radius 2", 1.0f);
ADD_FLOAT_PROP("Length",   1.0f);
ADD_BYTE_PROP("Slices",    10);
ADD_BYTE_PROP("Stacks",    1);
ADD_BYTE_PROP("Bottom Rings",1);
ADD_BYTE_PROP("Top Rings",1);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_RANDOMSELECTMESHFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(RandomSelectMeshFilter, 1, 2, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Random Select", RandomSelectMeshFilter, Mesh, MeshOperatorRenderer);
ADD_BYTE_PROP("Probablility", 128);
ADD_BYTE_PROP("Seed", 1);
ADD_INPUT(Mesh);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_COLORIZETEXTUREFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(ColorizeTextureFilter, 1, 3, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP, 
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Colorize", ColorizeTextureFilter, Texture, TextureOperatorRenderer);
ADD_BYTE_PROP("Hue", 0);
ADD_BYTE_PROP("Saturation", 255);
ADD_BYTE_PROP("Light", 128);
ADD_INPUT(Texture);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_MEGAEXTRUDEMESHFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(MegaExtrudeMeshFilter, 1, 4, 
                  DB_FLOAT_PROP, 
                  DB_BYTE_PROP, 
                  DB_VECTOR_PROP, 
                  DB_VECTOR_PROP);
DEF_OP_FOR_EDITOR("Mega Extrude", MegaExtrudeMeshFilter, Mesh, MeshOperatorRenderer);
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
DEF_OP_FOR_EDITOR("Flat", FlatTextureFilter, Texture, TextureOperatorRenderer);
ADD_COLOR_PROP("Color", 255, 255, 255);
END_OP_FOR_EDITOR();
#endif

#if defined(DB_BOXMESHFILTER) || defined(DB_EDITOR)
DEF_OP_FOR_LOADER(BoxMeshFilter, 0, 6, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP, 
                  DB_FLOAT_PROP,
                  DB_BYTE_PROP,
                  DB_BYTE_PROP,
                  DB_BYTE_PROP);
DEF_OP_FOR_EDITOR("Box", BoxMeshFilter, Mesh, MeshOperatorRenderer);
ADD_FLOAT_PROP("Width",  1.0f);
ADD_FLOAT_PROP("Height", 1.0f);
ADD_FLOAT_PROP("Depth",  1.0f);
ADD_BYTE_PROP("X Slices", 1);
ADD_BYTE_PROP("Y Slices", 1);
ADD_BYTE_PROP("Z Slices", 1);
END_OP_FOR_EDITOR();
#endif

#endif
