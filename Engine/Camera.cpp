#include "Camera.h"

Camara::Camara( const Vec2f& cPos,Map& map,Player& Pl )
	:
	cPos( cPos ),
	map( map ),
	Pl( Pl )
{
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
	for ( int my = ( int )cPos.y - 19; my <= cPos.y + 19; ++my )
	{
		for ( int mx = ( int )cPos.x - 25 ; mx <= cPos.x + 25; ++mx )
		{
			auto contens = map.getContens( { mx,my } );
			if ( contens != -1 )
			{
				gfx.DrawRecDimClip(
					Vec2f(
						( ( ( float )mx - cPos.x ) * 16.0f ) + gfx.ScreenWidth / 2,
						( ( ( float )my - cPos.y ) * 16.0f ) + gfx.ScreenHeight / 2
					),
					15,
					15,
					Colors::Green
				);
			}
		}
	}
	gfx.DrawSprite(
		( int )( ( ( Pl.PlPos().x - cPos.x ) * 16.0f - Pl.PlWidth() / 2 ) + gfx.ScreenWidth / 2 ),
		( int )( ( ( Pl.PlPos().y - cPos.y ) * 16.0f - Pl.PlHeight() ) + gfx.ScreenHeight / 2 ),
		Pl.PlSprite()
	);
	//gfx.DrawRecDimClip(
	//	Vec2f(
	//		( ( Pl.PlPos().x - cPos.x ) * 16.0f - Pl.PlWidth() / 2 ) + gfx.ScreenWidth / 2,
	//		( ( Pl.PlPos().y - cPos.y ) * 16.0f - Pl.PlHeight() ) + gfx.ScreenHeight / 2
	//	),
	//	Pl.PlWidth(),
	//	Pl.PlHeight(),
	//	Colors::Blue
	//);
}
