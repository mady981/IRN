#include "Entity.h"
#include <assert.h>

Entity::Entity( const Vec2f& pos,const Vec2f& vel,const float& maxHitPoints,const float& Speed,const float& JumpSpeed,
	const float& FallSpeedInc,const float& Damage,const int& width,const int& height,Map& map )
	:
	pos( pos ),
	vel( vel ),
	maxHitPoints( maxHitPoints ),
	Speed( Speed ),
	JumpSpeed( JumpSpeed ),
	FallSpeedInc( FallSpeedInc ),
	Damage( Damage ),
	width( width ),
	height( height ),
	currFallSpeed( 0.0f ),
	currJumpSpeed( 0.0f ),
	HitPoints( maxHitPoints ),
	map( map )
{
}

void Entity::setDir( const Vec2f& dir,const bool& jump )
{
	vel = dir * Speed;
	if ( map.CollidingWith( pos.getRound(),HitBox() ) )
	{
		currJumpSpeed = 0;
		if ( dir.y > 0 )
		{
			vel.y = 0;
		}
		if ( jump )
		{
			currJumpSpeed = JumpSpeed;
		}
	}
}

void Entity::Tick( const float& dt )
{
	Update( dt );
	Jump( dt );
	Physik( dt );
}

void Entity::TakeDamage( const float& damagetaken )
{
	assert( damagetaken >= 0.0f );
	HitPoints > 0 ? HitPoints -= damagetaken : HitPoints = 0;
}

void Entity::DealDamage( Entity& target ) const
{
	assert( &target != this );
	target.TakeDamage( Damage );
}

Vec2f Entity::Pos() const
{
	return pos;
}

RecF Entity::HitBox() const
{
	return RecF(
		pos.x - width / 2,
		pos.x + width / 2,
		pos.y - height,
		pos.y
	);
}

bool Entity::isAlive() const
{
	if ( HitPoints <= 0 )
	{
		return false;
	}
	return true;
}

void Entity::Update( const float& dt )
{
	pos += vel * dt;
}

void Entity::Jump( const float& dt )
{
	pos.y -= JumpSpeed * dt;
}

void Entity::Physik( const float& dt )
{
	if ( !map.CollidingWith( pos.getRound(),HitBox() ) )
	{
		pos.y += currFallSpeed * dt;
		currFallSpeed += FallSpeedInc * dt;
	}
	else
	{
		currFallSpeed = 0.0f;
	}
}
