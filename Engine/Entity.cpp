#include "Entity.h"
#include <assert.h>
#include "WorldObject.h"

Entity::Entity( const Vec2f& pos,const Vec2f& vel,int maxHitPoints,float Speed,float JumpSpeed,
	float FallSpeedInc,int Damage,float InvincibleTime,Surface* pSprite )
	:
	pos( pos ),
	vel( vel ),
	maxHitPoints( maxHitPoints ),
	Speed( Speed ),
	JumpSpeed( JumpSpeed ),
	FallSpeedInc( FallSpeedInc ),
	Damage( Damage ),
	HitPoints( maxHitPoints ),
	pSprite( pSprite ),
	width( pSprite->getWidth() ),
	height( pSprite-> getHeight() ),
	InvincibleTime( InvincibleTime )
{
	
}

void Entity::Tick( float dt,WorldObject& world )
{
	Update( dt );
	Jump( dt );
	Physik( dt,world );
	Invincible( dt );
}

void Entity::TakeDamage( int damagetaken )
{
	assert( damagetaken >= 0.0f );
	if ( !isInvincible )
	{
		HitPoints > 0 ? HitPoints -= damagetaken : HitPoints = 0;
		isInvincible = true;
	}
}

void Entity::setDir( const Vec2f& dir,bool jump,WorldObject& world )
{
	vel = dir * Speed;
	if ( dir != Vec2f{ 0,0 } )
	{
		facing = (int)dir.x;
	}
	if ( world.getMap()->CollidingWith( pos.getRound(),HitBox() ) )
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

Vec2f Entity::getPos() const
{
	return pos;
}

RecF Entity::HitBox() const
{
	return RecF(
		pos.x * ( float )Map::Dimantion() - width / 2.0f,
		pos.x * ( float )Map::Dimantion() + width / 2.0f,
		pos.y * ( float )Map::Dimantion() - height,
		pos.y * ( float )Map::Dimantion()
	);
}

const Surface* Entity::Sprite() const
{
	return pSprite;
}

int Entity::getHitPoits() const
{
	return HitPoints;
}

bool Entity::isAlive() const
{
	if ( HitPoints <= 0 )
	{
		return false;
	}
	return true;
}

int Entity::Facing() const
{
	return facing;
}

void Entity::Update( float dt )
{
	pos += vel * dt;
}

void Entity::Jump( float dt )
{
	pos.y -= currJumpSpeed * dt;
}

void Entity::Physik( float dt,WorldObject& world )
{
	if ( !world.getMap()->CollidingWith( pos.getRound(),HitBox() ) )
	{
		pos.y += currFallSpeed * dt;
		currFallSpeed += FallSpeedInc * dt;
	}
	else
	{
		currFallSpeed = 0.0f;
	}
}

void Entity::Invincible( float dt )
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
