/*!
 * @brief	シンプルシェーダー。
 */

//定数バッファ。
cbuffer c0 : register(b0){
	float4	color;		//カラー。
} ;
/*!
 * @brief	頂点シェーダーの出力。
 */
struct SOutputVS{
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
//--------------------------------------------------------------------------------------
// 頂点シェーダーのエントリー関数。
//--------------------------------------------------------------------------------------
float4 VS( float4 Pos : POSITION ) : SV_POSITION
{
    return Pos;
}


//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PS( SOutputVS In ) : SV_Target
{
    return color; 
}
