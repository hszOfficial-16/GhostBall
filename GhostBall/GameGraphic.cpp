#include "GameGraphic.h"

#include <SDL.h>
#include <SDL_image.h>

class GameTexture::Impl
{
public:
	int				m_nWidth;
	int				m_nHeight;
	SDL_Texture*	m_pTexture;

public:
	Impl()
	{
		m_nWidth = 0;
		m_nHeight = 0;
		m_pTexture = nullptr;
	}

	~Impl()
	{

	}
};

void GameTextureManager::Load(std::wstring)
{

}