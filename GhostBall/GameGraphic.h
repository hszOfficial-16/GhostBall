#ifndef _GAME_GRAPHIC_H_
#define _GAME_GRAPHIC_H_

class GameTexture
{
public:


private:
	class Impl;
	Impl* m_pImpl;
private:
	GameTexture();
	~GameTexture() = default;
	friend class TextureManager;
};

class TextureManager
{
public:

private:

public:
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	static TextureManager& GetInstance()
	{
		static TextureManager instance;
		return instance;
	}
private:
	TextureManager();
};

#endif