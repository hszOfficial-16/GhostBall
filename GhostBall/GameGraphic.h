#ifndef _GAME_GRAPHIC_H_
#define _GAME_GRAPHIC_H_

#include "GameResourceManager.h"

class GameTexture
{
public:


private:
	class Impl;
	Impl* m_pImpl;

private:
	GameTexture();
	~GameTexture() = default;
	friend class GameTextureManager;
};

class GameTextureManager : public GameResourceManager<GameTexture>
{
public:
	void LoadFromFile(std::wstring strFile);
	void LoadFromPath(std::wstring strPath);
	void LoadFromPack(std::wstring strPack);
};

#endif