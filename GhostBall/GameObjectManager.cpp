#include "GameObjectManager.h"

class GameObjectManager::Impl
{
public:
	size_t nObjectSize;
	size_t nChunkSize;

public:
	Impl()
	{
		nObjectSize = 0;
		nChunkSize = 16;
	}
	~Impl()
	{

	}
};

GameObjectManager::GameObjectManager(size_t nObjectSize, size_t nChunkSize)
{
	m_pImpl = new Impl();
	m_pImpl->nObjectSize = nObjectSize;
	m_pImpl->nChunkSize = nChunkSize;
}

GameObjectManager::~GameObjectManager()
{
	delete m_pImpl;
}