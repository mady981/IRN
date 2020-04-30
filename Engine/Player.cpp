#include "Player.h"

Player::Player( const Vec2f& pos,Map& map )
	:
	Entity( pos,{ 0,0 },150,10.0f,20.0f,45.0f,10.0f,new Surface( L"../Engine/Sprite/Player.bmp" ),map )
{
}

float Player::MaxHitPoints() const
{
	return maxHitPoints;
}
