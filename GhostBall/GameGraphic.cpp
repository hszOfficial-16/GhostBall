#include "GameGraphic.h"
#include "GameUtils.h"

#include <SDL.h>
#include <SDL_image.h>

#include <filesystem>

class GameWindow::Impl
{
public:
	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRenderer;

public:
	Impl()
	{
		m_pWindow = SDL_CreateWindow("ÓÄÁéÇò", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	}
	~Impl()
	{
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);
	}
};

GameWindow::GameWindow()
{
	m_pImpl = new Impl();
}

GameWindow::~GameWindow()
{
	delete m_pImpl;
}

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
};

GameTexture::GameTexture()
{
	m_pImpl = new Impl();
}

GameTexture::~GameTexture()
{
	delete m_pImpl;
}

bool GameTextureManager::LoadTextureFromPath(std::string strPathName)
{
	using namespace std::filesystem;

	path pathLoading(strPathName);
	if (!exists(pathLoading))
	{
		return false;
	}

	directory_entry entryDirectory(pathLoading);
	if (entryDirectory.status().type() != file_type::directory)
	{
		return false;
	}

	directory_iterator listFile(entryDirectory);
	for (auto& iter : listFile)
	{
		SDL_Surface* pSurface = IMG_Load(strPathName.c_str());
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(GameWindow::GetInstance().m_pImpl->m_pRenderer, pSurface);

		GameTexture* pGameTexture = new GameTexture();
		pGameTexture->m_pImpl->m_nWidth = pSurface->w;
		pGameTexture->m_pImpl->m_nHeight = pSurface->h;
		pGameTexture->m_pImpl->m_pTexture = pTexture;
		          
		std::string strFileName = GameUtils::WString2String(iter.path().filename());

		Register(strFileName, pGameTexture);
	}

	return true;
}

bool GameTextureManager::LoadTextureFromPack(std::string strPackName)
{
	using namespace std::filesystem;
}