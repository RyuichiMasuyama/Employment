//--------------------------------------------------------------------------------------
// vs2d.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"
//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS2D_OUTPUT main(float4 Pos		:	POSITION,
	float4 Normal : NORMAL,
    float4 Tangent : TANGENT,
    float2 Tex : TEXCOORD)
{
    VS2D_OUTPUT output = (VS2D_OUTPUT) 0;

    output.Pos = mul(Pos, World);

	//output.Pos = float4(Pos, 1.f);
    output.Pos.w = 1.f;

    output.Color = float4(1.0f, 1.0f, 1.0f, 1.0f);

    output.Tex = Tex;

    //float w, h;
    //w = 800.f;
    //h = 600.f;
        
    //[unroll]
    //for (int i = 0; i < 8; i++)
    //{
    //    output.Tex[i] = Tex + float2(-1.0f / w, 0.0f);
    //}
    //output.Tex0 = Tex + float2(-1.0f / w, -1.0f / h);
    //output.Tex1 = Tex + float2(-3.0f / w, -3.0f / h);
    //output.Tex2 = Tex + float2(-5.0f / w, -5.0f / h);
    //output.Tex3 = Tex + float2(-7.0f / w, -7.0f / h);
    //output.Tex4 = Tex + float2(-9.0f / w, -9.0f / h);
    //output.Tex5 = Tex + float2(-11.0f / w, -11.0f / h);
    //output.Tex6 = Tex + float2(-13.0f / w, -13.0f / h);
    //output.Tex7 = Tex + float2(-15.0f / w, -15.0f / h);

    //output.Tex0 = Tex + float2(0.f, -1.0f / h);
    //output.Tex1 = Tex + float2(0.f, -3.0f / h);
    //output.Tex2 = Tex + float2(0.f, -5.0f / h);
    //output.Tex3 = Tex + float2(0.f, -7.0f / h);
    //output.Tex4 = Tex + float2(0.f , -9.0f / h);
    //output.Tex5 = Tex + float2(0.f, -11.0f / h);
    //output.Tex6 = Tex + float2(0.f, -13.0f / h);
    //output.Tex7 = Tex + float2(0.f, -15.0f / h);
    
    return output;
}