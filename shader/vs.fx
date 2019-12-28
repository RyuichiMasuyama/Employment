//--------------------------------------------------------------------------------------
// vs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"
//--------------------------------------------------------------------------------------
// ���_�V�F�[�_�[
//--------------------------------------------------------------------------------------
VS_OUTPUT main(VS_INPUT_ANIMETION _ver)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

    output.Pos = mul(_ver.Pos, World);
	output.WPos = output.Pos;
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	//output.Tex = Tex;

    float4 N = _ver.Normal;
	N.w = 0.0f;					// �@���̓x�N�g���Ȃ̂łv�̒l���O�ɂ���B

	N = mul(N, World);
	N = normalize(N);

	output.Normal = N;

	return output;
}