#pragma once
#include <list>
using namespace std;

class BitmapClass;
class TextureShaderClass;
class D3DClass;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();
	bool Initialize(TextureShaderClass*,D3DClass*);
	bool Render(XMMATRIX, XMMATRIX, XMMATRIX);
	bool AddRenderTarget(BitmapClass*);
	void Shutdown();
private:
	list<BitmapClass*> RenderTarget;
	TextureShaderClass* m_textureShader;
	D3DClass* m_direct3D;
};

