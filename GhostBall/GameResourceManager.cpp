#include "GameResourceManager.h"

#include "GameUtils.h"

#include <filesystem>
#include <unordered_map>

class GameResourceManager::Impl
{
public:
	std::unordered_map<std::string, void*>	m_mapResource;
	ResourceConstructFunc					m_funcConstructResource;
	ResourceDeconstructFunc					m_funcDeconstructResource;

public:
	Impl()
	{
		m_funcConstructResource = nullptr;
		m_funcDeconstructResource = nullptr;
	}
	~Impl()
	{
		for (auto iter = m_mapResource.begin(); iter != m_mapResource.end(); iter++)
		{
			if (m_funcDeconstructResource)
			{
				m_funcDeconstructResource((*iter).second);
			}
			delete (*iter).second;
		}
	}
};

bool GameResourceManager::LoadFromFilter(std::string strFilterPath)
{
	using namespace std::filesystem;

	if (!m_pImpl->m_funcConstructResource)
	{
		return false;
	}

	path pathLoading(strFilterPath);
	if (!exists(pathLoading))
	{
		return false;
	}

	directory_entry entryDirectory(pathLoading);
	if (entryDirectory.status().type() != file_type::directory)
	{
		return false;
	}

	directory_iterator listFile(entryDirectory);
	for (auto& iter : listFile)
	{
		void* pResource = m_pImpl->m_funcConstructResource(GameUtils::WString2String(iter.path()));
		std::string strFileName = GameUtils::WString2String(iter.path().filename());
		m_pImpl->m_mapResource[strFileName] = pResource;
	}

	return true;
}

bool GameResourceManager::LoadFromPack(std::string strPackName)
{
	using namespace std::filesystem;
}

void GameResourceManager::SetConstructFunc(ResourceConstructFunc funcConstructResource)
{
	m_pImpl->m_funcConstructResource = funcConstructResource;
}

void GameResourceManager::SetDeconstructFunc(ResourceDeconstructFunc funcDeconstructResource)
{
	m_pImpl->m_funcDeconstructResource = funcDeconstructResource;
}

void* GameResourceManager::Get(std::string strFileName)
{
	return m_pImpl->m_mapResource[strFileName];
}

void GameResourceManager::ClearAllResource()
{
	for (auto iter = m_pImpl->m_mapResource.begin(); iter != m_pImpl->m_mapResource.end(); iter++)
	{
		if (m_pImpl->m_funcDeconstructResource)
		{
			m_pImpl->m_funcDeconstructResource((*iter).second);
			delete (*iter).second;
		}
	}
}

GameResourceManager::GameResourceManager()
{
	m_pImpl = new Impl();
}

GameResourceManager::~GameResourceManager()
{
	delete m_pImpl;
}