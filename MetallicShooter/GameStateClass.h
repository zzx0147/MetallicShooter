#pragma once

enum class GameStateEnum
{
	INTRO,
	INGAME,
	GAMEEND
};

class GameStateClass
{
private:
	GameStateClass();
	static GameStateEnum m_GameState;
public:
	~GameStateClass();
	static GameStateEnum GetGameStateEnum();
	static void SetGameStateEnum(GameStateEnum);
};