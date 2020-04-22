#include "Player.h"
#include <iostream>
#include <sstream>

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

Player::Player( const Vec2f& pos )
	:
	pos( pos )
{
}

void Player::setDir( const Vec2f& dir,const bool jump )
{
	vel = dir * speed;
	if ( map.getMap().contains( ( Vec2i )pos / map.getTileDimantion() - Vec2i( 0,1 ) ) )
	{
		if ( map.getMap().find( ( Vec2i )pos / map.getTileDimantion() - Vec2i( 0,1 ) )->second->TileHitBox().isOverlappingWith( RecF{
				PlayerHitBox().left / ( float )map.getTileDimantion(),
				PlayerHitBox().right / ( float )map.getTileDimantion(),
				PlayerHitBox().top / ( float )map.getTileDimantion(),
				PlayerHitBox().bottem / ( float )map.getTileDimantion()
				} ) )
		{
			jvel = 0;
			if ( dir.y > 0 )
			{
				vel.y = 0;
			}
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

	if ( map.getMap().contains( ( Vec2i )pos / map.getTileDimantion() - Vec2i( 0,1 ) ) )
	{
		if ( map.getMap().find( ( Vec2i )pos / map.getTileDimantion() - Vec2i( 0,1 ) )->second->TileHitBox().isOverlappingWith( RecF{
				PlayerHitBox().left / ( float )map.getTileDimantion(),
				PlayerHitBox().right / ( float )map.getTileDimantion(),
				PlayerHitBox().top / ( float )map.getTileDimantion(),
				PlayerHitBox().bottem / ( float )map.getTileDimantion()
			} ) )
		{
			currfvel = 0.0f;
		}
	}
	else
	{
		pos.y += currfvel * dt;
		currfvel += fvelinc * dt;
	}
}

RecF Player::PlayerHitBox() const
{
	return RecF( pos.x,pos.x + 16.0f,pos.y - 24,pos.y );
}

Vec2i Player::PlayerPos() const
{
	return Vec2i( pos );
}
