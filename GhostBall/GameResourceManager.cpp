#include "GameResourceManager.h"

#include "GameUtils.h"

#include <filesystem>
#include <unordered_map>

class GameResourceManager::Impl
{
public:
	std::unordered_map<std::string, void*>	m_mapResource;
	std::function<void* (std::string)>		m_funcCreateResource;

public:
	Impl()
	{
		m_funcCreateResource = nullptr;
	}
};

bool GameResourceManager::LoadFromFilter(std::string strFilterPath)
{
	using namespace std::filesystem;

	if (!m_pImpl->m_funcCreateResource)
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
		void* pResource = m_pImpl->m_funcCreateResource(GameUtils::WString2String(iter.path().filename()));
		std::string strFileName = GameUtils::WString2String(iter.path().filename());
		m_pImpl->m_mapResource[strFileName] = pResource;
	}

	return true;
}

bool GameResourceManager::LoadFromPack(std::string strPackName)
{
	using namespace std::filesystem;
}

void GameResourceManager::SetCreateFunc(std::function<void* (std::string)> funcCreateResource)
{
	m_pImpl->m_funcCreateResource = funcCreateResource;
}

void* GameResourceManager::Get(std::string strFileName)
{
	return m_pImpl->m_mapResource[strFileName];
}

GameResourceManager::GameResourceManager()
{
	m_pImpl = new Impl();
}

GameResourceManager::~GameResourceManager()
{
	delete m_pImpl;
}