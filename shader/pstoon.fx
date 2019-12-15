//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
//  �s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
    float4 N = input.Normal;
    float4 Pos = input.Pos;

    N.w = 0.f; // �@���̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B
    Pos.w = 0.f;

    N = normalize(N); // �@���x�N�g�����K��
    
	// ���ʔ��ˌ��̌v�Z�i�u�����t�H���j
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