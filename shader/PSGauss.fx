//--------------------------------------------------------------------------------------
// VSGauss.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//  2Dシェーダー(ガウステスト)
//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_GAUSSE_OUTPUT input) : SV_Target
{
    
    float4 output = (float4) 0;
    float2 OffSet = float2(16.f / 800.0f, 16.f / 600.f);
    
    // X軸
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex0.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex7.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss1.x;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex1.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex6.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss1.y;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex2.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex5.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss1.z;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex3.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex4.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss1.w;
                                                                                                                                                      
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex4.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex3.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss2.x;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex5.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex2.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss2.y;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex6.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex1.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss2.z;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex7.x, input.Tex.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex0.x + OffSet.x, input.Tex.y))) * PostEffect.Gauss2.w;

    // Y軸
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex0.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex7.y + OffSet.y))) * PostEffect.Gauss1.x;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex1.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex6.y + OffSet.y))) * PostEffect.Gauss1.y;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex2.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex5.y + OffSet.y))) * PostEffect.Gauss1.z;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex3.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex4.y + OffSet.y))) * PostEffect.Gauss1.w;
                                                                                                                                 
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex4.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex3.y + OffSet.y))) * PostEffect.Gauss2.x;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex5.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex2.y + OffSet.y))) * PostEffect.Gauss2.y;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex6.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex1.y + OffSet.y))) * PostEffect.Gauss2.z;
    output += (g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex7.y)) + g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex0.y + OffSet.y))) * PostEffect.Gauss2.w;
    // return g_Tex.Sample(g_SamplerLinear, float2(input.Tex.x, input.Tex.y));
    return output / 2.0f;
}