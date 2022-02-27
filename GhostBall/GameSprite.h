#ifndef _GAME_SPRITE_H_
#define _GAME_SPRITE_H_

#include "GameGraphic.h"

#include <box2d.h>

class GameSprite
{
public:
	GamePosition		GetPosition();
	const float&		GetAngle();
	const GameFlip&		GetFlip();
	const int&			GetZOrder();

	void				SetPosition(const GamePosition& position);
	void				SetAngle(const float& fAngle);
	void				SetFlip(const GameFlip& emFlip);
	void				SetZOrder(const int& nZOrder);

	b2Body*				GetBody();

private:
	class				Impl;
	Impl*				m_pImpl;

private:
	GameSprite();
	~GameSprite();

	friend class GameSpriteManager;
};

class GameSpriteManager
{
public:
	GameSprite* CreateSprite(const GamePosition& position = { 0.0f, 0.0f }, const float& fAngle = 0.0f, const int& nZOrder = 0);
	GameSprite* CreateSpriteWithBody(b2World* pWorld, const b2BodyDef* pBodyDef, const int& nZOrder);
	b2Body*		CreateBodyOnSprite(GameSprite* pSprite, b2World* pWorld);

private:
	class Impl;
	Impl* m_pImpl;

public:
	~GameSpriteManager();
	GameSpriteManager(const GameSpriteManager&) = delete;
	GameSpriteManager& operator=(const GameSpriteManager&) = delete;
	static GameSpriteManager& GetInstance()
	{
		static GameSpriteManager instance;
		return instance;
	}
private:
	GameSpriteManager();
};

#endif // !_GAME_SPRITE_H_