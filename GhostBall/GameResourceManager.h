#ifndef _GAME_SOURCE_POOL_H_
#define _GAME_SOURCE_POOL_H_

#include <string>
#include <functional>

class GameResourceManager
{
public:
	/* 读取文件夹下的所有文件读入内存，并根据用户提供的函数构造资源对象
	* @param 文件夹的相对路径
	* @return 是否读取成功
	*/
	bool	LoadFromFilter(std::string strFliterPath);
	
	/* 读取二进制包下的所有文件读取内存，并根据用户提供的函数构造资源对象
	* @param 二进制包的相对路径
	* @return 是否读取成功
	*/
	bool	LoadFromPack(std::string strPackName);

	/* 根据文件名获取内存中的资源对象指针
	* @param 资源文件的文件名
	* @return 资源对象指针
	*/
	void*	Get(std::string strFileName);

	/* 设置资源对象的构造函数
	* @param 构造函数名
	* @return 无
	*/
	void	SetConstructFunc(std::function<void* (std::string)> funcConstructResource);

	/* 设置资源对象的析构函数
	* @param 构造函数名
	* @return 无
	*/
	void	SetDeconstructFunc(std::function<void* (std::string)> funcDeconstructResource);

private:
	class	Impl;
	Impl*	m_pImpl;

public:
	GameResourceManager();
	~GameResourceManager();
};

#endif // !_GAME_SOURCE_POOL_H_