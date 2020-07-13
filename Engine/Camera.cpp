#include "Camera.h"
#include "WorldObject.h"

Camera::Camera( const Vec2f& cPos )
	:
	cPos( cPos )
{
}

void Camera::BindToPlayer( const Vec2f& PlayerPos )
{
	cPos = PlayerPos;
}

void Camera::HandleImputs( Keyboard& kbd,WorldObject& world )
{
	if ( !FreeCam )
	{
		if ( kbd.KeyIsPressed( 'M' ) )
		{
			FreeCam = true;
		}
		BindToPlayer( world.getPl()->getPos() );
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
		if ( kbd.KeyIsPressed( VK_CONTROL ) )
		{
			Move( cdir,50.0f );
		}
		else
		{
			Move( cdir );
		}
	}
}

void Camera::Move( const Vec2f& dir,std::optional<float> camspeed )
{
	cVel = dir * camspeed.value_or( FreeCamMoveSpeed );
}

void Camera::Move( const Vec2f& dir )
{
	Move( dir,{} );
}

void Camera::Update( float dt )
{
	if ( FreeCam )
	{
		cPos += cVel * dt;
	}
}

Vec2f Camera::cPos_get() const
{
	return Vec2f( cPos );
}
