//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
    float4 col = input.Color;
    float4 normal = input.Normal;
    float4 light = way;

    normal = normalize(normal);
    light = normalize(light);

   // col = max(0.0, dot(light, normal));

    col.a = 1.f;

    float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);

    // float outcolor = float4(1.f, 1.f, 1.f, 1.f);
    // return outcolor;
    return texcol * col;
}