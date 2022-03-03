#ifndef _GAME_SOURCE_POOL_H_
#define _GAME_SOURCE_POOL_H_

#include <string>

/* 负责管理游戏资源的生命周期
使用 C++ 默认的内存分配方式
*/
class GameResourceManager
{
public:
	/* 根据资源文件路径加载文件并返回资源对象指针的函数类型
	* @param 资源文件路径
	* @return 资源对象指针
	*/
	typedef void*(*ResourceConstructFunc)(std::string);

	/* 析构该指针对应的资源对象的函数类型
	* @param 资源对象指针
	* @return 无
	*/
	typedef void(*ResourceDeconstructFunc)(void*);

	/* 读取文件夹下的所有文件，并根据用户提供的函数构造资源对象
	* @param 文件夹的相对路径
	* @return 是否读取成功
	*/
	bool	LoadFromFilter(std::string strFliterPath);
	
	/* 读取二进制包下的所有文件，并根据用户提供的函数构造资源对象
	* @param 二进制包的相对路径
	* @return 是否读取成功
	*/
	bool	LoadFromPack(std::string strPackName);

	/* 根据文件名获取内存中的资源对象指针
	* @param 资源文件的文件名
	* @return 资源对象指针
	*/
	void*	Get(std::string strFileName);

	/* 清空资源管理者中的所有资源对象
	* @param 无
	* @return 无
	*/
	void	ClearAllResource();

	/* 设置资源对象的构造函数
	* @param 构造函数名
	* @return 无
	*/
	void	SetConstructFunc(ResourceConstructFunc funcConstructResource);

	/* 设置资源对象的析构函数
	* @param 构造函数名
	* @return 无
	*/
	void	SetDeconstructFunc(ResourceDeconstructFunc funcDeconstructResource);

private:
	class	Impl;
	Impl*	m_pImpl;

public:
	GameResourceManager();
	~GameResourceManager();
};

#endif // !_GAME_SOURCE_POOL_H_