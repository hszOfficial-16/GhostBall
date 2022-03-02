#include "GameObjectManager.h"

#include <vector>

class GameObjectManager::Impl
{
public:
	struct MemoryChunk
	{
		uintptr_t arrData;
		MemoryChunk* pNext;
	};
	MemoryChunk* m_pChunkHead;

	size_t m_nObjectSize;
	size_t m_nChunkSize;

	std::function<void(void*)> m_funcConstructor;
	std::function<void(void*)> m_funcDeconstructor;

	std::vector<void*> m_vFreeBlock;

public:
	Impl()
	{
		m_nObjectSize = 0;
		m_nChunkSize = 16;

		m_funcConstructor = nullptr;
		m_funcDeconstructor = nullptr;

		m_pChunkHead = nullptr;
	}
	~Impl()
	{
		while (m_pChunkHead)
		{
			delete[] (unsigned char*)m_pChunkHead->arrData;
			delete m_pChunkHead;
			m_pChunkHead = m_pChunkHead->pNext;
		}
	}
};

void* GameObjectManager::Create()
{
	if (m_pImpl->m_vFreeBlock.empty())
	{
		Impl::MemoryChunk* pNewChunk = new Impl::MemoryChunk();
		pNewChunk->arrData = (uintptr_t)new unsigned char[m_pImpl->m_nObjectSize * m_pImpl->m_nChunkSize];

		// 将新区块的空闲内存全部压入栈内
		for (int i = 0; i < m_pImpl->m_nChunkSize; i++)
		{
			m_pImpl->m_vFreeBlock.push_back((void*)(pNewChunk->arrData + i * m_pImpl->m_nObjectSize));
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
	}

	void* pObject = (void*)(*m_pImpl->m_vFreeBlock.end());
	m_pImpl->m_vFreeBlock.pop_back();
	m_pImpl->m_funcConstructor(pObject);

	return pObject;
}

void GameObjectManager::Destroy(void* pObject)
{
	m_pImpl->m_funcDeconstructor(pObject);
	m_pImpl->m_vFreeBlock.push_back(pObject);
}

void GameObjectManager::SetConstructFunc(std::function<void(void*)> funcConstructor)
{
	m_pImpl->m_funcConstructor = funcConstructor;
}

void GameObjectManager::SetDeconstructFunc(std::function<void(void*)> funcDeconstructor)
{
	m_pImpl->m_funcDeconstructor = funcDeconstructor;
}

GameObjectManager::GameObjectManager(size_t nObjectSize, size_t nChunkSize)
{
	m_pImpl = new Impl();
	m_pImpl->m_nObjectSize = nObjectSize;
	m_pImpl->m_nChunkSize = nChunkSize;
}

GameObjectManager::~GameObjectManager()
{
	delete m_pImpl;
}