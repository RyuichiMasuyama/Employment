//--------------------------------------------------------------------------------------
// testps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
    // これを組み込めばシャドウマップになる
    //float shadowTreshold = 1.f;
    //float shadowBais = 0.01f;
    //float3 shadowColor = float3(0.2f, 0.2f, 0.2f);

    //shadowTreshold = g_shadowMap.SampleCmpLevelZero(g_SamplerShadowMap,, -shadowBais);
    //shadowColor = lerp(shadowColor, float3(1.f, 1.f, 1.f), shadowTreshold);
    //return ;
    return input.Pos.z / input.Pos.w;
}