#include "stdafx.h"
#include "BitmapClass.h"
#include "TextureClass.h"
#include "GameStateClass.h"
#include <atlstr.h>

BitmapClass::BitmapClass()
{
}

BitmapClass::BitmapClass(const BitmapClass& other)
{
}

BitmapClass::~BitmapClass()
{
}

bool BitmapClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext,const int& screenWidth,const int& screenHeight, WCHAR* textureFilename,const int& bitmapWidth, const int& bitmapHeight,const int& renderPriority,const int& enabledStatesCount,GameStateEnum* enabledStates)
{
	//ȭ�� ũ�⸦ ��� ������ ����
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	//�������� ��Ʈ���� �ȼ��� ũ�⸦ ����
	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;

	//������ �켱������ ��������� ����
	m_renderPriority = renderPriority;

	// ���� ������ ��ġ�� ������ �ʱ�ȭ�մϴ�.
	m_previousPosX = -1;
	m_previousPosY = -1;

	//���� �� �ε��� ���۸� �ʱ�ȭ�մϴ�.
	if (!InitializeBuffers(device))
	{
		return false;
	}
	//������ ������ ���� �����̽��� �����մϴ�.
	m_EnabledState = enabledStates;
	m_EnabledStateCount = enabledStatesCount;

	//�� ���� �ؽ�ó�� �ε��մϴ�.
	return LoadTexture(device, deviceContext, textureFilename);
}

void BitmapClass::Shutdown()
{
	//�� �ؽ��ĸ� ��ȯ�մϴ�.
	ReleaseTexture();

	//���ؽ� �� �ε��� ���۸� �����մϴ�.
	ShutdownBuffers();

}

bool BitmapClass::Render(ID3D11DeviceContext* deviceContext, int positionX, int positionY)
{
	//ȭ���� �ٸ� ��ġ�� �������ϱ� ���� ���� ���� ���۸� �ٽ� �����մϴ�.
	if (!UpdateBuffers(deviceContext, positionX, positionY))
	{
		return false;
	}

	//�׸��⸦ �غ��ϱ� ���� �׷��� ���������ο� �������� �ε��� ���۸� �����ϴ�.
	RenderBuffers(deviceContext);

	return true;
}

bool BitmapClass::operator<(BitmapClass& RightBitmap)
{
	if (this->GetRenderPriority() < RightBitmap.GetRenderPriority())
	{
		return true;
	}
	return false;
}

bool BitmapClass::operator>(BitmapClass& RightBitmap)
{
	if (this->GetRenderPriority() > RightBitmap.GetRenderPriority())
	{
		return true;
	}
	return false;
}

int BitmapClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* BitmapClass::GetTexture()
{
	return m_Texture->GetTexture();
}

int BitmapClass::GetPreviousPosX()
{
	return m_previousPosX;
}

int BitmapClass::GetPreviousPosY()
{
	return m_previousPosY;
}

void BitmapClass::SetNextPosX(int NewX)
{
	m_nextPosX = NewX;
}

void BitmapClass::SetNextPosY(int NewY)
{
	m_nextPosY = NewY;
}

int BitmapClass::GetNextPosX()
{
	return m_nextPosX;
}

int BitmapClass::GetNextPosY()
{
	return m_nextPosY;
}

bool BitmapClass::GetIsVisible()
{
	return m_isVisible;
}

bool BitmapClass::GetIsFitState()
{
	GameStateEnum nowState = GameStateClass::GetGameStateEnum();
	for (int i = 0; i < m_EnabledStateCount; ++i)
	{
		if (m_EnabledState[i] == nowState)
		{
			return true;
		}
	}
	return false;
}

int BitmapClass::GetScreenWidth()
{
	return m_screenWidth;
}

int BitmapClass::GetScreenHeight()
{
	return m_screenHeight;
}

void BitmapClass::SetIsVisible(bool visibleNow)
{
	m_isVisible = visibleNow;
}

void BitmapClass::InitPos(int x, int y)
{
	m_previousPosX = x;
	m_previousPosY = y;
}

bool BitmapClass::InitializeBuffers(ID3D11Device* device)
{
	//���� �迭�� ���� ���� �ε��� �迭�� �ε��� ���� �����մϴ�.
	m_indexCount = m_vertexCount = 6;

	//���� �迭�� ����ϴ�.
	VertexType* vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	//���� �迭�� 0���� �ʱ�ȭ�մϴ�.
	memset(vertices, 0, (sizeof(VertexType)*m_vertexCount));

	//�ε��� �迭�� ����ϴ�.
	unsigned long* indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	//�����ͷ� �ε��� �迭�� �ε��մϴ�.
	for (int i = 0; i < m_indexCount; ++i)
	{
		indices[i] = i;
	}

	//���� ���� ������ ����ü�� �����մϴ�.
	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType)*m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//subresource������ ���� �����Ϳ� ���� �����͸� �����մϴ�.
	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//���� ���� ���۸� ����ϴ�.
	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	//���� �ε��� ������ ����ü�� �����մϴ�.
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long)* m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//�ε��� �����͸� ����Ű�� ���� ���ҽ� ����ü�� �ۼ��մϴ�.
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//�ε��� ���۸� �����մϴ�.
	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	//�����ǰ� ���� �Ҵ�� ���� ���ۿ� �ε��� ���۸� �����մϴ�.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

	return true;
}

