#include "stdafx.h"
#include "RenderManager.h"
#include "BitmapClass.h"
#include "TextureShaderClass.h"
#include "D3DClass.h"

RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

bool RenderManager::Initialize(TextureShaderClass* shader,D3DClass* direct3D)
{

	m_textureShader = shader;
	m_direct3D = direct3D;
	return true;
}

bool RenderManager::Render(XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX orthoMatrix)
{
	if (RenderTarget.empty())
	{
		return true;
	}

	list<BitmapClass*>::iterator itor;
	for (itor = RenderTarget.begin(); itor != RenderTarget.end(); itor++)
	{
		if (!(*itor)->Render(m_direct3D->GetDeviceContext(), (*itor)->GetNextPosX(), (*itor)->GetNextPosY()))
		{
			return false;
		}

		if (!m_textureShader->Render(m_direct3D->GetDeviceContext(), (*itor)->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,(*itor)->GetTexture()))
		{
			return false;
		}
	}

	return true;
	
}


bool RenderManager::AddRenderTarget(BitmapClass* newRenderTarget)
{
	RenderTarget.push_back(newRenderTarget);
	return true;
}

void RenderManager::Shutdown()
{

}