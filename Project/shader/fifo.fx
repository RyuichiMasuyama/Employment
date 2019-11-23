//--------------------------------------------------------------------------------------
// fifo.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

cbuffer ConstantBufferFifoTimer : register(b7)
{
	float4 FifoTimer;
}

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
	float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
	float alpha;

	alpha = FifoTimer.x - 1.f + texcol.r;

	return float4(0.f, 0.f, 0.f, alpha);
}
