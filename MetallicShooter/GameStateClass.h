#pragma once

enum class GameStateEnum
{
	INTRO,
	MAIN,
	INTRODUCTIONSCENE,
	HOWTOSCENE,
	GAMEREADY,
	ENEMYREADY,
	MYTURN,
	ENEMYTURN,
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