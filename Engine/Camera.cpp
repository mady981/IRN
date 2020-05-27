#include "Camera.h"

Camara::Camara( const Vec2f& cPos,Player& pl )
	:
	cPos( cPos ),
	pl( pl )
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
		BindToPlayer( pl.Pos() );
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

Vec2f Camara::cPos_get() const
{
	return Vec2f( cPos );
}
