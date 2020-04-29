#include "Player.h"
#include <assert.h>
#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

Player::Player( const Vec2f& pos,Map& map )
	:
	map( map ),
	pos( pos )
{
}

Player::~Player()
{
	delete pSprite;
}

void Player::setDir( const Vec2f& dir,const bool jump )
{
	vel = dir * speed;
	if ( map.CollidingWith( pos.getRound(),HitBox() ) )
	{
		jvel = 0;
		if ( dir.y > 0 )
		{
			vel.y = 0;
		}
	}
	if ( jump )
	{
		jvel = jumpspeed;
	}
}

void Player::Tick( const float& dt )
{
	Update( dt );
	Jump( dt );
	Physiks( dt );
}

void Player::PlDamage( const float damage )
{
	//assert( currhp > 0 );
	assert( damage >= 0 );
	currhp -= damage;
	if ( currhp <= 0.0f )
	{
		isAlive = false;
	}
}

RecF Player::HitBox() const
{
	return RecF(
		pos.x * map.TileSprite()->getWidth() - pSprite->getWidth() / 2,
		pos.x * map.TileSprite()->getWidth() + pSprite->getWidth() / 2,
		pos.y * map.TileSprite()->getHeight() - pSprite->getHeight(),
		pos.y * map.TileSprite()->getHeight()
	);
}

Vec2f Player::Pos() const
{
	return Vec2f( pos );
}

Surface* Player::Sprite() const
{
	return pSprite;
}

float Player::Health() const
{
	return currhp;
}

void Player::Update( const float dt )
{
	pos += vel * dt;
	//DBOUT( pos.x );
	//DBOUT( "  " );
	//DBOUT( pos.y );
	//DBOUT( "\n" );
	//if ( oldy > pos.y )
	//{
	//	DBOUT( pos.y );
	//	DBOUT( "\n" );
	//	oldy = pos.y;
	//}
}

void Player::Jump( const float dt )
{
	pos.y -= jvel * dt;
}

void Player::Physiks( const float dt )
{
	if ( map.CollidingWith( pos.getRound(),HitBox() ) )
	{
		currfvel = 0.0f;
	}
	else
	{
		pos.y += currfvel * dt;
		currfvel += fvelinc * dt;
	}
}
