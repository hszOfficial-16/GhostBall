#include "GameResourceManager.h"

#include <filesystem>
#include <unordered_map>

template<typename ResourceType>
class GameResourceManager<ResourceType>::Impl
{
public:
	std::unordered_map<std::string, ResourceType*> m_mapResource;
};

template<typename ResourceType>
void GameResourceManager<ResourceType>::Register(std::string strFileName, ResourceType* pResource)
{
	m_pImpl->m_mapResource[strFileName] = pResource;
}

template<typename ResourceType>
ResourceType* GameResourceManager<ResourceType>::Get(std::string strFileName)
{
	return m_pImpl->m_mapResource[strFileName];
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