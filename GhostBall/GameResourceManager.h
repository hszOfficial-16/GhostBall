#ifndef _GAME_SOURCE_POOL_H_
#define _GAME_SOURCE_POOL_H_

#include <string>

template<typename ResourceType>
class GameResourceManager
{
protected:
	void			Register(std::wstring strFile, ResourceType* pResource);
	ResourceType*	Get(std::wstring strFile);

private:
	class			Impl;
	Impl			m_pImpl;

public:
	virtual ~GameResourceManager() = default;
	GameResourceManager(const GameResourceManager&) = delete;
	GameResourceManager& operator=(const GameResourceManager&) = delete;
	static GameResourceManager& GetInstance()
	{
		static GameResourceManager instance;
		return instance;
	}
private:
	GameResourceManager() = default;
};

#endif // !_GAME_SOURCE_POOL_H_