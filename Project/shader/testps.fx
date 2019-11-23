//--------------------------------------------------------------------------------------
// testps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
	float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);

	float3 n;
	float3 v;
	float3 l;
	float3 r;
	float d;
	float a;
	float3 iA;
	float3 iD;
	float3 iS;

	n = normalize(input.Normal.xyz);
	v = normalize(CameraPos - input.WPos.xyz);
	l = EyePos.xyz - input.WPos.xyz;
	d= length(l);                                                                                     //光源距離
	l = normalize(l);
	r = 2.f * n * dot(n, l) - l;
	a = saturate(1.f / (LightAttenuate.x + LightAttenuate.y*d + LightAttenuate.z*d*d));

	iA = ambientMaterial.xyz  * LightColor;
	iD = saturate(dot(l, n)) * diffuseMaterial.xyz  * LightDiffuse.xyz  * a* texcol.xyz;
	iS = pow(saturate(dot(r, v)), specularMaterial.w) * specularMaterial.xyz * LightSpecular.xyz * a* texcol.xyz;

	return float4(saturate(iA + iD + iS), 1.f);

}