//--------------------------------------------------------------------------------------
// ps2dBlockout.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS2D_OUTPUT input) : SV_Target
{
	float4 tex;

	tex = g_Tex.Sample(g_SamplerLinear, input.Tex);
	
	if(tex.r < 0.1f){
		if(tex.g < 0.1f){
			if(tex.b < 0.1f){
				tex.a=0.f;
			}
		}
	}	

	return tex;
}