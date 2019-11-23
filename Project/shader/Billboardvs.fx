//--------------------------------------------------------------------------------------
// Billboardvs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main(float4 Pos		:	POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	//float4x4 wvMat = mul(World, View);

	output.WPos = mul(Pos, World);
	output.WPos = output.Pos;
	//output.Pos = mul(Pos, CameraInvers);transpose
	float4 newpos = mul(float4(1.f, 0.f, 0.f, 0.f) , View) + Pos;
	output.Pos = mul(newpos, World);
	output.Pos += Pos;
	
	output.Pos = mul(output.Pos, Projection);

	float4 N = Normal;
	N.w = 0.0f;					// 法線はベクトルなのでＷの値を０にする。

	N = mul(N, World);
	N = normalize(N);

	output.Normal = N;

	return output;
}