#include "Player.h"
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
	if ( map.Collision( pos.getRound(),PlHitBox() ) )
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

RecF Player::PlHitBox() const
{
	return RecF(
		pos.x * map.TileSprite()->getWidht() - pSprite->getWidht() / 2,
		pos.x * map.TileSprite()->getWidht() + pSprite->getWidht() / 2,
		pos.y * map.TileSprite()->getHeight() - pSprite->getHeight(),
		pos.y * map.TileSprite()->getHeight()
	);
}

Vec2f Player::PlPos() const
{
	return Vec2f( pos );
}

Surface* Player::PlSprite() const
{
	return pSprite;
}

void Player::Update( const float dt )
{
	pos += vel * dt;
	DBOUT( pos.x );
	DBOUT( "  " );
	DBOUT( pos.y );
	DBOUT( "\n" );
}

void Player::Jump( const float dt )
{
	pos.y -= jvel * dt;
}

void Player::Physiks( const float dt )
{
	if ( map.Collision( pos.getRound(),PlHitBox() ) )
	{
		currfvel = 0.0f;
	}
	else
	{
		pos.y += currfvel * dt;
		currfvel += fvelinc * dt;
	}
}
