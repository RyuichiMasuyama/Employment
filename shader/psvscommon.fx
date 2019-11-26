Texture2D g_Tex : register(t0);				// �e�N�X�`��
Texture2D g_TexNormal : register(t1);			// �e�N�X�`��
Texture2D g_TexHi : register(t2);			// �e�N�X�`��
SamplerState g_SamplerLinear : register(s0);	// �T���v���[
SamplerState g_SamplerShadowMap : register(s1);

//--------------------------------------------------------------------------------------
// �R���X�^���g�o�b�t�@
//--------------------------------------------------------------------------------------

struct MaterialStruct
{
    float4 ambient;
    float4 diffuse;
    float4 emissive;
    float4 bump;
    float4 specular;
    float transparency;
    float shininess;
    float reflectivity;
};

cbuffer ConstantBufferWorld : register(b0)
{
	float4x4 World;
}

cbuffer ConstantBufferView : register(b1)
{
    float4x4 View;
}

cbuffer ConstantBufferProjection : register(b2)
{
    float4x4 Projection;
}

// ������ɕύX�\��
//cbuffer ConstantCamera : register(b1)
//{
//      Camera
//}

cbuffer ConstantBufferMaterial : register(b3)
{
	float4	ambientMaterial;
	float4	diffuseMaterial;
	float4	specularMaterial;
}

// ������ɕύX�\��
//cbuffer ConstantBufferMaterial : register(b2)
//{
//    MaterialStruct material;
//}

//cbuffer ConstantBufferLight : register(b4)
//{
//	float4 LightDirection;			// ���̕���
//	float4 EyePos;					// ���_�ʒu
//	float3 LightColor;				// ���C�g�̃J���[
//	float4 LightAttenuate;			// ����
//	float4 LightSpecular;
//	float4 LightDiffuse;
//}

cbuffer ConstantaBufferLightTest : register(b4)
{
    float4 way;
    float4 color;
}

cbuffer ConstantBufferTime : register(b5)
{
	float4 myTime;				// ���Ԏ擾 x ���̂܂�,y =x/2,z =x/4,w =x/8
	float4 myDeltaTime;			// �o�ߎ��Ԏ擾 x ���̂܂�,y =x/2,z =x/4,w =x/8
}

cbuffer ConstantBufferCamera : register(b6)
{
	float3 CameraPos;
	float4x4 CameraInvers;
}

cbuffer PostEffect : register(b7)
{
    float4 Wight1; // �K�E�X�̏d�݌v�Z
    float4 Wight2; // ����
    //float Wight[8];
}

//--------------------------------------------------------------------------------------
// �\���̒�`
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
	float4 Normal : NORMAL;
    float2 Tex : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
	float2 Tex : TEXCOORD;
	float4 WPos : TEXCOORD1;
	float4 Normal : TEXCOORD2;
};


struct VS2D_OUTPUT
{
	float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
    float2 Tex : TEXCOORD;
};

struct VS_GAUSSE_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
    float2 Tex : TEXCOORD;
    float2 Tex0 : TEXCOORD1;
    float2 Tex1 : TEXCOORD2;
    float2 Tex2 : TEXCOORD3;
    float2 Tex3 : TEXCOORD4;
    float2 Tex4 : TEXCOORD5;
    float2 Tex5 : TEXCOORD6;
    float2 Tex6 : TEXCOORD7;
    float2 Tex7 : TEXCOORD8;
};

struct Camera{
    matrix view;
    matrix Projection;
    matrix CameraInvers;
};
