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
	if (m_RenderTarget.empty())
	{
		return true;
	}

	list<BitmapClass*>::iterator itor;
	for (itor = m_RenderTarget.begin(); itor != m_RenderTarget.end(); itor++)
	{
		if ((*itor)->GetIsVisible()&& (*itor)->GetIsFitState())
		{
			if (!(*itor)->Render(m_direct3D->GetDeviceContext(), (*itor)->GetNextPosX(), (*itor)->GetNextPosY()))
			{
				return false;
			}

			if (!m_textureShader->Render(m_direct3D->GetDeviceContext(), (*itor)->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, (*itor)->GetTexture()))
			{
				return false;
			}
		}
	}
	return true;
}

bool RenderManager::AddRenderTarget(BitmapClass* newRenderTarget)
{
	m_RenderTarget.push_back(newRenderTarget);
	return true;
}

void RenderManager::Sort()
{	
	m_RenderTarget.sort([](BitmapClass* a, BitmapClass* b) {return a->GetRenderPriority() < b->GetRenderPriority(); });
}

void RenderManager::Shutdown()
{

}