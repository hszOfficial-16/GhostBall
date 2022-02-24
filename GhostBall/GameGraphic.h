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

public:
	GameTexture();
	~GameTexture();

	friend class GameTextureManager;
};

class GameTextureManager : public GameResourceManager<GameTexture>
{
public:
	bool	LoadTextureFromPath(std::string strPathName);
	bool	LoadTextureFromPack(std::string strPackName);
};

class GameFont
{
public:


private:
	class Impl;
	Impl* m_pImpl;

public:
	GameFont();
	~GameFont();

	friend class GameFontManager;
};

class GameFontManager : public GameResourceManager<GameFont>
{
public:

};

class GameImage
{
public:

private:

};

class GameImageManager
{
public:


private:


public:
	~GameImageManager() = default;
	GameImageManager(const GameImageManager&) = delete;
	GameImageManager& operator=(const GameImageManager&) = delete;
	static GameImageManager& GetInstance()
	{
		static GameImageManager instance;
		return instance;
	}
private:
	GameImageManager();
};

#endif