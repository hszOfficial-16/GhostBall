#ifndef _GAME_SOURCE_POOL_H_
#define _GAME_SOURCE_POOL_H_

#include <string>
#include <functional>

class GameResourceManager
{
public:
	bool	LoadFromFilter(std::string strFliterPath);
	bool	LoadFromPack(std::string strPackName);

	void*	Get(std::string strFileName);
	void	SetCreateFunc(std::function<void* (std::string)> funcCreateResource);

private:
	class	Impl;
	Impl*	m_pImpl;

public:
	GameResourceManager();
	~GameResourceManager();
};

#endif // !_GAME_SOURCE_POOL_H_