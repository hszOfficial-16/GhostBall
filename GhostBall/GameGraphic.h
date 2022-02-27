#ifndef _GAME_GRAPHIC_H_
#define _GAME_GRAPHIC_H_

#include <string>
#include <initializer_list>

// 游戏图像相关基础结构

struct GamePosition
{
	float x;
	float y;
};

struct GameSize
{
	int nWidth;
	int nHeight;
};

enum class GameFlip
{
	NONE = 0,
	HORIZONTAL,
	VERTICAL
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
	class		Impl;
	Impl*		m_pImpl;

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
	const GameSize&		GetSize();

private:
	class				Impl;
	Impl*				m_pImpl;

private:
	GameTexture();
	~GameTexture();

	friend class GameTextureManager;
};

class GameTextureManager
{
public:
	bool	LoadFromFilter(std::string strFliterPath);
	bool	LoadFromPack(std::string strPackName);

private:
	class	Impl;
	Impl*	m_pImpl;

public:
	~GameTextureManager();
	GameTextureManager(const GameTextureManager&) = delete;
	GameTextureManager& operator=(const GameTextureManager&) = delete;
	static GameTextureManager& GetInstance()
	{
		static GameTextureManager instance;
		return instance;
	}
private:
	GameTextureManager();
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

class GameFontManager
{
public:
	bool	LoadFromFilter(std::string strFliterPath);
	bool	LoadFromPack(std::string strPackName);

private:
	class	Impl;
	Impl*	m_pImpl;

public:
	virtual ~GameFontManager();
	GameFontManager(const GameFontManager&) = delete;
	GameFontManager& operator=(const GameFontManager&) = delete;
	static GameFontManager& GetInstance()
	{
		static GameFontManager instance;
		return instance;
	}
private:
	GameFontManager();
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