//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"../psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ジオメトリシェーダー
//--------------------------------------------------------------------------------------

float4x4 Size(float _size)
{
    float4x4 resize;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resize[i][j] = 0.f;
        }
    }

    resize._11_22_33 = float3(_size, _size, _size);

    return resize;
}

[maxvertexcount(6)]
void main(triangle VS_OUTPUT input[3], inout TriangleStream<VS_OUTPUT> TriStr)
{
    for (int i = 0; i < 3; i++)
    {
		//同じデータを挿入
        VS_OUTPUT out_vertex = input[i];
		
        TriStr.Append(out_vertex);

        //out_vertex.Pos.x += 5.f;

       // TriStr.Append(out_vertex);
    }
    TriStr.RestartStrip();

    for (int i = 2; i >= 0; i--)
    {
		//同じデータを挿入
        VS_OUTPUT out_vertex = input[i];

        //out_vertex.Pos.xy *= 1.2f;
        float4 normal = out_vertex.Normal;
        out_vertex.Pos += out_vertex.Normal * 0.03f;
        out_vertex.Color = float4(0.f, 0.f, 0.f, 1.f);
        out_vertex.Normal = float4(0.f, 0.f, 0.f, 0.f);

        TriStr.Append(out_vertex);
    }
    
    //VS_OUTPUT out_put = (VS_OUTPUT) 0;

    //out_put.Pos.x = -0.25f;
    //out_put.Pos.y = 0.25f;
    //out_put.Pos.z = 0.5f;
    //out_put.Pos.w = 1.f;

    //// out_put.Color.a = 1.f;

    //TriStr.Append(out_put);
    
    //out_put.Pos.x = 0.25f;
    //out_put.Pos.y = 0.25f;
    //out_put.Pos.z = 0.5f;
    //out_put.Pos.w = 1.f;
    
    ////out_put.Color.a = 1.f;

    //TriStr.Append(out_put);
    
    //out_put.Pos.x = -0.25f;
    //out_put.Pos.y = -0.25f;
    //out_put.Pos.z = 0.5f;
    //out_put.Pos.w = 1.f;

    //// out_put.Color.a = 1.f;

    //TriStr.Append(out_put);
    
    //out_put.Pos.x = 0.25f;
    //out_put.Pos.y = -0.25f;
    //out_put.Pos.z = 0.5f;
    //out_put.Pos.w = 1.f;

    //// out_put.Color.a = 1.f;

    //// TriStr.Append(out_put);

    TriStr.RestartStrip();

}

//頂点生成
//TriStr.Append(out_vertex);

//ポリゴンのつながりを切る
//TriStr.RestartStrip();