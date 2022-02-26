#include "GameObjectPool.h"

#include <vector>

class GameObjectPool::Impl
{
public:

public:

};

GameObjectPool::GameObjectPool()
{
	m_pImpl = new Impl();
}

GameObjectPool::~GameObjectPool()
{
	delete m_pImpl;
}