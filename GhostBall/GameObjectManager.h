#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

class GameObjectManager
{
public:


private:
	class Impl;
	Impl* m_pImpl;

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