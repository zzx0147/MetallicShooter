#include "stdafx.h"
#include "TextureClass.h"
#include <cstdio>

TextureClass::TextureClass()
{
	m_texture = nullptr;
}


TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* filename)
{
	HRESULT result;

	//텍스처를 로드합니다.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void TextureClass::Shutdown()
{
	//텍스처 뷰 리소스를 해제한다.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}
