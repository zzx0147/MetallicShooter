#pragma once

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

	bool Initialize(ID3D11Device*, ID3D11DeviceContext* deviceContext, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	void SetTextureUV(float, float,float,float);

	int GetBitmapWidth();
	int GetBitmapHeight();


	int GetPreviousPosX();
	int GetPreviousPosY();
	void SetNextPosX(int);
	void SetNextPosY(int);
	int GetNextPosX();
	int GetNextPosY();
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
	int m_vertexCount = 0;
	int m_indexCount = 0;
	TextureClass* m_Texture = nullptr;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	int m_bitmapWidth = 0;
	int m_bitmapHeight = 0;
	int m_previousPosX = 0;
	int m_previousPosY = 0;
	int m_nextPosX = 0;
	int m_nextPosY = 0;

	float m_TextureUStart = 0.0f;
	float m_TextureUEnd = 1.0f;
	float m_TextureVStart = 0.0f;
	float m_TextureVEnd = 1.0f;

	//이 비트맵을 렌더링 할 것인지를 나타내는 변수입니다. true일 경우 화면에 렌더링되고 false 일 경우 RenderManager에서 감지하고 렌더링하지 않습니다.
	bool m_isVisible = true;

	//렌더링 우선 순위입니다. 낮을수록 먼저 렌더링되며 우선순위가 같을 경우 나중에 넣은 것이 나중에 렌더링됩니다. 0은 백그라운드입니다.
	int m_renderPriority = 1;

};

