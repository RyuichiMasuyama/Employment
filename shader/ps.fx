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
    
    // emmisbe
    float4 emi = Material.Emissive;

    // ambient
    float4 amb = Material.Ambient;

    // diffuse
    float4 L = way;
    float difL = max(dot(N, L), 0);
    float4 dif = Material.Diffuse * color * difL;
    
	// 鏡面反射光の計算（ブリンフォン）
    float4 H;
    float4 V = normalize(Position - input.Pos);
    H = normalize(L + V);
    float specL = pow(max(dot(N, H), 0), Material.Specular.w);

    if (specL < 0)
        specL = 0;

    float3 spec = Material.Specular.xyz * color.xyz * specL;

    float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
    float4 col;
    col.rgb = dif.rgb + (spec.rgb * texcol.rgb) + amb.rgb;// + emi.rgb;
    col.a = 1.f;

    return col;
}