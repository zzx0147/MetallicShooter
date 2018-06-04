#pragma once
#include "GameStateClass.h"

class TextureClass;
class BitmapClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();
	virtual bool Initialize(ID3D11Device*, ID3D11DeviceContext* deviceContext,const int&,const int&, WCHAR*,const int&,const int&,const int&,const int&,GameStateEnum*);

	void Shutdown();
	virtual bool Render(ID3D11DeviceContext*, int, int);

	bool operator<(BitmapClass&);
	bool operator>(BitmapClass&);

	ID3D11ShaderResourceView* GetTexture();
	int GetIndexCount();
	int GetBitmapWidth();
	int GetBitmapHeight();
	int GetPreviousPosX();
	int GetPreviousPosY();
	int GetNextPosX();
	int GetNextPosY();
	int GetRenderPriority();
	bool GetIsVisible();
	bool GetIsFitState();
	int GetScreenWidth();
	int GetScreenHeight();

	void SetTextureUV(float, float, float, float);
	void SetNextPosX(int);
	void SetNextPosY(int);
	void SetIsVisible(bool);
	void InitPos(int, int);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext* deviceContext, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer * m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	TextureClass* m_Texture = nullptr;
	
	int m_vertexCount = 0;
	int m_indexCount = 0;
	//플레이어의 모니터 크기를 나타냅니다. 처음 initalize에서 값을 받습니다.
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	//비트맵의 크기를 나타냅니다. 처음 initalize 에서 값을 받습니다.
	int m_bitmapWidth = 0;
	int m_bitmapHeight = 0;
	//이전에 있었던 위치와 다음 프레임으로 이동할 위치를 나타냅니다 둘이 같을 경우 처리하지 않습니다.
	int m_previousPosX = 0;
	int m_previousPosY = 0;
	int m_nextPosX = 0;
	int m_nextPosY = 0;
	//렌더링 우선 순위입니다. 낮을수록 먼저 렌더링되며 우선순위가 같을 경우 나중에 넣은 것이 나중에 렌더링됩니다. 0은 백그라운드입니다.
	int m_renderPriority = 1;
	//텍스쳐 UV를 조절하는 값들입니다 각각 UV의 시작과 끝부분을 나타냅니다.
	float m_TextureUStart = 0.0f;
	float m_TextureUEnd = 1.0f;
	float m_TextureVStart = 0.0f;
	float m_TextureVEnd = 1.0f;
	//이 비트맵을 렌더링 할 것인지를 나타내는 변수입니다. true일 경우 화면에 렌더링되고 false 일 경우 RenderManager에서 감지하고 렌더링하지 않습니다.
	bool m_isVisible = true;
	//이 비트맵이 어느 게임 스테이트에서 렌더링이 될 지를 결정합니다
	//isVisible이 false이거나 enabledState에 현재 GameState가 없을 시 렌더링되지 않습니다.
	GameStateEnum* m_EnabledState;
	int m_EnabledStateCount = 0;
};

