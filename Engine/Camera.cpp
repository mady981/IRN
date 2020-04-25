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
	for ( int my = ( int )cPos.y - 1; my < cPos.y + 38; ++my )
	{
		for ( int mx = ( int )cPos.x -1 ; mx < cPos.x + 51; ++mx )
		{
			auto contens = map.getContens( { mx,my } );
			if ( contens != -1 )
			{
				gfx.DrawRecDimClip( Vec2f( ( ( ( float )mx - cPos.x ) * 16.0f ),( ( ( float )my - cPos.y ) * 16.0f ) ),15,15,Colors::Green );
			}
		}
	}
	gfx.DrawRecDimClip( Vec2f( Pl.PlPos().x - cPos.x,Pl.PlPos().y - cPos.y ) * 16.0f,Pl.PlWidth(),Pl.PlHeight(),Colors::Blue );
}
