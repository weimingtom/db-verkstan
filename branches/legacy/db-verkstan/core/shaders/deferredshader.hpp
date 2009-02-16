#if 0

//listing of all techniques and passes with embedded asm listings 

technique Deferred
{
    pass P0
    {
        vertexshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.24.950.2656
            //
            // Parameters:
            //
            //   float4x4 matViewProjection;
            //
            //
            // Registers:
            //
            //   Name              Reg   Size
            //   ----------------- ----- ----
            //   matViewProjection c0       4
            //
            
                vs_2_0
                dcl_position v0
                dcl_normal v1
                dcl_texcoord v2
                dp4 oPos.x, v0, c0
                dp4 oPos.y, v0, c1
                dp4 oPos.w, v0, c3
                dp4 r0.x, v0, c2
                mov oPos.z, r0.x
                mov oT3.x, r0.x
                mov oT0.xyz, v0
                mov oT1.xyz, v1
                mov oT2.xy, v2
            
            // approximately 9 instruction slots used
            };

        pixelshader = 
            asm {
            //
            // Generated by Microsoft (R) HLSL Shader Compiler 9.24.950.2656
            //
            // Parameters:
            //
            //   sampler2D diffuseTex;
            //
            //
            // Registers:
            //
            //   Name         Reg   Size
            //   ------------ ----- ----
            //   diffuseTex   s0       1
            //
            
                ps_2_0
                def c0, 0, 0, 0, 1
                dcl t0.xyz
                dcl t1.xyz
                dcl t2.xy
                dcl t3.x
                dcl_2d s0
                texld r0, t2, s0
                mov oC0, c0
                mov r1.xyz, t1
                mov r1.w, t3.x
                mov oC1, r1
                mov oC2, r0
                mov r0.xyz, t0
                mov r0.w, c0.w
                mov oC3, r0
            
            // approximately 9 instruction slots used (1 texture, 8 arithmetic)
            };
    }
}

#endif

