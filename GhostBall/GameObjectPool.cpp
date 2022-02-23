#include "GameObjectPool.h"

#include <vector>

template<typename ObjectType, size_t nBlockNum>
class GameObjectPool<ObjectType, nBlockNum>::Impl
{
public:
	struct MemoryChunk
	{
		ObjectType		blocks[nBlockNum];
		MemoryChunk*	pNext;
	};

	MemoryChunk*				m_pChunkHead;
	std::vector<ObjectType*>	m_vFreeBlocks;

public:
	Impl()
	{
		m_pChunkHead = nullptr;
		m_vFreeBlocks.resize(nBlockNum);
	}
};

template<typename ObjectType, size_t nBlockNum>
ObjectType* GameObjectPool<ObjectType, nBlockNum>::Malloc()
{
	if (m_pImpl->m_vFreeBlocks.empty())
	{
		typename Impl::MemoryChunk* pNewChunk = new Impl::MemoryChunk();
		for (int i = 0; i < nBlockNum; i++)
		{
			m_pImpl->m_vFreeBlocks.push_back(&m_pImpl->m_pChunkHead->blocks[i]);
		}

		if (!m_pImpl->m_pChunkHead)
		{
			m_pImpl->m_pChunkHead = pNewChunk;
		}
		else
		{
			pNewChunk->pNext = m_pImpl->m_pChunkHead;
			m_pImpl->m_pChunkHead = pNewChunk;
		}

		ObjectType* pObject = m_pImpl->m_vFreeBlocks[m_pImpl->m_vFreeBlocks.size() - 1];
		m_pImpl->m_vFreeBlocks.pop_back();

		return pObject;
	}
}

template<typename ObjectType, size_t nBlockNum>
void GameObjectPool<ObjectType, nBlockNum>::Free(ObjectType* pObject)
{
	m_pImpl->m_vFreeBlocks.push_back(pObject);
}

template<typename ObjectType, size_t nBlockNum>
GameObjectPool<ObjectType, nBlockNum>::GameObjectPool()
{
	m_pImpl = new Impl();
}

template<typename ObjectType, size_t nBlockNum>
GameObjectPool<ObjectType, nBlockNum>::~GameObjectPool()
{
	delete m_pImpl;
}