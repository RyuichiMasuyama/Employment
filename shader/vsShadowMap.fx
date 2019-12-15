//--------------------------------------------------------------------------------------
// vs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
// 関数
//--------------------------------------------------------------------------------------
float4 ShadowMadrixChange(float4 pro)
{
    matrix mat = Matrix(
    0.5f, 0.0f, 0.0f, 0.0f,
    0.0f, -0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 1.0f);

    pro = mul(pro, mat);

    return pro;
}
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main(float4 Pos : POSITION,
	float4 Normal : NORMAL,
    float4 Tangent : TANGENT,
    float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, World);
	output.WPos = output.Pos;
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
    
    output.Pos = ShadowMadrixChange(output.Pos);

	return output;
}
