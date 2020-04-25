#include "Player.h"

Player::Player( const Vec2f& pos,Map& map )
	:
	map( map ),
	pos( pos )
{
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
	//Physiks( dt );
}

RecF Player::PlHitBox() const
{
	return RecF( pos.x - PlayerWidth / 2,pos.x + PlayerWidth / 2,pos.y - PlayerHeight,pos.y );
}

Vec2f Player::PlPos() const
{
	return Vec2f( pos );
}

int Player::PlWidth() const
{
	return PlayerWidth;
}

int Player::PlHeight() const
{
	return PlayerHeight;
}

void Player::Update( const float dt )
{
	pos += vel * dt;
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
