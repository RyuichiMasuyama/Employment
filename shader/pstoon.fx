//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
    float4 N = input.Normal;
    float4 Pos = input.Pos;

    N.w = 0.f; // 法線はベクトルなのでＷの値を０にする。
    Pos.w = 0.f;

    N = normalize(N); // 法線ベクトル正規化
    
	// 鏡面反射光の計算（ブリンフォン）
    float4 L = way;
    float4 H;
    float4 V = normalize(Position - input.Pos);
    H = normalize(L + V);
    float specL = pow(max(dot(N, H), 0), Material.Specular.w);
    
    if (specL < 0)
        specL = 0;
    if ( 1 < specL)
        specL = 0.99f;

    float4 Col = g_TexHi.Sample(g_SamplerLinear, float2(0.f, specL));

    float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
    texcol.a = 1.f;

    return texcol * Col;
}