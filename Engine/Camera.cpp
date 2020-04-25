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
	for ( int my = ( int )cPos.y - 18; my < cPos.y + 18; ++my )
	{
		for ( int mx = ( int )cPos.x - 25; mx < cPos.x + 25; ++mx )
		{
			auto contens = map.getContens( { mx,my } );
			if ( contens != -1 )
			{
				gfx.DrawRecDimClip( { ( mx - ( int )cPos.x ) * 16,( my - ( int )cPos.y ) * 16 },15,15,Colors::Green );
			}
		}
	}
	gfx.DrawRecDimClip( Vec2f( Pl.PlPos().x - cPos.x,Pl.PlPos().y - cPos.y ) * 16.0f,Pl.PlWidth(),Pl.PlHeight(),Colors::Blue );
}
