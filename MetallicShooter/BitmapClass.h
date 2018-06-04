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
	//�÷��̾��� ����� ũ�⸦ ��Ÿ���ϴ�. ó�� initalize���� ���� �޽��ϴ�.
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	//��Ʈ���� ũ�⸦ ��Ÿ���ϴ�. ó�� initalize ���� ���� �޽��ϴ�.
	int m_bitmapWidth = 0;
	int m_bitmapHeight = 0;
	//������ �־��� ��ġ�� ���� ���������� �̵��� ��ġ�� ��Ÿ���ϴ� ���� ���� ��� ó������ �ʽ��ϴ�.
	int m_previousPosX = 0;
	int m_previousPosY = 0;
	int m_nextPosX = 0;
	int m_nextPosY = 0;
	//������ �켱 �����Դϴ�. �������� ���� �������Ǹ� �켱������ ���� ��� ���߿� ���� ���� ���߿� �������˴ϴ�. 0�� ��׶����Դϴ�.
	int m_renderPriority = 1;
	//�ؽ��� UV�� �����ϴ� �����Դϴ� ���� UV�� ���۰� ���κ��� ��Ÿ���ϴ�.
	float m_TextureUStart = 0.0f;
	float m_TextureUEnd = 1.0f;
	float m_TextureVStart = 0.0f;
	float m_TextureVEnd = 1.0f;
	//�� ��Ʈ���� ������ �� �������� ��Ÿ���� �����Դϴ�. true�� ��� ȭ�鿡 �������ǰ� false �� ��� RenderManager���� �����ϰ� ���������� �ʽ��ϴ�.
	bool m_isVisible = true;
	//�� ��Ʈ���� ��� ���� ������Ʈ���� �������� �� ���� �����մϴ�
	//isVisible�� false�̰ų� enabledState�� ���� GameState�� ���� �� ���������� �ʽ��ϴ�.
	GameStateEnum* m_EnabledState;
	int m_EnabledStateCount = 0;
};

