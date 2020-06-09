#include "Enemy.h"
#include <assert.h>
#include "SpriteEffect.h"
#include "MorMath.h"
#include "WorldObject.h"

Enemy::Enemy( const Vec2f& pos )
	:
	Entity( pos,{ 0,0 },100,4.0f,20.0f,45.0f,10,1.0f,SurfaceCodex::Retrieve( L"Player.bmp" ) )
{
}

void Enemy::AI( Entity* target,WorldObject& world )
{
	assert( target );
	assert( target != this );
	Vec2f dir = Vec2f( target->getPos() - pos );
	facing = ( int )MorMath::one( dir.x );
	float distsq = dir.getLengthSq();
	if ( distsq < TrackDistSq && distsq > inRangeSq )
	{
		setDir( dir.getSetOne(),false,world );
	}
	else
	{
		setDir( { 0,0 },false,world );
	}
	if ( AttackHB().isOverlappingWith( target->HitBox() ) )
	{
		target->TakeDamage( Damage );
	}
}

void Enemy::Draw( const Vec2f& pos_c,Graphics& gfx ) const
{
	const Vec2f offset = pos - pos_c;
	gfx.DrawSprite(
		Vec2_{ int( offset.x * Map::Dimantion() - pSprite->getWidth() / 2 + gfx.ScreenWidth / 2 ),
		int( offset.y * Map::Dimantion() - pSprite->getHeight() + gfx.ScreenHeight / 2 ) },
		*pSprite,
		facing < 0,
		SpriteEffect::Substitution( Colors::Red )
	);
}

RecF Enemy::AttackHB() const
{
	RecF AHB(
		pos.x * ( float )Map::Dimantion(),
		pos.x * ( float )Map::Dimantion() + ( float )( AttackWidth * ( int )facing ),
		pos.y * ( float )Map::Dimantion() - ( float )AttackHeight,
		pos.y * ( float )Map::Dimantion()
	);
	if ( AHB.left > AHB.right )
	{
		std::swap( AHB.left,AHB.right );
	}
	return AHB;
}
