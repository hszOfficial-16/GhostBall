#ifndef _GAME_OBJECT_POOL_H_
#define _GAME_OBJECT_POOL_H_

class GameObjectPool
{
public:
	void*	Malloc();
	void	Free(void* pObject);

private:
	class	Impl;
	Impl*	m_pImpl;

public:
	GameObjectPool();
	~GameObjectPool();
};

#endif // !_GAME_OBJECT_POOL_H_