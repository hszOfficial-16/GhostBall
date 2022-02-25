#ifndef _GAME_GRAPHIC_H_
#define _GAME_GRAPHIC_H_

#include "GameResourceManager.h"
#include "GameObjectPool.h"

#include <initializer_list>

struct GameSize
{
	int nWidth;
	int nHeight;
};

class GameWindow
{
public:
	GameSize	GetWindowSize();
	GameSize	GetWindowMaxSize();
	GameSize	GetWindowMinSize();

	void		SetWindowSize(const GameSize& windowSize);
	void		SetWindowMaxSize(const GameSize& windowMaxSize);
	void		SetWindowMinSize(const GameSize& windowMinSize);

private:
	class	Impl;
	Impl*	m_pImpl;

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
	bool LoadFromPath(std::string strPathName);
	bool LoadFromPack(std::string strPackName);
};

class GameFont
{
public:


private:
	class Impl;
	Impl* m_pImpl;

private:
	GameFont();
	~GameFont();

	friend class GameFontManager;
};

class GameFontManager : public GameResourceManager<GameFont>
{
public:
	bool LoadFromPath(std::string strPathName);
	bool LoadFromPack(std::string strPackName);
};

struct GameImage
{
	GameTexture*	pTexture;
	unsigned int	nDuration;
};

class GameImageManager
{
public:
	GameImage*	CreateStaticImage(GameTexture* pGameTexture);
	GameImage*	CreateDynamicImage(std::initializer_list<GameImage>& ilFrames);

	void		DestroyImage(GameImage* pGameImage);
	
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