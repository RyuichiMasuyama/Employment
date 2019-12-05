Texture2D g_Tex : register(t0);				// テクスチャ
Texture2D g_TexNormal : register(t1);			// テクスチャ
Texture2D g_TexHi : register(t2);			// テクスチャ
Texture2D g_shadowMap : register(t3);       // シャドウマップテクスチャ
SamplerState g_SamplerLinear : register(s0);	// サンプラー
SamplerState g_SamplerShadowMap : register(s1);

//--------------------------------------------------------------------------------------
// コンスタントバッファ
//--------------------------------------------------------------------------------------

struct MaterialStruct
{
    float4 Ambient;
    float4 Diffuse;
    float4 Emissive;
    float4 Bump;
    float4 Specular;
    float Transparency;
    float Shininess;
    float Reflectivity;
};

struct CameraStruct
{
    float4x4 View;
    float4x4 Projection;
    float4x4 CameraInvers;
    float4 Position;
};

struct PostEffectStruct
{
    float4 Gauss1;
    float4 Gauss2;
    float Bloom;
};

cbuffer ConstantBufferWorld : register(b0)
{
    float4x4 World;
}

// こちらに変更予定
cbuffer ConstantCamera : register(b1)
{
    float4x4 View;
    float4x4 Projection;
    float4x4 CameraInvers;
    float4 Position;
}

cbuffer ConstantBufferMaterial : register(b2)
{
    MaterialStruct Material : packoffset(c0);
}

cbuffer ConstantaBufferLightTest : register(b3)
{
    float4 way;
    float4 color;
}

cbuffer ConstantBufferTime : register(b4)
{
	float4 myTime;				// 時間取得 x そのまま,y =x/2,z =x/4,w =x/8
	float4 myDeltaTime;			// 経過時間取得 x そのまま,y =x/2,z =x/4,w =x/8
}

cbuffer ConstantBufferPostEffect : register(b5)
{
    PostEffectStruct PostEffect: packoffset(c0);
}

//--------------------------------------------------------------------------------------
// 構造体定義
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
