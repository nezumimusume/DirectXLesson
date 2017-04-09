/*!
 *@brief	DirectX11チュートリアル01
 */
#include "stdafx.h"
#include "tkEngine2/tkEnginePreCompile.h"
#include "tkEngine2/tkEngine.h"

using namespace tkEngine2;

class CComputeTest : public IGameObject {
	struct BufType
	{
		int i;
		float f;
	};
	CShader m_csShader;
	CStructuredBuffer m_inputBuffer_0;	//!<入力用GPUバッファ0。
	CStructuredBuffer m_inputBuffer_1;	//!<入力用GPUバッファ1。
	CStructuredBuffer m_outputBuffer;	//!<出力用GPUバッファ。
	static const UINT NUM_ELEMENTS = 1024;
	BufType g_vBuf0[NUM_ELEMENTS];		//!<入力データ0。
	BufType g_vBuf1[NUM_ELEMENTS];		//!<入力データ1。
	CShaderResourceView m_inputSRV_0;	//!<入力SRV0。
	CShaderResourceView m_inputSRV_1;	//!<入力SRV1。
	CUnorderedAccessView m_outputUAV;	//!<出力UAV。
public:
	CComputeTest()
	{

	}
	~CComputeTest()
	{

	}
	bool Start() override
	{
		//コンピュートシェーダーをロード。
		TK_ASSERT(m_csShader.Load("Assets/shader/BasicCompute11.fx", "CSMain", CShader::EnType::CS), "Failed");
		//入力用のStructuredBufferを作成。
		TK_ASSERT(m_inputBuffer_0.Create(NUM_ELEMENTS, sizeof(BufType), g_vBuf0), "Failed");
		TK_ASSERT(m_inputBuffer_1.Create(NUM_ELEMENTS, sizeof(BufType), g_vBuf1), "Failed");
		//出力用のStructuredBufferを作成。
		TK_ASSERT(m_outputBuffer.Create(NUM_ELEMENTS, sizeof(BufType), NULL), "Failed");

		//SRVを作成。
		TK_ASSERT(m_inputSRV_0.Create(m_inputBuffer_0), "Failed");
		TK_ASSERT(m_inputSRV_1.Create(m_inputBuffer_1), "Failed");
		//UAVを作成。
		TK_ASSERT(m_outputUAV.Create(m_outputBuffer), "Failed");
		return true;
	}
	void Update() override
	{

	}
	void Render(CRenderContext& renderContext)
	{
		//コンピュートシェーダーを設定。
		renderContext.CSSetShader(m_csShader);
		//SRVを設定。
		renderContext.CSSetShaderResource(0, m_inputSRV_0);
		renderContext.CSSetShaderResource(1, m_inputSRV_1);
		//UAVを設定。
		renderContext.CSSetUnorderedAccessView(0, m_outputUAV);

	}
};

class CTriangleDraw : public IGameObject {
	
	CShader m_vsShader;
	CShader m_psShader;
	
	
	CVertexBuffer m_vertexBuffer;
	struct SSimpleVertex {
		CVector3 pos;
	};
public:
	bool Start() override
	{
		m_vsShader.Load("Assets/shader/Tutorial02.fx", "VS", CShader::EnType::VS);
		m_psShader.Load("Assets/shader/Tutorial02.fx", "PS", CShader::EnType::PS);
		
		SSimpleVertex vertices[] =
		{
			CVector3(0.0f, 0.5f, 0.5f),
			CVector3(0.5f, -0.5f, 0.5f),
			CVector3(-0.5f, -0.5f, 0.5f),
		};
		m_vertexBuffer.Create(3, sizeof(SSimpleVertex), vertices);
		return true;
	}
	void Update() override
	{

	}
	void Render(CRenderContext& renderContext) override
	{
		renderContext.SetVertexBuffer(m_vertexBuffer);
		renderContext.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		renderContext.VSSetShader(m_vsShader);
		renderContext.PSSetShader(m_psShader);
		renderContext.SetInputLayout(m_vsShader.GetInputLayout());
		renderContext.Draw(3,0);
	}
};

/*!
 *@brief	メイン関数。
 */
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
    //tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	//エンジンを初期化。
	if (Engine().Init(initParam) == true) {
		
		NewGO<CTriangleDraw>(0);
		NewGO<CComputeTest>(0);
		//初期化に成功。
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();
	
    return 0;
}

