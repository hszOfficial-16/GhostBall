#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

/* 为对象分配内存并管理其生命周期
*/
class GameObjectManager
{
public:
	/* 为对象分配内存并调用构造函数
	* @param 无
	* @return 指向该对象的指针
	*/
	void*	Create();

	/* 调用析构函数并释放对象的内存
	* @param 由该内存管理对象管理的指针
	* @return 无
	*/
	void	Destroy(void* pObject);

private:
	class	Impl;
	Impl*	m_pImpl;

public:
	/* 构造一个对象管理者，负责管理定长对象的生命周期
	* @param nObjectSize: 对象大小 
	* nChunkSize: 单个区块可容纳对象数量(默认为 16)
	*/
	GameObjectManager(
		size_t nObjectSize,
		size_t nChunkSize = 16
	);

	~GameObjectManager();
};

#endif // !_GAME_OBJECT_MANAGER_H_