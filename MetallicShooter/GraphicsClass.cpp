#include "stdafx.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "textureshaderclass.h"
#include "BitmapClass.h"
#include "graphicsclass.h"
#include "GameStateClass.h"
#include "InputClass.h"
#include "RenderManager.h"
#include "ActorManager.h"
#include "CreatorHelperClass.h"
#include "SpaceShipActorClass.h"
#include "PressEnterToStart.h"
#include "FlowingBackgroundActor.h"
#include "BulletActor.h"
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
	// Direct3D ��ü ����
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Direct3D ��ü �ʱ�ȭ
	if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera ��ü ����
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// ī�޶� ������ ����
	m_Camera->SetPosition(0.0f, 0.0f, -6.0f);


	// m_TextureShader ��ü ����
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// m_TextureShader ��ü �ʱ�ȭ
	if (!m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the Texture shader object.", L"Error", MB_OK);
		return false;
	}

	//m_renderManager ��ü �ʱ�ȭ
	m_RenderManager = new RenderManager();
	m_RenderManager->Initialize(m_TextureShader,m_Direct3D);

	//m_ActorManager ��ü �ʱ�ȭ
	m_ActorManager = new ActorManager();
	m_ActorManager->Initialize();

	//CreatorHelperClass ��ü �ʱ�ȭ
	m_CreatorHelper = new CreatorHelperClass();
	m_CreatorHelper->Initalize(m_RenderManager, m_ActorManager);

	//���� ������Ʈ ���� 
	GameStateClass::SetGameStateEnum(GameStateEnum::INTRO);

	
	//�����̽��� ��ü�� ������
	auto SpaceShip = m_CreatorHelper->CreateObject<SpaceShipActorClass>();
	if (!SpaceShip)
	{
		return false;
	}
	if (!SpaceShip->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight,
		(WCHAR*)L"../MetallicShooter/data/Rocket.png", 60, 60, 10, 1, new GameStateEnum[1]{ GameStateEnum::INGAME }))
	{
		return false;
	}
	//�����̽��� ���� �ҷ� ��ü�� ����
	if (!SpaceShip->InitalizeBullet(m_CreatorHelper, m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight,
		(WCHAR*)L"../MetallicShooter/data/Bullet.png", 10, 20, 10, 1, new GameStateEnum[1]{ GameStateEnum::INGAME }))
	{
		return false;
	}
	

	//��׶��� ��ü�� ������
	m_BackGround = m_CreatorHelper->CreateObject<BitmapClass>();
	if (!m_BackGround)
	{
		return false;
	}
	if (!m_BackGround->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight,
		(WCHAR*)L"../MetallicShooter/data/MetallicShooterMain.png", screenWidth, screenHeight, 0, 1,
		new GameStateEnum[3]{ GameStateEnum::INTRO }))
	{
		return false;
	}

	auto pressEnterToStart = m_CreatorHelper->CreateObject<PressEnterToStart>();
	if (!pressEnterToStart)
	{
		return false;
	}
	if (!pressEnterToStart->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight,
		(WCHAR*)L"../MetallicShooter/data/Press.png", 600 , 60, 1, 1, new GameStateEnum[1]{ GameStateEnum::INTRO }))
	{
		return false;
	}
	pressEnterToStart->SetNextPosX(660);
	pressEnterToStart->SetNextPosY(900);
	
	auto backGround1 = m_CreatorHelper->CreateObject<FlowingBackgroundActor>();
	if (!backGround1)
	{
		return false;
	}
	if (!backGround1->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight,
		(WCHAR*)L"../MetallicShooter/data/FlowingBackground.png", screenWidth, screenHeight, 0, 1, new GameStateEnum[1]{ GameStateEnum::INGAME }))
	{
		return false;
	}

	auto backGround2 = m_CreatorHelper->CreateObject<FlowingBackgroundActor>();
	if (!backGround2)
	{
		return false;
	}
	if (!backGround2->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight,
		(WCHAR*)L"../MetallicShooter/data/FlowingBackground.png", screenWidth, screenHeight, 0, 1, new GameStateEnum[1]{ GameStateEnum::INGAME }))
	{
		return false;
	}

	backGround1->InitPos(0, 0);
	backGround2->InitPos(0, 1080);

	m_RenderManager->Sort();

	return true;
}

void GraphicsClass::Shutdown()
{
	// m_TextureShader ��ü ��ȯ
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// m_Camera ��ü ��ȯ
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D ��ü ��ȯ
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}

bool GraphicsClass::Frame()
{
	m_ActorManager->Frame();

	static float rotation = 0.0f;

	// �� �������� rotation ������ ������Ʈ�մϴ�.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	return Render(rotation);
}

bool GraphicsClass::Render(float rotation)
{
	// ���� �׸��� ���� ���۸� ����ϴ�
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// ī�޶��� ��ġ�� ���� �� ����� �����մϴ�
	m_Camera->Render();

	// ī�޶� �� d3d ��ü���� ����, �� �� ���� ����� �����ɴϴ�
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	// ��� 2D �������� �����Ϸ��� Z ���۸� ���ϴ�.
	m_Direct3D->TurnZBufferOff();


	//���� �Ŵ����� ��ϵ� ��Ʈ�ʵ��� �������մϴ�.
	if (!m_RenderManager->Render(worldMatrix, viewMatrix, orthoMatrix))
	{
		return false;
	}

	////m_DestBitmapObject �ȿ� ����ִ� ��� ������Ʈ�� �������մϴ�.
	//for (int i = 0; i < m_BitmapArrayLength; ++i)
	//{
	//	// ��Ʈ �� ���ؽ��� �ε��� ���۸� �׷��� ������ ���ο� ��ġ�Ͽ� �׸��⸦ �غ��մϴ�.
	//	if (m_DestBitmapObjects[i])
	//	{
	//		if (!m_DestBitmapObjects[i]->Render(m_Direct3D->GetDeviceContext(), m_DestBitmapObjects[i]->GetNextPosX(), m_DestBitmapObjects[i]->GetNextPosY()))
	//		{
	//			return false;
	//		}

	//		// �ؽ�ó ���̴��� ��Ʈ ���� �������մϴ�.	
	//		if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_DestBitmapObjects[i]->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_DestBitmapObjects[i]->GetTexture()))
	//		{
	//			return false;
	//		}
	//	}
	//}
	


	// ��� 2D �������� �Ϸ�Ǿ����Ƿ� Z ���۸� �ٽ� �ѽʽÿ�.
	m_Direct3D->TurnZBufferOn();

	// ������ ������ ȭ�鿡 ����մϴ�
	m_Direct3D->EndScene();

	return true;
}