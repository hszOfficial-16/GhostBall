#ifndef _GAME_OBJECT_POOL_H_
#define _GAME_OBJECT_POOL_H_

template<typename ObjectType, size_t nBlockNum = 16>
class GameObjectPool
{
public:
	ObjectType*		Malloc();
	void			Free(ObjectType* pObject);

private:
	class Impl;
	Impl* m_pImpl;

public:
	GameObjectPool();
	~GameObjectPool();
};

#endif // !_GAME_OBJECT_POOL_H_