#include "Enemy.h"
#include <assert.h>

Enemy::Enemy( const Vec2f& pos,Map& map,const float& TrackDist,const float& inRange,const int& AttackWidth,const int& AttackHeight )
	:
	Entity( pos,{ 0,0 },100,4.0f,20.0f,45.0f,10,1.0f,SurfaceCodex::Retrieve( L"Player.bmp" ),map ),
	TrackDistSq( TrackDist * TrackDist ),
	inRangeSq( inRange * inRange ),
	AttackWidth( AttackWidth ),
	AttackHeight( AttackHeight ),
	facing( { 1,0 } )
{
}

void Enemy::AI( Entity& target )
{
	assert( &target != this );
	Vec2f dir = Vec2f( target.Pos() - pos );
	facing.x = dir.x;
	facing.SetOne();
	float distsq = dir.getLengthSq();
	if ( distsq < TrackDistSq && distsq > inRangeSq )
	{
		setDir( dir.getSetOne(),false );
	}
	else
	{
		setDir( { 0,0 },false );
	}
	if ( AttackHB().isOverlappingWith( target.HitBox() ) )
	{
		target.TakeDamage( Damage );
	}
}

void Enemy::Draw( const Vec2f& pos_c,Graphics& gfx ) const
{
	const Vec2f offset = pos - pos_c;
	gfx.DrawSpriteOverColor(
		int( offset.x * map.TileSprite()->getWidth() - pSprite->getWidth() / 2 + gfx.ScreenWidth / 2 ),
		int( offset.y * map.TileSprite()->getHeight() - pSprite->getHeight() + gfx.ScreenHeight / 2 ),
		*pSprite,
		Colors::Red,
		facing.y < 0
	);
}

RecF Enemy::AttackHB() const
{
	RecF AHB(
		pos.x * ( float )map.TileSprite()->getWidth(),
		pos.x * ( float )map.TileSprite()->getWidth() + ( float )( AttackWidth * ( int )facing.x ),
		pos.y * ( float )map.TileSprite()->getHeight() - ( float )AttackHeight,
		pos.y * ( float )map.TileSprite()->getHeight()
	);
	if ( AHB.left > AHB.right )
	{
		std::swap( AHB.left,AHB.right );
	}
	return AHB;
}
