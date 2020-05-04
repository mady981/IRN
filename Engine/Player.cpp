#include "Player.h"

Player::Player( const Vec2f& pos,Map& map )
	:
	Entity( pos,{ 0,0 },150,10.0f,20.0f,45.0f,10.0f,1.0f,new Surface( L"../Engine/Sprite/Player.bmp" ),map )
{
}

void Player::HandleImtputs( Keyboard& kbd )
{
    Vec2f dir = { 0.0f,0.0f };
    bool jump = false;
    if ( kbd.KeyIsPressed( VK_SPACE ) )
    {
        jump = true;
    }
    if ( kbd.KeyIsPressed( 'W' ) )
    {
        dir.y -= 1.0;
    }
    if ( kbd.KeyIsPressed( 'S' ) )
    {
        dir.y += 1.0f;
    }
    if ( kbd.KeyIsPressed( 'A' ) )
    {
        dir.x -= 1.0f;
    }
    if ( kbd.KeyIsPressed( 'D' ) )
    {
        dir.x += 1.0f;
    }
    setDir( dir,jump );
}

float Player::MaxHitPoints() const
{
	return maxHitPoints;
}
