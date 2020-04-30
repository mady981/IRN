#pragma once
#include "Vec2.h"
#include "Rec.h"
#include "Surface.h"
#include "Map.h"

class Entity
{
public:
	Entity( const Vec2f& pos,const Vec2f& vel,const float& maxHitPoints,const float& Speed,const float& JumpSpeed,
		const float& FallSpeedInc,const float& Damage,Surface* pSprite,Map& map );
	virtual ~Entity();
	virtual void setDir( const Vec2f& dir,const bool& jump );
	virtual void Tick( const float& dt );
	void TakeDamage( const float& damage );
	void DealDamage( Entity& target ) const;
public:
	Vec2f Pos() const;
	RecF HitBox() const;
	Surface* Sprite() const;
	float HitPoints() const;
	bool isAlive() const;
protected:
	void Update( const float& dt );
	void Jump( const float& dt );
	void Physik( const float& dt );
protected:
	Vec2f pos;
	Vec2f vel;
	float maxHitPoints;
	const float Speed;
	const float JumpSpeed;
	const float FallSpeedInc;
	const float Damage;
	float currFallSpeed;
	float currJumpSpeed;
	float hitpoints;
	const int width;
	const int height;
protected:
	Surface* pSprite;
	Map& map;
};