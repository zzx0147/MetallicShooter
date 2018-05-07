#pragma once
#include <d3d11.h>
#include <d3dx11tex.h>

class TextureClass
{

public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();


	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, WCHAR* filename);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:

private:

	ID3D11ShaderResourceView * m_texture = nullptr;
};