//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"../psvscommon.fx"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
    float4 N = input.Normal;
    float4 Pos = input.Pos;

    N.w = 0.f; // 法線はベクトルなのでＷの値を０にする。
    Pos.w = 0.f;

    N = normalize(N); // 法線ベクトル正規化
    
    N = (N + 1) / 2;

    return N;
}