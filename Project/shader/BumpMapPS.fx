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
	float4 L = LightDirection;

	N.w = 0.0f;					// �@���̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B
	L.w = 0.0f;					// ���̕����̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B

	N = normalize(N);			// �@���x�N�g�����K��
	L = normalize(L);			// ���̕����x�N�g�����K��

	float4 texcol2 = g_TexBump.Sample(g_SamplerLinear, input.Tex);

	texcol2 = 2.f * texcol2 - 1.0f;
	texcol2 = normalize( texcol2 );         // �W����

	N = texcol2 * N;
	N = normalize(N);
	
	// �g�U���ˌ��̌v�Z
	float d = max(0.0, dot(L, N));			// �����o�[�g�]����
	float4 diffuse = diffuseMaterial * d;	// �}�e���A���l�Ɗ|���Z

	// ���ʔ��ˌ��̌v�Z�i�u�����t�H���j
	float4 H;
	float4 V = normalize(EyePos - input.WPos);
	H = normalize(L + V);
	//* dot(texcol2 , L)
	float s = max(0, dot(N, H));
	s = pow(s,1);
	float4 specular = s * specularMaterial;

	float4 texcol = g_Tex.Sample(g_SamplerLinear, input.Tex);
	float4 col;
	//col.rgb = specular.rgb + diffuse.rgb * texcol.rgb;

	col =  diffuse  * texcol * + specular;

	col.a = 1.f;


	return col;
}