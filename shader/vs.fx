//--------------------------------------------------------------------------------------
// vs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT_ANIMETION _ver)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

    output.Pos = mul(_ver.Pos, World);
	output.WPos = output.Pos;
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	//output.Tex = Tex;

    float4 N = _ver.Normal;
	N.w = 0.0f;					// 法線はベクトルなのでＷの値を０にする。

	N = mul(N, World);
	N = normalize(N);

	output.Normal = N;

	return output;
}