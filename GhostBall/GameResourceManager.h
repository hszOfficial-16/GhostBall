#ifndef _GAME_SOURCE_POOL_H_
#define _GAME_SOURCE_POOL_H_

#include <string>

template<typename ResourceType>
class GameResourceManager
{
public:
	virtual ResourceType*	Get(std::string strFile);
	virtual void			Register(std::string strFileName, ResourceType* pResource);

private:
	class					Impl;
	Impl*					m_pImpl;

public:
	virtual ~GameResourceManager();
	GameResourceManager(const GameResourceManager&) = delete;
	GameResourceManager& operator=(const GameResourceManager&) = delete;
protected:
	GameResourceManager();
};

#endif // !_GAME_SOURCE_POOL_H_