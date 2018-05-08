#include "stdafx.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "textureshaderclass.h"
#include "BitmapClass.h"
#include "graphicsclass.h"
#include "GameStateClass.h"
#include "InputClass.h"
#include "RenderManager.h"
#include <cstdlib>
#include <ctime>


GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	// Direct3D 객체 생성
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Direct3D 객체 초기화
	if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera 객체 생성
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// 카메라 포지션 설정
	m_Camera->SetPosition(0.0f, 0.0f, -6.0f);


	// m_TextureShader 객체 생성
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// m_TextureShader 객체 초기화
	if (!m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the Texture shader object.", L"Error", MB_OK);
		return false;
	}

	//m_renderManager 객체 초기화
	m_RenderManager = new RenderManager();
	m_RenderManager->Initialize(m_TextureShader,m_Direct3D);

	m_BackGround = new BitmapClass();
	if (!m_BackGround)
	{
		return false;
	}
	if (!m_BackGround->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, (WCHAR*)L"../MetallicShooter/data/MetallicShooterMain.png", screenWidth, screenHeight))
	{
		return false;
	}

	m_RenderManager->AddRenderTarget(m_BackGround);


	return true;
}


void GraphicsClass::Shutdown()
{
	// m_TextureShader 객체 반환
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// m_Camera 객체 반환
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D 객체 반환
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}

bool GraphicsClass::Frame()
{

	//k는 DestbitmapObjects 배열의 인덱스로 사용합니다
	int k = 0;

	static float rotation = 0.0f;

	// 각 프레임의 rotation 변수를 업데이트합니다.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	return Render(rotation);
}


bool GraphicsClass::Render(float rotation)
{
	// 씬을 그리기 위해 버퍼를 지웁니다
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// 카메라의 위치에 따라 뷰 행렬을 생성합니다
	m_Camera->Render();

	// 카메라 및 d3d 객체에서 월드, 뷰 및 투영 행렬을 가져옵니다
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// 모든 2D 렌더링을 시작하려면 Z 버퍼를 끕니다.
	m_Direct3D->TurnZBufferOff();


	//렌더 매니저에 등록된 비트맵들을 렌더링합니다.
	if (!m_RenderManager->Render(worldMatrix, viewMatrix, orthoMatrix))
	{
		return false;
	}

	////m_DestBitmapObject 안에 들어있는 모든 오브젝트를 렌더링합니다.
	//for (int i = 0; i < m_BitmapArrayLength; ++i)
	//{
	//	// 비트 맵 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
	//	if (m_DestBitmapObjects[i])
	//	{
	//		if (!m_DestBitmapObjects[i]->Render(m_Direct3D->GetDeviceContext(), m_DestBitmapObjects[i]->GetNextPosX(), m_DestBitmapObjects[i]->GetNextPosY()))
	//		{
	//			return false;
	//		}

	//		// 텍스처 쉐이더로 비트 맵을 렌더링합니다.	
	//		if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_DestBitmapObjects[i]->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_DestBitmapObjects[i]->GetTexture()))
	//		{
	//			return false;
	//		}
	//	}
	//}
	


	// 모든 2D 렌더링이 완료되었으므로 Z 버퍼를 다시 켜십시오.
	m_Direct3D->TurnZBufferOn();

	// 버퍼의 내용을 화면에 출력합니다
	m_Direct3D->EndScene();

	return true;
}