void BitmapClass::ShutdownBuffers()
{
	//�ε��� ���۸� �����մϴ�.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	//���� ���۸� �����մϴ�
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

bool BitmapClass::UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	//�� ��Ʈ���� ������ �� ��ġ�� ������� ���� ��� ���� ���۸� ������Ʈ ���� ���ʽÿ�
	//���� �ùٸ� �Ű� ������ �ֽ��ϴ�.
	//if ((positionX == m_previousPosX) && (positionY == m_previousPosY))
	//{
	//	return true;
	//}

	// ����� ��� �������Ǵ� ��ġ�� ������Ʈ�մϴ�
	m_previousPosX = positionX;
	m_previousPosY = positionY;

	//��Ʈ �� ������ ȭ�� ��ǥ�� ����մϴ�.
	left = (float)((m_screenWidth / 2)*-1) + (float)positionX;

	//��Ʈ �� �������� ȭ�� ��ǥ�� ����մϴ�.
	right = left + (float)m_bitmapWidth;

	//��Ʈ �� ����� ȭ�� ��ǥ�� ����մϴ�.
	top = (float)(m_screenHeight / 2) - (float)positionY;

	//��Ʈ  �� �ϴ��� ȭ�� ��ǥ�� ����մϴ�.
	bottom = top - (float)m_bitmapHeight;

	//���� �迭�� ����ϴ�.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	//���� �迭�� �����͸� �ε��մϴ�.
	//ù��° �ﰢ��
	vertices[0].position = XMFLOAT3(left, top, 0.0f); // top left
	vertices[0].texture = XMFLOAT2(m_TextureUStart, m_TextureVStart);

	vertices[1].position = XMFLOAT3(right, bottom, 0.0f);//bottom right
	vertices[1].texture = XMFLOAT2(m_TextureUEnd, m_TextureVEnd);

	vertices[2].position = XMFLOAT3(left, bottom, 0.0f);//bottom Left
	vertices[2].texture = XMFLOAT2(m_TextureUStart, m_TextureVEnd);

	//�ι�° �ﰢ��
	vertices[3].position = XMFLOAT3(left, top, 0.0f); // top left
	vertices[3].texture = XMFLOAT2(m_TextureUStart,m_TextureVStart);

	vertices[4].position = XMFLOAT3(right, top, 0.0f);//top right
	vertices[4].texture = XMFLOAT2(m_TextureUEnd, m_TextureVStart);

	vertices[5].position = XMFLOAT3(right, bottom, 0.0f);//bottom right
	vertices[5].texture = XMFLOAT2(m_TextureUEnd, m_TextureVEnd);

	//���ؽ� ���۸� �� �� �ֵ��� ��޴ϴ�.
	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	//���� ������ �����͸� ����Ű�� �����͸� ��´�.
	verticesPtr = (VertexType*)mappedResource.pData;

	//�����͸� ���� ���ۿ� �����մϴ�.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType)* m_vertexCount));

	//���� ������ ����� �����մϴ�.
	deviceContext->Unmap(m_vertexBuffer, 0);

	//�� �̻� �ʿ����� ���� ������ �迭�� �����մϴ�.
	delete[] vertices;
	vertices = 0;

	return true;
}

void BitmapClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	//���� ������ ������ �������� �����մϴ�.
	UINT stride = sizeof(VertexType);
	UINT offset = 0;

	//������ �� �� �ֵ��� �Է� ��������� ���� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//������ �� �� �ֵ��� �Է� ��������� �ε��� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//���� ���۸� �׸� �⺻���� �����մϴ�. ���⼭�� �ﰢ������ �����մϴ�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool BitmapClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* filename)
{
	//�ؽ�ó ������Ʈ�� �����Ѵ٤�.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	//�ؽ�ó ������Ʈ�� �ʱ�ȭ�Ѵ�.

	return m_Texture->Initialize(device, deviceContext, filename);
}

void BitmapClass::ReleaseTexture()
{
	//�ؽ��� ������Ʈ�� �������Ѵ�.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}

void BitmapClass::SetTextureUV(float uStart, float uEnd, float vStart, float vEnd)
{
	m_TextureUStart = uStart;
	m_TextureVStart = vStart;
	m_TextureUEnd = uEnd;
	m_TextureVEnd = vEnd;
}

int BitmapClass::GetBitmapHeight()
{
	return m_bitmapHeight;
}

int BitmapClass::GetBitmapWidth()
{
	return m_bitmapWidth;
}

int BitmapClass::GetRenderPriority()
{
	return m_renderPriority;
}

