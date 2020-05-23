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

void Camara::HandelImputs( Keyboard& kbd )
{
	if ( !FreeCam )
	{
		if ( kbd.KeyIsPressed( 'M' ) )
		{
			FreeCam = true;
		}
		BindToPlayer( Pl.Pos() );
	}
	else
	{
		Vec2f cdir = { 0.0f,0.0f };
		if ( kbd.KeyIsPressed( 'P' ) )
		{
			FreeCam = false;
		}
		if ( kbd.KeyIsPressed( VK_UP ) )
		{
			cdir.y -= 1.0;
		}
		if ( kbd.KeyIsPressed( VK_DOWN ) )
		{
			cdir.y += 1.0f;
		}
		if ( kbd.KeyIsPressed( VK_LEFT ) )
		{
			cdir.x -= 1.0f;
		}
		if ( kbd.KeyIsPressed( VK_RIGHT ) )
		{
			cdir.x += 1.0f;
		}
		Move( cdir );
	}
}

void Camara::Move( const Vec2f& dir )
{
	cVel = dir * FreeCamMoveSpeed;
}

void Camara::Update( float dt )
{
	if ( FreeCam )
	{
		cPos += cVel * dt;
	}
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
				map.Tiles().find( { mx,my } )->second->Draw( cPos,gfx );
			}
		}
	}
	// Enemys
	for ( const auto& e : eh.Enemys() )
	{
		e->Draw( cPos,gfx );
	}
	// Player
	Pl.Draw( cPos,gfx );
}
