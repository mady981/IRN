#include "Entity.h"
#include <assert.h>

Entity::Entity( const Vec2f& pos,const Vec2f& vel,const float& maxHitPoints,const float& Speed,const float& JumpSpeed,
	const float& FallSpeedInc,const float& Damage,Surface* pSprite,Map& map )
	:
	pos( pos ),
	vel( vel ),
	maxHitPoints( maxHitPoints ),
	Speed( Speed ),
	JumpSpeed( JumpSpeed ),
	FallSpeedInc( FallSpeedInc ),
	Damage( Damage ),
	currFallSpeed( 0.0f ),
	currJumpSpeed( 0.0f ),
	hitpoints( maxHitPoints ),
	pSprite( pSprite ),
	map( map ),
	width( pSprite->getWidth() ),
	height( pSprite-> getHeight() ),
	facing( { 0,0 } )
{
}

Entity::~Entity()
{
	delete pSprite;
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

void Entity::Tick( const float& dt )
{
	Update( dt );
	Jump( dt );
	Physik( dt );
}

void Entity::TakeDamage( const float& damagetaken )
{
	assert( damagetaken >= 0.0f );
	hitpoints > 0 ? hitpoints -= damagetaken : hitpoints = 0;
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
		pos.x * ( float )map.TileSprite()->getWidth() - width / 2.0f,
		pos.x * ( float )map.TileSprite()->getWidth() + width / 2.0f,
		pos.y * ( float )map.TileSprite()->getHeight() - height,
		pos.y * ( float )map.TileSprite()->getHeight()
	);
}

Surface* Entity::Sprite() const
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
