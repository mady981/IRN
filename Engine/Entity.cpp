#include "Entity.h"

Entity::Entity( const Vec2f& pos,const Vec2f& vel,const float health,const float speed,const float jumpvel,
	const float fallvelinc,const int width,const int height,const Surface& sprite,Map& map )
	:
	ePos( pos / ( float )map.getTileDimantion() ),
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
	if ( map.Collishion( ePos.getRound(),EntityHitBox() ) )
	{
		eCurrCumpVel = 0;
		if ( dir.y > 0 )
		{
			eVel.y = 0;
		}
		if ( jump )
		{
			eCurrCumpVel = eJumpVel;
		}
	}
}

void Entity::Draw( const Vec2i& scrPos,Graphics& gfx ) const
{
	gfx.DrawRecDimClip( ePos * ( float )map.getTileDimantion - scrPos,eWidth,eHeight,Colors::Red );
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
	if ( map.Collishion( ePos.getRound(),EntityHitBox() ) )
	{
		ePos.y -= eCurrFallVel * dt;
		eCurrFallVel += eFallVelInc * dt;
	}
	else
	{
		eCurrFallVel = 0;
	}
}

RecF Entity::EntityHitBox() const
{
	return RecF(
		ePos.x * ( float )map.getTileDimantion() - eWidth / 2,
		ePos.x * ( float )map.getTileDimantion() + eWidth / 2,
		ePos.y * ( float )map.getTileDimantion() - eHealth,
		ePos.y * ( float )map.getTileDimantion()
		);
}
