//--------------------------------------------------------------------------------------
// testvs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT_ANIMETION _input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
    _input.Pos.w = 1.f;
    output.Pos = mul(_input.Pos, World);
	output.WPos = output.Pos;
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

    output.Tex = _input.Tex;

    float4 N = _input.Normal;
	N.w = 0.0f;					// 法線はベクトルなのでＷの値を０にする。

	N = mul(N, World);
	N = normalize(N);

	output.Normal = N;
    output.Color = saturate(dot(N, way));

	return output;
}