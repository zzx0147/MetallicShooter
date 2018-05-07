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
	int m_NextPosX = 0;
	int m_NextPosY = 0;

	float m_TextureUStart = 0.0f;
	float m_TextureUEnd = 1.0f;
	float m_TextureVStart = 0.0f;
	float m_TextureVEnd = 1.0f;
};

