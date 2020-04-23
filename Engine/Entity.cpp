#include "Entity.h"

Entity::Entity( const Vec2f& pos,const Vec2f& vel,const float health,const float speed,const float jumpvel,
	const float fallvelinc,const int width,const int height,const Surface& sprite,Map& map )
	:
	ePos( pos / map.getTileDimantion() ),
	eVel( vel ),
	eHealth( health ),
	eSpeed( speed ),
	eJumpVel( jumpvel ),
	eFallVelInc( fallvelinc ),
	eWidth( width ),
	eHeight( height ),
	eSprite( sprite ),
	map( map )
{
}

void Entity::setDir( const Vec2f& dir,const bool jump )
{
	eVel = dir * eSpeed;
}

void Entity::Draw( Graphics& gfx ) const
{
	// draw entity
}

void Entity::Tick( const float dt )
{
	Update( dt );
	Jump( dt );
	Physiks( dt );
}

void Entity::Update( const float dt )
{
	ePos += eVel * dt;
}

void Entity::Jump( const float dt )
{
	ePos.y -= eJumpVel * dt;
}

void Entity::Physiks( const float dt )
{
	ePos.y -= eCurrFallVel * dt;
	eCurrFallVel += eFallVelInc * dt;
}

RecI Entity::EntityHitBox() const
{
	return RecI(
		ePos.x * ( float )map.getTileDimantion() - eWidth / 2,
		ePos.x * ( float )map.getTileDimantion() + eWidth / 2,
		ePos.y * ( float )map.getTileDimantion() - eHealth,
		ePos.y * ( float )map.getTileDimantion()
		);
}
