#include "Camera.h"

Camara::Camara( const Vec2f& cPos,Map& map,Player& Pl,Enemy& eny )
	:
	cPos( cPos ),
	map( map ),
	Pl( Pl ),
	eny( eny )
{
}

void Camara::BindToPlayer( const Vec2f& PlayerPos )
{
	cPos = PlayerPos;
}

void Camara::Move( const Vec2f& dir )
{
	cVel = dir * 10.0f;
}

void Camara::Update( float dt )
{
	cPos += cVel * dt;
}

void Camara::Draw( Graphics& gfx ) const
{
	// Tiles
	for ( int my = ( int )cPos.y - 19; my <= cPos.y + 19; ++my )
	{
		for ( int mx = ( int )cPos.x - 25 ; mx <= cPos.x + 25; ++mx )
		{
			auto contens = map.getContens( { mx,my } );
			if ( contens != -1 )
			{
				gfx.DrawSprite(
					( int )( ( ( ( float )mx - cPos.x ) * 16.0f ) + gfx.ScreenWidth / 2 ),
					( int )( ( ( ( float )my - cPos.y ) * 16.0f ) + gfx.ScreenHeight / 2 ),
					*map.TileSprite()
				);
				//gfx.DrawRecDimClip(
				//	Vec2f(
				//		( ( ( float )mx - cPos.x ) * 16.0f ) + gfx.ScreenWidth / 2,
				//		( ( ( float )my - cPos.y ) * 16.0f ) + gfx.ScreenHeight / 2
				//	),
				//	15,
				//	15,
				//	Colors::Green
				//);
			}
		}
	}
	// Enemys
	gfx.DrawSpriteOverColor(
		( int )( ( ( eny.Pos().x - cPos.x ) * map.TileSprite()->getWidth() - eny.Sprite()->getWidth() / 2 ) + gfx.ScreenWidth / 2 ),
		( int )( ( ( eny.Pos().y - cPos.y ) * map.TileSprite()->getHeight() - eny.Sprite()->getHeight() ) + gfx.ScreenHeight / 2 ),
		*eny.Sprite(),
		Colors::Red
	);
	// Player
	gfx.DrawSprite(
		( int )( ( ( Pl.Pos().x - cPos.x ) * map.TileSprite()->getWidth() - Pl.Sprite()->getWidth() / 2 ) + gfx.ScreenWidth / 2 ),
		( int )( ( ( Pl.Pos().y - cPos.y ) * map.TileSprite()->getHeight() - Pl.Sprite()->getHeight() ) + gfx.ScreenHeight / 2 ),
		*Pl.Sprite()
	);
	//gfx.DrawRecDimClip(
	//	Vec2f(
	//		( ( Pl.Pos().x - cPos.x ) * 16.0f - Pl.PlWidth() / 2 ) + gfx.ScreenWidth / 2,
	//		( ( Pl.Pos().y - cPos.y ) * 16.0f - Pl.PlHeight() ) + gfx.ScreenHeight / 2
	//	),
	//	Pl.PlWidth(),
	//	Pl.PlHeight(),
	//	Colors::Blue
	//);
}
