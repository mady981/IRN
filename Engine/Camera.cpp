#include "Camera.h"

Camara::Camara( const Vec2f& cPos,Map& map,Player& Pl,EntityHandle& eh )
	:
	cPos( cPos ),
	map( map ),
	Pl( Pl ),
	eh( eh )
{
}

void Camara::BindToPlayer( const Vec2f& PlayerPos )
{
	cPos = PlayerPos;
}

void Camara::Move( const Vec2f& dir )
{
	cVel = dir * FreeCamMoveSpeed;
}

void Camara::Update( float dt )
{
	cPos += cVel * dt;
}

void Camara::Draw( Graphics& gfx ) const
{
	// Tiles
	const int HalfRenderHeight = gfx.ScreenHeight / map.TileSprite()->getHeight() / 2 + 1;
	const int HalfRenderWidth = gfx.ScreenWidth / map.TileSprite()->getWidth() / 2 + 1;
	for ( int my = ( int )cPos.y - HalfRenderHeight; my <= cPos.y + HalfRenderHeight; ++my )
	{
		for ( int mx = ( int )cPos.x - HalfRenderWidth; mx <= cPos.x + HalfRenderWidth; ++mx )
		{
			auto contens = map.getContens( { mx,my } );
			if ( contens != -1 )
			{
				gfx.DrawSprite(
					( int )( ( ( ( float )mx - cPos.x ) * map.TileSprite()->getWidth() ) + gfx.ScreenWidth / 2 ),
					( int )( ( ( ( float )my - cPos.y ) * map.TileSprite()->getHeight() ) + gfx.ScreenHeight / 2 ),
					*map.TileSprite()
				);
			}
		}
	}
	// Enemys
	for ( auto e : eh.Enemys() )
	{
		gfx.DrawSpriteOverColor(
			( int )( ( ( e->Pos().x - cPos.x ) * map.TileSprite()->getWidth() - e->Sprite()->getWidth() / 2 ) + gfx.ScreenWidth / 2 ),
			( int )( ( ( e->Pos().y - cPos.y ) * map.TileSprite()->getHeight() - e->Sprite()->getHeight() ) + gfx.ScreenHeight / 2 ),
			*e->Sprite(),
			Colors::Red,
			e->Facing().x < 0
		);
	}
	// Player
	gfx.DrawSprite(
		( int )( ( ( Pl.Pos().x - cPos.x ) * map.TileSprite()->getWidth() - Pl.Sprite()->getWidth() / 2 ) + gfx.ScreenWidth / 2 ),
		( int )( ( ( Pl.Pos().y - cPos.y ) * map.TileSprite()->getHeight() - Pl.Sprite()->getHeight() ) + gfx.ScreenHeight / 2 ),
		*Pl.Sprite(),
		Pl.Facing().x < 0
	);
}
