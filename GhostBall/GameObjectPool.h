#ifndef _GAME_OBJECT_POOL_H_
#define _GAME_OBJECT_POOL_H_

template<typename ObjectType, size_t nBlockNum = 16>
class GameObjectPool
{
public:
	virtual ObjectType*	Malloc();
	virtual void		Free(ObjectType* pObject);

private:
	class				Impl;
	Impl*				m_pImpl;

public:
	GameObjectPool();
	virtual ~GameObjectPool();
};

#endif // !_GAME_OBJECT_POOL_H_