#pragma once

//Àü¿ª


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class D3DClass;
class CameraClass;
class TextureShaderClass;
class BitmapClass;
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render(float);

private:
	D3DClass * m_Direct3D = nullptr;
	CameraClass* m_Camera = nullptr;
	TextureShaderClass* m_TextureShader = nullptr;

	BitmapClass** m_DestBitmapObjects = nullptr;
	int m_BitmapArrayLength = 300;
};

