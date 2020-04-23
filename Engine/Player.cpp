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
	pos( pos / ( float )map.getTileDimantion() )
{
}

void Player::setDir( const Vec2f& dir,const bool jump )
{
	vel = dir * speed;
	if ( map.Collishion( pos.getRound(),PlayerHitBox() ) )
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

void Player::Draw( Graphics& gfx ) const
{
	gfx.DrawRecDimClip(
		Vec2f( gfx.ScreenWidth / 2 - PlayerHitBox().getWidth() / 2,gfx.ScreenHeight / 2 - PlayerHitBox().getHeight() ),
		( int )PlayerHitBox().getWidth(),
		( int )PlayerHitBox().getHeight(),
		Colors::Blue
	);
}

void Player::Tick( const float& dt )
{
	Update( dt );
	Jump( dt );
	Physiks( dt );
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

	if ( map.Collishion( pos.getRound(),PlayerHitBox() ) )
	{
		currfvel = 0.0f;
	}
	else
	{
		pos.y += currfvel * dt;
		currfvel += fvelinc * dt;
	}
}

RecF Player::PlayerHitBox() const
{
	return RecF(
		pos.x * ( float )map.getTileDimantion() - PlayerWidth / 2,
		pos.x * ( float )map.getTileDimantion() + PlayerWidth / 2,
		pos.y * ( float )map.getTileDimantion() - PlayerHeight,
		pos.y * ( float )map.getTileDimantion()
	);
}

Vec2f Player::PlayerPos() const
{
	return Vec2f( pos * ( float )map.getTileDimantion() );
}