const BYTE deferredshader[] =
{
      1,   9, 255, 254,  84,   1, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,  96,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  18,   0,   0,   0, 
    109,  97, 116,  86, 105, 101, 
    119,  80, 114, 111, 106, 101, 
     99, 116, 105, 111, 110,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0, 212,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   4,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0, 109,  97, 116,  87, 
    111, 114, 108, 100,   0,   0, 
      0,   0,  12,   0,   0,   0, 
      4,   0,   0,   0, 252,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  11,   0,   0,   0, 
    100, 105, 102, 102, 117, 115, 
    101,  84, 101, 120,   0,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  15,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  80,  48, 
      0,   0,   9,   0,   0,   0, 
     68, 101, 102, 101, 114, 114, 
    101, 100,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   4,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 120,   0,   0,   0, 
    148,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    228,   0,   0,   0, 248,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  68,   1, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  60,   1, 
      0,   0,   0,   0,   0,   0, 
      2,   0,   0,   0, 146,   0, 
      0,   0,   0,   0,   0,   0, 
     16,   1,   0,   0,  12,   1, 
      0,   0, 147,   0,   0,   0, 
      0,   0,   0,   0,  40,   1, 
      0,   0,  36,   1,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   1,   0,   0,   0, 
      0,   0,   0,   0,  88,   1, 
      0,   0,   0,   2, 255, 255, 
    254, 255,  34,   0,  67,  84, 
     65,  66,  28,   0,   0,   0, 
     83,   0,   0,   0,   0,   2, 
    255, 255,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   0, 
      0,  32,  76,   0,   0,   0, 
     48,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     60,   0,   0,   0,   0,   0, 
      0,   0, 100, 105, 102, 102, 
    117, 115, 101,  84, 101, 120, 
      0, 171,   4,   0,  12,   0, 
      1,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
    112, 115,  95,  50,  95,  48, 
      0,  77, 105,  99, 114, 111, 
    115, 111, 102, 116,  32,  40, 
     82,  41,  32,  72,  76,  83, 
     76,  32,  83, 104,  97, 100, 
    101, 114,  32,  67, 111, 109, 
    112, 105, 108, 101, 114,  32, 
     57,  46,  50,  52,  46,  57, 
     53,  48,  46,  50,  54,  53, 
     54,   0,  81,   0,   0,   5, 
      0,   0,  15, 160,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    128,  63,  31,   0,   0,   2, 
      0,   0,   0, 128,   0,   0, 
      7, 176,  31,   0,   0,   2, 
      0,   0,   0, 128,   1,   0, 
      7, 176,  31,   0,   0,   2, 
      0,   0,   0, 128,   2,   0, 
      3, 176,  31,   0,   0,   2, 
      0,   0,   0, 128,   3,   0, 
      1, 176,  31,   0,   0,   2, 
      0,   0,   0, 144,   0,   8, 
     15, 160,  66,   0,   0,   3, 
      0,   0,  15, 128,   2,   0, 
    228, 176,   0,   8, 228, 160, 
      1,   0,   0,   2,   0,   8, 
     15, 128,   0,   0, 228, 160, 
      1,   0,   0,   2,   1,   0, 
      7, 128,   1,   0, 228, 176, 
      1,   0,   0,   2,   1,   0, 
      8, 128,   3,   0,   0, 176, 
      1,   0,   0,   2,   1,   8, 
     15, 128,   1,   0, 228, 128, 
      1,   0,   0,   2,   2,   8, 
     15, 128,   0,   0, 228, 128, 
      1,   0,   0,   2,   0,   0, 
      7, 128,   0,   0, 228, 176, 
      1,   0,   0,   2,   0,   0, 
      8, 128,   0,   0, 255, 160, 
      1,   0,   0,   2,   3,   8, 
     15, 128,   0,   0, 228, 128, 
    255, 255,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    124,   1,   0,   0,   0,   2, 
    254, 255, 254, 255,  52,   0, 
     67,  84,  65,  66,  28,   0, 
      0,   0, 155,   0,   0,   0, 
      0,   2, 254, 255,   1,   0, 
      0,   0,  28,   0,   0,   0, 
      0,   0,   0,  32, 148,   0, 
      0,   0,  48,   0,   0,   0, 
      2,   0,   0,   0,   4,   0, 
      0,   0,  68,   0,   0,   0, 
     84,   0,   0,   0, 109,  97, 
    116,  86, 105, 101, 119,  80, 
    114, 111, 106, 101,  99, 116, 
    105, 111, 110,   0, 171, 171, 
      3,   0,   3,   0,   4,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 118, 115,  95,  50, 
     95,  48,   0,  77, 105,  99, 
    114, 111, 115, 111, 102, 116, 
     32,  40,  82,  41,  32,  72, 
     76,  83,  76,  32,  83, 104, 
     97, 100, 101, 114,  32,  67, 
    111, 109, 112, 105, 108, 101, 
    114,  32,  57,  46,  50,  52, 
     46,  57,  53,  48,  46,  50, 
     54,  53,  54,   0,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,   3,   0,   0, 128, 
      1,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      2,   0,  15, 144,   9,   0, 
      0,   3,   0,   0,   1, 192, 
      0,   0, 228, 144,   0,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   2, 192,   0,   0, 
    228, 144,   1,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      8, 192,   0,   0, 228, 144, 
      3,   0, 228, 160,   9,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0, 228, 144,   2,   0, 
    228, 160,   1,   0,   0,   2, 
      0,   0,   4, 192,   0,   0, 
      0, 128,   1,   0,   0,   2, 
      3,   0,   1, 224,   0,   0, 
      0, 128,   1,   0,   0,   2, 
      0,   0,   7, 224,   0,   0, 
    228, 144,   1,   0,   0,   2, 
      1,   0,   7, 224,   1,   0, 
    228, 144,   1,   0,   0,   2, 
      2,   0,   3, 224,   2,   0, 
    228, 144, 255, 255,   0,   0
};