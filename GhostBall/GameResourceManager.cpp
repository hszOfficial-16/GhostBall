#include "GameResourceManager.h"

#include <unordered_map>

template<typename ResourceType>
class GameResourceManager<ResourceType>::Impl
{
public:
	std::unordered_map<std::wstring, ResourceType*> m_mapResources;
};

template<typename ResourceType>
void GameResourceManager<ResourceType>::Register(std::wstring strFileName, ResourceType* pResource)
{
	m_pImpl->m_mapResources[strFileName] = pResource;
}

template<typename ResourceType>
ResourceType* GameResourceManager<ResourceType>::Get(std::wstring strFileName)
{
	return m_pImpl->m_mapResources[strFileName];
}

template<typename ResourceType>
GameResourceManager<ResourceType>::GameResourceManager()
{
	m_pImpl = new Impl();
}

template<typename ResourceType>
GameResourceManager<ResourceType>::~GameResourceManager()
{
	delete m_pImpl;
}