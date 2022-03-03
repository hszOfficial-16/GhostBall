#ifndef _GAME_GRAPHIC_H_
#define _GAME_GRAPHIC_H_

#include <string>
#include <initializer_list>

// 世界/屏幕坐标类型
struct GamePoint
{
	float x, y;
};

// 图片资源文件的宽与高
struct GameSize
{
	int nWidth, nHeight;
};

// 图片绘制矩形
struct GameRect
{
	float x, y, w, h;
};

// RGBA 颜色
struct GameColor
{
	int r, g, b, a;
};

// 图片翻转类型
enum class GameFlip
{
	NONE = 0,
	HORIZONTAL,
	VERTICAL
};

// 窗口单例类
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

// 字体类(游戏资源)
class GameFont
{
private:
	class Impl;
	Impl* m_pImpl;

private:
	GameFont();
	~GameFont();

	friend class GameFontManager;
};

// 字体资源管理者单例类
class GameFontManager
{
public:
	bool LoadFromFilter(std::string strFliterPath);

	bool LoadFromPack(std::string strPackName);

	GameFont* Get(std::string strFileName);

private:
	class Impl;
	Impl* m_pImpl;

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

// 纹理类(游戏资源)
class GameTexture
{
private:
	class				Impl;
	Impl*				m_pImpl;

private:
	GameTexture();
	~GameTexture();

	friend class GameTextureManager;
};

// 纹理资源管理者单例类
class GameTextureManager
{
public:
	/* 读取文件夹下的所有文件并构造为纹理
	* @param 文件夹的相对路径
	* @return 是否读取成功
	*/
	bool LoadFromFilter(std::string strFliterPath);

	/* 读取二进制包下的所有文件并构造为纹理
	* @param 文件夹的相对路径
	* @return 是否读取成功
	*/
	bool LoadFromPack(std::string strPackName);

	GameTexture* CreateTextSolid(std::string strTextContent, GameFont* pFont,
		const GameColor& colorFg);

	GameTexture* CreateTextBlended(std::string strTextContent, GameFont* pFont,
		const GameColor& colorFg);

	GameTexture* CreateTextShaded(std::string strTextContent, GameFont* pFont,
		const GameColor& colorFg, const GameColor& colorBg);

	/* 根据纹理文件名获取纹理对象指针
	* @param 纹理文件名
	* @return 纹理对象指针
	*/
	GameTexture* Get(std::string strFileName);

	/* 根据参数提供信息在窗口内绘制纹理
	* @param pTexture: 需要绘制的纹理的指针
	* rectDraw: 纹理绘制的矩形区域
	* fAngle: 纹理绘制的旋转角度(弧度制)
	* pointAnchor: 纹理绘制的旋转锚点
	* emFlip: 纹理绘制的翻转类型
	* @return 无
	*/
	void Render(GameTexture* pTexture,
		const GameRect& rectDraw,
		const double& fAngle,
		const GamePoint& pointAnchor,
		const GameFlip& emFlip
	);

private:
	class Impl;
	Impl* m_pImpl;

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

// 图片对象类
struct GameImage
{
	GameTexture*	pTexture;
	unsigned int	nDuration;
};

// 图片对象单例工厂
class GameImageFactory
{
public:
	GameImage*	CreateStaticImage(GameTexture* pGameTexture);
	GameImage*	CreateDynamicImage(std::initializer_list<GameImage>& ilFrames);

	void		DestroyImage(GameImage* pGameImage);
	
public:
	~GameImageFactory() = default;
	GameImageFactory(const GameImageFactory&) = delete;
	GameImageFactory& operator=(const GameImageFactory&) = delete;
	static GameImageFactory& GetInstance()
	{
		static GameImageFactory instance;
		return instance;
	}
private:
	GameImageFactory();
};

#endif