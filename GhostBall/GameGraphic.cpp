#include "GameGraphic.h"
#include "GameUtils.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <filesystem>

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

bool GameTextureManager::LoadFromPath(std::string strPathName)
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
		SDL_Surface* pSurface = IMG_Load(GameUtils::WString2String(iter.path()).c_str());
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(GameWindow::GetInstance().m_pImpl->m_pRenderer, pSurface);

		GameTexture* pGameTexture = new GameTexture();
		pGameTexture->m_pImpl->m_size.nWidth = pSurface->w;
		pGameTexture->m_pImpl->m_size.nHeight = pSurface->h;
		pGameTexture->m_pImpl->m_pTexture = pTexture;
		          
		std::string strFileName = GameUtils::WString2String(iter.path().filename());

		Register(strFileName, pGameTexture);
	}

	return true;
}

bool GameTextureManager::LoadFromPack(std::string strPackName)
{
	using namespace std::filesystem;
}

GameTextureManager::GameTextureManager()
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
}

GameTextureManager::~GameTextureManager()
{
	IMG_Quit();
}

// GameFont 实现

class GameFont::Impl
{
public:
	TTF_Font* m_pFont;

public:
	Impl()
	{
		m_pFont = nullptr;
	}
	~Impl()
	{
		TTF_CloseFont(m_pFont);
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

bool GameFontManager::LoadFromPath(std::string strPathName)
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

		GameFont* pGameFont = new GameFont();
		pGameFont->m_pImpl->m_pFont = TTF_OpenFont(GameUtils::WString2String(iter.path()).c_str(), 64);

		std::string strFileName = GameUtils::WString2String(iter.path().filename());

		Register(strFileName, pGameFont);
	}

	return true;
}

bool GameFontManager::LoadFromPack(std::string strPackName)
{
	using namespace std::filesystem;
}

GameFontManager::GameFontManager()
{
	TTF_Init();
}

GameFontManager::~GameFontManager()
{
	TTF_Quit();
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
	for (size_t index = 0; index < ilFrames.size(); index++)
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