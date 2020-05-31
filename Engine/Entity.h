#pragma once
#include "Vec2.h"
#include "Rec.h"
#include "Surface.h"
#include "Map.h"

class Entity
{
public:
	Entity( const Vec2f& pos,const Vec2f& vel,int maxHitPoints,float Speed,float JumpSpeed,
		float FallSpeedInc,int Damage,float InvincibleTime,Surface* pSprite,Map& map );
	virtual ~Entity() = default;
	virtual void Tick( float dt );
	virtual void TakeDamage( int damage );
	virtual void Draw( const Vec2f& cPos,Graphics& gfx ) const = 0;
protected:
	virtual void setDir( const Vec2f& dir,bool jump );
	virtual void DealDamage( Entity& target ) const;
public:
	Vec2f Pos() const;
	RecF HitBox() const;
	const Surface* Sprite() const;
	int HitPoints() const;
	bool isAlive() const;
	virtual int Facing() const;
protected:
	void Update( float dt );
	void Jump( float dt );
	void Physik( float dt );
	void Invincible( float dt );
protected:
	Vec2f pos;
	Vec2f vel;
	int facing = 1;
	int maxHitPoints;
	const float Speed;
	const float JumpSpeed;
	const float FallSpeedInc;
	const int Damage;
	float currFallSpeed = 0.0f;
	float currJumpSpeed = 0.0f;
	int hitpoints;
	const int width;
	const int height;
	const float InvincibleTime;
	float curriTime = 0.0f;
	bool isInvincible = false;
protected:
	const Surface* pSprite;
	Map& map;
};