#pragma once
#include "Vec2.h"
#include "Rec.h"
#include "Surface.h"
#include "Map.h"

class Entity
{
public:
	Entity( const Vec2f& pos,const Vec2f& vel,const float& maxHitPoints,const float& Speed,const float& JumpSpeed,
		const float& FallSpeedInc,const float& Damage,const float& InvincibleTime,Surface* pSprite,Map& map );
	virtual ~Entity();
	virtual void Tick( const float& dt );
	virtual void TakeDamage( const float& damage );
	virtual void Draw( const Vec2f& cPos,Graphics& gfx ) const = 0;
protected:
	virtual void setDir( const Vec2f& dir,const bool& jump );
	virtual void DealDamage( Entity& target ) const;
public:
	Vec2f Pos() const;
	RecF HitBox() const;
	Surface* Sprite() const;
	float HitPoints() const;
	bool isAlive() const;
	virtual Vec2f Facing() const;
protected:
	void Update( const float& dt );
	void Jump( const float& dt );
	void Physik( const float& dt );
	void Invincible( const float& dt );
protected:
	Vec2f pos;
	Vec2f vel;
	Vec2f facing = { 0.0f,0.0f };
	float maxHitPoints;
	const float Speed;
	const float JumpSpeed;
	const float FallSpeedInc;
	const float Damage;
	float currFallSpeed = 0.0f;
	float currJumpSpeed = 0.0f;
	float hitpoints;
	const int width;
	const int height;
	const float InvincibleTime;
	float curriTime = 0.0f;
	bool isInvincible = false;
protected:
	Surface* pSprite;
	Map& map;
};