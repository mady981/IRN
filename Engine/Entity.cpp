#include "Entity.h"

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
	HitPoints( maxHitPoints ),
	map( map )
{
}

void Entity::setDir( const Vec2f& dir )
{
	vel = dir * Speed;
}

void Entity::Tick( const float& dt )
{
	Update( dt );
	Jump( dt );
	Physik( dt );
}

void Entity::TakeDamage( const float& damagetaken )
{
	HitPoints -= damagetaken;
}

void Entity::DealDamage( Entity& target ) const
{
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
