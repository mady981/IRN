#include "Entity.h"
#include <assert.h>

Entity::Entity( const Vec2f& pos,const Vec2f& vel,const float& maxHitPoints,const float& Speed,const float& JumpSpeed,
	const float& FallSpeedInc,const float& Damage,const float& InvincibleTime,Surface* pSprite,Map& map )
	:
	pos( pos ),
	vel( vel ),
	maxHitPoints( maxHitPoints ),
	Speed( Speed ),
	JumpSpeed( JumpSpeed ),
	FallSpeedInc( FallSpeedInc ),
	Damage( Damage ),
	hitpoints( maxHitPoints ),
	pSprite( pSprite ),
	map( map ),
	width( pSprite->getWidth() ),
	height( pSprite-> getHeight() ),
	InvincibleTime( InvincibleTime )
{
}

void Entity::Tick( const float& dt )
{
	Update( dt );
	Jump( dt );
	Physik( dt );
	Invincible( dt );
}

void Entity::TakeDamage( const float& damagetaken )
{
	assert( damagetaken >= 0.0f );
	if ( !isInvincible )
	{
		hitpoints > 0 ? hitpoints -= damagetaken : hitpoints = 0;
		isInvincible = true;
	}
}

void Entity::setDir( const Vec2f& dir,const bool& jump )
{
	vel = dir * Speed;
	if ( dir != Vec2f{ 0,0 } )
	{
		facing = dir;
	}
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
	return pSprite->getRect<float>();
}

const Surface* Entity::Sprite() const
{
	return pSprite;
}

float Entity::HitPoints() const
{
	return hitpoints;
}

bool Entity::isAlive() const
{
	if ( hitpoints <= 0 )
	{
		return false;
	}
	return true;
}

Vec2f Entity::Facing() const
{
	return Vec2f( facing );
}

void Entity::Update( const float& dt )
{
	pos += vel * dt;
}

void Entity::Jump( const float& dt )
{
	pos.y -= currJumpSpeed * dt;
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

void Entity::Invincible( const float& dt )
{
	if ( isInvincible )
	{
		curriTime += dt;
		while ( curriTime >= InvincibleTime )
		{
			curriTime -= InvincibleTime;
			isInvincible = false;
		}
	}
}
