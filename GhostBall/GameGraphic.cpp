#include "GameGraphic.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameResourceManager.h"

// GameWindow 实现

class GameWindow::Impl
{
public:
	SDL_Window*		m_pWindow;
	SDL_Renderer*	m_pRenderer;

public:
	Impl()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		m_pWindow = SDL_CreateWindow("幽灵球", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

		SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	}
	~Impl()
	{
		SDL_DestroyRenderer(m_pRenderer);
		SDL_DestroyWindow(m_pWindow);

		SDL_Quit();
	}
};

GameSize GameWindow::GetWindowSize()
{
	GameSize campWindowSize;
	SDL_GetWindowSize(m_pImpl->m_pWindow, &campWindowSize.nWidth, &campWindowSize.nHeight);
	return campWindowSize;
}

GameSize GameWindow::GetWindowMaxSize()
{
	GameSize campWindowMaxSize;
	SDL_GetWindowMaximumSize(m_pImpl->m_pWindow, &campWindowMaxSize.nWidth, &campWindowMaxSize.nHeight);
	return campWindowMaxSize;
}

GameSize GameWindow::GetWindowMinSize()
{
	GameSize campWindowMinSize;
	SDL_GetWindowMinimumSize(m_pImpl->m_pWindow, &campWindowMinSize.nWidth, &campWindowMinSize.nHeight);
	return campWindowMinSize;
}

void GameWindow::SetWindowSize(const GameSize& windowSize)
{
	SDL_SetWindowSize(m_pImpl->m_pWindow, windowSize.nWidth, windowSize.nHeight);
}

void GameWindow::SetWindowMaxSize(const GameSize& windowMaxSize)
{
	SDL_SetWindowSize(m_pImpl->m_pWindow, windowMaxSize.nWidth, windowMaxSize.nHeight);
}

void GameWindow::SetWindowMinSize(const GameSize& windowMinSize)
{
	SDL_SetWindowSize(m_pImpl->m_pWindow, windowMinSize.nWidth, windowMinSize.nHeight);
}

GameWindow::GameWindow()
{
	m_pImpl = new Impl();
}

GameWindow::~GameWindow()
{
	delete m_pImpl;
}

// GameTexture 实现

class GameTexture::Impl
{
public:
	GameSize		m_size;
	SDL_Texture*	m_pTexture;

public:
	Impl()
	{
		m_size.nWidth = 0;
		m_size.nHeight = 0;
		m_pTexture = nullptr;
	}
	~Impl()
	{
		if (m_pTexture)
		{
			SDL_DestroyTexture(m_pTexture);
		}
	}
};

const GameSize& GameTexture::GetSize()
{
	return m_pImpl->m_size;
}

GameTexture::GameTexture()
{
	m_pImpl = new Impl();
}

GameTexture::~GameTexture()
{
	delete m_pImpl;
}

class GameTextureManager::Impl
{
public:
	GameResourceManager m_textureManager;

public:
	Impl()
	{
		m_textureManager.SetConstructFunc([&](std::string strFileName)->void* {
			SDL_Surface* pSurface = IMG_Load(strFileName.c_str());
			SDL_Texture* pTexture = SDL_CreateTextureFromSurface(GameWindow::GetInstance().m_pImpl->m_pRenderer, pSurface);
			GameTexture* pGameTexture = new GameTexture();
			pGameTexture->m_pImpl->m_size.nWidth = pSurface->w;
			pGameTexture->m_pImpl->m_size.nHeight = pSurface->h;
			pGameTexture->m_pImpl->m_pTexture = pTexture;
			return (void*)pGameTexture;
			});
	}
};

bool GameTextureManager::LoadFromFilter(std::string strFilterPath)
{
	return m_pImpl->m_textureManager.LoadFromFilter(strFilterPath);
}

bool GameTextureManager::LoadFromPack(std::string strPackName)
{
	return m_pImpl->m_textureManager.LoadFromPack(strPackName);
}

GameTextureManager::GameTextureManager()
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	m_pImpl = new Impl();
}

GameTextureManager::~GameTextureManager()
{
	IMG_Quit();
	delete m_pImpl;
}

// GameFont 实现

class GameFont::Impl
{
public:
	TTF_Font*	m_pFont;

public:
	Impl()
	{
		m_pFont = nullptr;
	}
	~Impl()
	{
		if (m_pFont)
		{
			TTF_CloseFont(m_pFont);
		}
	}
};

GameFont::GameFont()
{
	m_pImpl = new Impl();
}

GameFont::~GameFont()
{
	delete m_pImpl;
}

class GameFontManager::Impl
{
public:
	GameResourceManager m_fontManager;

public:
	Impl()
	{
		m_fontManager.SetConstructFunc([&](std::string strFileName)->void* {
			TTF_Font* pFont = TTF_OpenFont(strFileName.c_str(), 64);
			GameFont* pGameFont = new GameFont();
			pGameFont->m_pImpl->m_pFont = pFont;
			return (void*)pGameFont;
			});
	}
};

bool GameFontManager::LoadFromFilter(std::string strFilterPath)
{
	return m_pImpl->m_fontManager.LoadFromFilter(strFilterPath);
}

bool GameFontManager::LoadFromPack(std::string strPackName)
{
	return m_pImpl->m_fontManager.LoadFromPack(strPackName);
}

GameFontManager::GameFontManager()
{
	TTF_Init();
	m_pImpl = new Impl();
}

GameFontManager::~GameFontManager()
{
	TTF_Quit();
	delete m_pImpl;
}

// GameImage 实现

GameImage* GameImageManager::CreateStaticImage(GameTexture* pGameTexture)
{
	GameImage* arrImages = new GameImage[1];
	arrImages[0] = { pGameTexture , 0 };
	return arrImages;
}

GameImage* GameImageManager::CreateDynamicImage(std::initializer_list<GameImage>& ilFrames)
{
	GameImage* arrImages = new GameImage[ilFrames.size()];
	for (int index = 0; index < ilFrames.size(); index++)
	{
		arrImages[index] = *(ilFrames.begin() + index);
	}
	return arrImages;
}

void GameImageManager::DestroyImage(GameImage* pGameImage)
{
	if (pGameImage)
	{
		delete[] pGameImage;
	}
}