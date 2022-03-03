#include "GameSprite.h"

#include <SDL.h>
#include <vector>

class GameSprite::Impl
{
public:
	GamePoint			m_position;
	float					m_fAngle;
	GameFlip				m_emFlip;
	int						m_nZOrder;
	std::vector<GameImage*>	m_vImage;

	b2Body*					m_pBody;

public:
	Impl()
	{
		m_position = { 0.0f, 0.0f };
		m_fAngle = 0.0f;
		m_emFlip = GameFlip::NONE;
		m_nZOrder = 0;
		m_pBody = nullptr;
	}
};

GamePoint GameSprite::GetPosition()
{
	if (!m_pImpl->m_pBody)
	{
		return m_pImpl->m_position;
	}
	else
	{
		return 
		{ 
			m_pImpl->m_pBody->GetPosition().x,
			m_pImpl->m_pBody->GetPosition().y
		};
	}
}

const float& GameSprite::GetAngle()
{
	if (!m_pImpl->m_pBody)
	{
		return m_pImpl->m_fAngle;
	}
	else
	{
		return m_pImpl->m_pBody->GetAngle();
	}
}

const GameFlip& GameSprite::GetFlip()
{
	return m_pImpl->m_emFlip;
}

const int& GameSprite::GetZOrder()
{
	return m_pImpl->m_nZOrder;
}

void GameSprite::SetPosition(const GamePoint& position)
{
	if (!m_pImpl->m_pBody)
	{
		m_pImpl->m_position = position;
	}
	else
	{
		m_pImpl->m_pBody->SetTransform({ position.x, position.y }, m_pImpl->m_pBody->GetAngle());
	}
}

void GameSprite::SetAngle(const float& fAngle)
{
	if (!m_pImpl->m_pBody)
	{
		m_pImpl->m_fAngle = fAngle;
	}
	else
	{
		m_pImpl->m_pBody->SetTransform(m_pImpl->m_pBody->GetPosition(), fAngle);
	}
}

void GameSprite::SetFlip(const GameFlip& emFlip)
{
	m_pImpl->m_emFlip = emFlip;
}

void GameSprite::SetZOrder(const int& nZOrder)
{
	m_pImpl->m_nZOrder = nZOrder;
}

b2Body* GameSprite::GetBody()
{
	return m_pImpl->m_pBody;
}

GameSprite::GameSprite()
{
	m_pImpl = new Impl();
}

GameSprite::~GameSprite()
{
	delete m_pImpl;
}

class GameSpriteManager::Impl
{
	
};

GameSprite* GameSpriteManager::CreateSprite(const GamePoint& position, const float& fAngle, const int& nZOrder)
{
	GameSprite* pSprite = new GameSprite();
	pSprite->m_pImpl->m_position = position;
	pSprite->m_pImpl->m_fAngle = fAngle;
	pSprite->m_pImpl->m_nZOrder = nZOrder;

	return pSprite;
}

GameSprite* GameSpriteManager::CreateSpriteWithBody(b2World* pWorld, const b2BodyDef* pBodyDef, const int& nZOrder)
{	
	GameSprite* pSprite = new GameSprite();
	pSprite->m_pImpl->m_position = { pBodyDef->position.x, pBodyDef->position.y };
	pSprite->m_pImpl->m_fAngle = pBodyDef->angle;
	pSprite->m_pImpl->m_nZOrder = nZOrder;
	pSprite->m_pImpl->m_pBody = pWorld->CreateBody(pBodyDef);

	return pSprite;
}

b2Body* GameSpriteManager::CreateBodyOnSprite(GameSprite* pSprite, b2World* pWorld)
{
	b2BodyDef campBodyDef;
	campBodyDef.position = { pSprite->GetPosition().x, pSprite->GetPosition().y };
	campBodyDef.angle = pSprite->GetAngle();
	campBodyDef.userData.pointer = (uintptr_t)pSprite;

	pSprite->m_pImpl->m_pBody = pWorld->CreateBody(&campBodyDef);

	return pSprite->m_pImpl->m_pBody;
}

GameSpriteManager::GameSpriteManager()
{
	m_pImpl = new Impl();
}

GameSpriteManager::~GameSpriteManager()
{
	delete m_pImpl;
}