//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS2D_OUTPUT input) : SV_Target
{
    //// input.Pos = (input.Pos + 1) / 2;
    //return input.Color;
    return g_Tex.Sample(g_SamplerLinear, input.Tex);
}