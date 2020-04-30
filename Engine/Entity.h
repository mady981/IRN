#pragma once
#include "Vec2.h"
#include "Rec.h"
#include "Map.h"

class Entity
{
public:
	Entity( const Vec2f& pos,const Vec2f& vel,const float& maxHitPoints,const float& Speed,const float& JumpSpeed,
		const float& FallSpeedInc,const float& Damage,const int& width,const int& height,Map& map );
	virtual ~Entity() = 0;
	void setDir( const Vec2f& dir,const bool& jump );
	void Tick( const float& dt );
	void TakeDamage( const float& damage );
	void DealDamage( Entity& target ) const;
public:
	Vec2f Pos() const;
	RecF HitBox() const;
	bool isAlive() const;
protected:
	void Update( const float& dt );
	void Jump( const float& dt );
	void Physik( const float& dt );
protected:
	Vec2f pos;
	Vec2f vel;
	const float maxHitPoints;
	const float Speed;
	const float JumpSpeed;
	const float FallSpeedInc;
	const float Damage;
	float currFallSpeed;
	float currJumpSpeed;
	float HitPoints;
	const int width;
	const int height;
private:
	Map& map;
};