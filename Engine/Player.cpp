#include "Player.h"

Player::Player( const Vec2f& pos,Map& map )
	:
	Entity( pos,{ 0,0 },150,10.0f,20.0f,45.0f,10.0f,1.0f,SurfaceCodex::Retrieve( L"Player.bmp" ),map )
{
}

void Player::HandleImputs( Keyboard& kbd )
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
    /*------Test Code Begin---------------------*/
    if ( kbd.KeyIsPressed( 'R' ) )
    {
        debugSetPlayer( { 0,-1 },0.0f );
    }
    if ( kbd.KeyIsPressed( 'J' ) && !ispresst )
    {
        TakeDamage( 10.0f );
        ispresst = true;
    }
    else if ( kbd.KeyIsPressed( 'H' ) && !ispresst )
    {
        healPlayer( 1000.0f );
        ispresst = true;
    }
    if ( kbd.KeyIsPressed( 'O' ) && !ispresst )
    {
        incMaxHP( 20.0f );
        ispresst = true;
    }
    if ( kbd.KeyIsPressed( 'L' ) && !ispresst )
    {
        decMaxHP( 20.0f );
        ispresst = true;
    }
    /*------Test Code End----------------------*/
}

void Player::Draw( const Vec2f& pos_c,Graphics& gfx ) const
{
    const Vec2f offset = pos - pos_c;
    gfx.DrawSprite(
        int( offset.x * Map::Dimantion() - pSprite->getWidth() / 2 + gfx.ScreenWidth / 2 ),
        int( offset.y * Map::Dimantion() - pSprite->getHeight() + gfx.ScreenHeight / 2 ),
        *pSprite,
        facing.x < 0
    );
}

float Player::MaxHitPoints() const
{
	return maxHitPoints;
}
