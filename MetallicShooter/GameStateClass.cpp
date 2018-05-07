#include "stdafx.h"
#include "GameStateClass.h"


GameStateClass::GameStateClass()
{
}


GameStateClass::~GameStateClass()
{
}

GameStateEnum GameStateClass::GetGameStateEnum()
{
	return m_GameState;
}

void GameStateClass::SetGameStateEnum(GameStateEnum NewGameState)
{
	m_GameState = NewGameState;
}

GameStateEnum GameStateClass::m_GameState = GameStateEnum::INTRO;