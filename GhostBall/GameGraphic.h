#ifndef _GAME_GRAPHIC_H_
#define _GAME_GRAPHIC_H_

#include "GameResourceManager.h"

class GameWindow
{
public:
	

private:
	class Impl;
	Impl* m_pImpl;

public:
	~GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;
	static GameWindow& GetInstance()
	{
		static GameWindow instance;
		return instance;
	}
private:
	GameWindow();

	friend class GameTextureManager;
};

class GameTexture
{
public:


private:
	class Impl;
	Impl* m_pImpl;

private:
	GameTexture();
	~GameTexture();

	friend class GameTextureManager;
};

class GameTextureManager : public GameResourceManager<GameTexture>
{
public:
	bool	LoadFromPath(std::string strPathName);
	bool	LoadFromPack(std::string strPackName);
};

#endif