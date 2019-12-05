//--------------------------------------------------------------------------------------
// vs2d.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS2D_OUTPUT main(float4 Pos		:	POSITION,
	float4 Normal : NORMAL,
    float4 Tangent : TANGENT,
    float2 Tex : TEXCOORD)
{
    VS2D_OUTPUT output = (VS2D_OUTPUT) 0;

    output.Pos = mul(Pos, World);
   // output.Pos = Pos;
    output.Pos.w = 1.f;

    output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);

    output.Tex = Tex;
    
    return output;
}